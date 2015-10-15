S7 := 1
include ./src/mk/preface.mk

export PKG_NAME=safplus
export PKG_VER ?=7.0
export PKG_REL ?=1
TOP_DIR := $(CURDIR)
TAR_NAME := $(dir $(TOP_DIR))$(PKG_NAME)_$(PKG_VER).tar.gz
BUILD := $(TOP_DIR)/build
$(info VERSION is $(PKG_VER))
$(info RELEASE is $(PKG_REL))
$(info TOP DIR is $(TOP_DIR))

all: 
	$(info TBD)

prepare:
	echo  "This target prepares your environment for package generation.  You only need to run this once (as root)"
	apt-get install dh-make

archive: $(TAR_NAME)

$(TAR_NAME):
	$(info entering $(TOP_DIR))
	echo "Generating $(TAR_NAME) archive"; 
	tar cvzf $(TAR_NAME) -C $(TOP_DIR) *  --exclude=build --exclude=target --exclude=images --exclude=boost_1_55_0;
	mkdir -p $(BUILD)

define prepare_env_rpm
$(eval PKG_NAME=$1)
$(info Packing the $(PKG_NAME) in RPM)
$(eval PKG_DIR:=$(dir $(TOP_DIR))rpmbuild_$(PKG_NAME))
$(info PKG_DIR is $(PKG_DIR))
rm -rf $(PKG_DIR)
mkdir -p $(PKG_DIR)
$(eval BUILD_DIR:=$(PKG_DIR)/BUILD)
$(eval SRC_DIR:=$(PKG_DIR)/SOURCES)
$(eval SPECS_DIR:=$(PKG_DIR)/SPECS)
$(eval SRPMS_DIR:=$(PKG_DIR)/SRPMS)
$(eval RPMS_DIR:=$(PKG_DIR)/RPMS)
mkdir -p $(BUILD_DIR)
mkdir -p $(SRC_DIR)
mkdir -p $(SPECS_DIR)
mkdir -p $(SRPMS_DIR)
mkdir -p $(RPMS_DIR)
cp -r $(TOP_DIR)/SPECS/* $(SPECS_DIR)
sed -i '/Name:/c Name:\t\t$(PKG_NAME)\nVersion:\t$(PKG_VER)\nRelease:\t$(PKG_REL)%{dist}' $(SPECS_DIR)/safplus.spec
sed -i '/Prefix:/c Prefix:\t/opt/safplus/$(PKG_VER)/$2' $(SPECS_DIR)/safplus.spec
endef

define copy_binpkg_files
$(eval DEST_PKG_DIR=$1)
cp -rf $(BIN_DIR) $(DEST_PKG_DIR)
cp -rf $(PLUGIN_DIR) $(DEST_PKG_DIR)
cp -rf $(LIB_DIR) $(DEST_PKG_DIR)
mkdir -p $(DEST_PKG_DIR)/src
#Some of the header files present in the src/include contains symbolic links.
#We need to Copy those symlinks files as full files
#Both safplus src and binary debian package contains the header files,dpkg throws an error while installing the safplus
#debian package. Workaround is renameing the include directory to include1. Need to fix this problem.
rsync -rL $(SAFPLUS_INC_DIR) $(DEST_PKG_DIR)/src
rsync -rL $(SAFPLUS_MAKE_DIR) $(DEST_PKG_DIR)/src
cp -rf $(TOP_DIR)/DEB/Makefile $(DEST_PKG_DIR)
endef

rpm-src: archive
	$(call prepare_env_rpm,safplus-src,sdk)
	tar xvzf $(TAR_NAME) -C $(BUILD_DIR)
	sed -i '/%install/aexport PREFIX=%prefix\nexport DESTDIR=$$RPM_BUILD_ROOT\nmake rpm_install' $(SPECS_DIR)/safplus.spec
	sed -i '/%defattr/a /%prefix/*' $(SPECS_DIR)/safplus.spec
	rpmbuild  --define '_topdir $(PKG_DIR)' -bb $(SPECS_DIR)/safplus.spec
	mkdir -p $(BUILD)
	cp $(RPMS_DIR)/$(shell uname -p)/*.rpm $(BUILD)

rpm-bin: build_binary
	$(call prepare_env_rpm,safplus,sdk/target)
	$(call copy_binpkg_files,$(BUILD_DIR))
	sed -i '/%install/aexport PREFIX=%prefix\nexport DESTDIR=$$RPM_BUILD_ROOT\nmake rpm_install' $(SPECS_DIR)/safplus.spec
	sed -i '/%defattr/a /%prefix/*\n/%prefix/../src/*' $(SPECS_DIR)/safplus.spec
	rpmbuild  --define '_topdir $(PKG_DIR)' -bb $(SPECS_DIR)/safplus.spec
	mkdir -p $(BUILD)
	cp $(RPMS_DIR)/$(shell uname -p)/*.rpm $(BUILD)

rpm: rpm-bin rpm-src

define prepare_env_deb
$(eval PKG_NAME=$1)
$(info Packing the $(PKG_NAME) in DEBIAN)
$(eval PKG_DIR:=$(dir $(TOP_DIR))debbuild_$(PKG_NAME))
$(info PKG_DIR is $(PKG_DIR))
rm -rf $(PKG_DIR)
mkdir -p $(PKG_DIR)
$(eval DEB_TOP_DIR=$(PKG_DIR)/$(PKG_NAME)-$(PKG_VER))
mkdir -p $(DEB_TOP_DIR)
$(eval DEBIAN_DIR:=$(DEB_TOP_DIR)/debian)
echo $(DEBIAN_DIR)
mkdir -p  $(DEBIAN_DIR)
cp -r $(TOP_DIR)/DEB/* $(DEBIAN_DIR)
if [ "$(shell uname -p)" = "x86_64" ]; \
then \
     sed -i '/Architecture:/c Package: $(PKG_NAME)\nArchitecture: amd64\nSection: $2' $(DEBIAN_DIR)/control; \
else \
     sed -i '/Architecture:/c Package: $(PKG_NAME)\nArchitecture: i386\nSection: $2' $(DEBIAN_DIR)/control; \
fi;
sed -i '/Source:/c Source: $(PKG_NAME)\nSection: $2' $(DEBIAN_DIR)/control
sed -i '/prefix:/c prefix=/opt/saflus/$(PKG_VER)/$3' $(DEBIAN_DIR)/postrm
sed -i '/prefix:/c export PREFIX?=/opt/safplus/$(PKG_VER)/$3\nexport PACKAGENAME?=$(PKG_NAME)' $(DEBIAN_DIR)/rules
sed -i '/Destdir:/c export DESTDIR?=$(DEBIAN_DIR)/$(PKG_NAME)\nexport LIBRARY_DIR=$(DEB_TOP_DIR)' $(DEBIAN_DIR)/rules
sed -i '/safplus:/c$(PKG_NAME) ($(subst .,-,$(PKG_VER))-$(PKG_REL)) stable; urgency=medium' $(DEBIAN_DIR)/changelog
endef

deb-src:archive
	$(call prepare_env_deb,safplus-src,devel,sdk)
	tar xvzf $(TAR_NAME) -C $(DEB_TOP_DIR)
	sed -i '/Architecture:/aReplaces: safplus' $(DEBIAN_DIR)/control
	#echo TBD: create source install package
	cd $(DEB_TOP_DIR) && dpkg-buildpackage -uc -us -b
	mkdir -p $(BUILD)
	cp $(PKG_DIR)/*.deb $(BUILD)


build_binary:
	cd src && make 


deb-bin: build_binary
	$(call prepare_env_deb,safplus,lib,sdk/target)
	$(call copy_binpkg_files, $(DEB_TOP_DIR))
	cd $(DEB_TOP_DIR) && dpkg-buildpackage -uc -us -b
	mkdir -p $(BUILD)
	cp $(PKG_DIR)/*.deb $(BUILD)

deb: deb-bin deb-src

#Due to inclusion of src/mk/preface.mk creates a src/target directory in the package.
#This rule removes src/target from the safplus src package 
remove_target:
	rm -rf $(PWD)/src/target

define safplus_pkg_install
mkdir -p $(DESTDIR)/$(PREFIX)
for value in $1;do \
cp -r $$value $(DESTDIR)/$(PREFIX); \
done
# Need to uncomment the below line to include git repository in the SAFPlus Debian package.
#cp -r $(PWD)/.git $(DESTDIR)/$(PREFIX)
endef

deb_install:remove_target
	$(eval REQ_FILES:=$(filter-out $(PWD)/debian/, $(wildcard $(PWD)/*/)))
	$(call safplus_pkg_install,$(REQ_FILES))

deb_clean:remove_target
	rm -rf debian/$(PACKAGENAME).*debhelper
	rm -rf debian/$(PACKAGENAME).substvars

deb_build:remove_target
	echo "Not required"

rpm_install:remove_target
	$(eval REQ_FILES:=$(wildcard $(PWD)/*/))
	$(info $(REQ_FILES))
	$(call safplus_pkg_install,$(REQ_FILES))

clean:
	rm -rf $(TAR_NAME) $(BUILD)
