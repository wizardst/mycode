ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

include $(MKFILES_ROOT)/qmacros.mk

define PINFO
PINFO DESCRIPTION=THERMAL TEST
endef
NAME=thermal_test
USEFILE=$(PROJECT_ROOT)/$(NAME).use
INSTALLDIR = sbin


#####AUTO-GENERATED by packaging script... do not checkin#####
   INSTALL_ROOT_nto = $(PROJECT_ROOT)/../../../../../install
   USE_INSTALL_ROOT=1
##############################################################

include $(MKFILES_ROOT)/qtargets.mk

