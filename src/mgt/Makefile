S7 := 1
include ../mk/preface.mk

CPP_FLAGS += -I$(BOOST_DIR) -I. -I.. -I$(SAFPLUS_INC_DIR)

# Management includes and libraries
CPP_FLAGS +=  $(SAFPLUS_MGT_INC_FLAGS)
C_FLAGS += -I$(SAFPLUS_SRC_DIR)/SAFplus/include -I$(SAFPLUS_INC_DIR) -I$(SAFPLUS_SRC_DIR)/SAFplus/3rdparty/ezxml/stable

CLIENT_H := $(wildcard ../include/*.hxx)
CLIENT_SRC := $(wildcard *.cxx) $(wildcard *.cc)
CLIENT_OBJ := $(addprefix $(MWOBJ_DIR)/,$(subst .cc,.o, $(subst .cxx,.o,$(CLIENT_SRC))))

Release all: $(LIB_DIR)/libclMgt.so

$(LIB_DIR)/libclMgt.so: $(CLIENT_OBJ)
	$(LINK_SO) $@ $+ $(LINK_SO_LIBS) `pkg-config --libs protobuf`

$(MWOBJ_DIR)/%.o: %.cxx Makefile $(CLIENT_H)
	$(COMPILE_CPP) $@ $<

$(MWOBJ_DIR)/%.o: %.cc Makefile $(CLIENT_H)
	$(COMPILE_CPP) $@ $<

clean:
	rm -f $(LIB_DIR)/libclMgt.so $(CLIENT_OBJ)