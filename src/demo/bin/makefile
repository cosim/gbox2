# sub-makefile
include $(PRO_DIR)/prefix.mak

NAMES 					= \
						arc \
						svg \
						save \
						dump \
						rect \
						line \
						clip \
						path \
						draw \
						point \
						circle \
						cutter \
						ellipse \
						triangle


define MAKE_MODULES
$(1)_TYPE 				= BIN
$(1)_C_FILES 			+= $(1) $(demo_C_FILES)
$(1)_OBJ_FILES 			+= $(demo_OBJ_FILES)
$(1)_LIBS 				+= gbox2 tbox$(DTYPE) $(G2_CONFIG_DEMO_LIBS)
$(1)_LIBS-$(PNG) 		+= png
$(1)_LIBS-$(JPG) 		+= jpeg
$(1)_LIB_DIR 			+= ../.. $(demo_LIB_DIR)
$(1)_INC_DIR 			+= ../.. $(demo_INC_DIR)
$(1)_CXFLAGS 			+= -DTB_PRINT_TAG=\"gbox2\" $(demo_CXFLAGS)
$(1)_CXFLAGS-$(DEBUG) 	+= -DTB_TRACE_ENABLE -DTB_ASSERT_ENABLE $(demo_CXFLAGS-y)
$(1)_CXFLAGS-$(GL) 		+= -DTB_CONFIG_GL
$(1)_CXFLAGS-$(SKIA) 	+= -DTB_CONFIG_SKIA
$(1)_LDFLAGS 			+= $(G2_CONFIG_DEMO_LDFLAGS)
endef
$(foreach name, $(NAMES), $(eval $(call MAKE_MODULES,$(name))))

include $(PRO_DIR)/suffix.mak

