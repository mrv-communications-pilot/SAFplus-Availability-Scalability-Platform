#!/bin/sh

install_dir=${HOME}/clovis_2015
cd `dirname $0`
script_dir=$PWD

echo "copying toolchain..."

TARGET=i686-nptl-linux-gnu
mkdir -p ${install_dir}/buildtools
if [ -f ${TARGET}.tar.gz ]; then
        tar -C ${install_dir}/buildtools -xzf ${TARGET}.tar.gz
        ln -s ${install_dir}/buildtools/${TARGET} ${install_dir}/buildtools/i686
        echo "Copied Toolchain successfully"
else
        echo "ERROR : Toolchain ${TARGET}.tar.gz is missing"
	exit
fi

#export CPPFLAGS="-I/usr/include/c++/4.6.3 -I/usr/include/c++/4.6.3/i686-linux-gnu"
# we run preinstall as root
sudo ./install   --preinstall

if [ $? != 0 ]
then
   echo "Failed to install OC new version"
else
   sudo rm -rf log
   ./install   --install    --install-dir ${install_dir}
   if [ $? != 0 ]
   then
   	echo "Failed to install OC new version"
   fi
fi

#cp -r $src_dir/.git ${install_dir}/sdk-6.0 


