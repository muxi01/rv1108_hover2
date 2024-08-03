ifeq ($(BOARD_WIFI_VENDOR), espressif)
ifeq ($(WPA_SUPPLICANT_VERSION),VER_0_8_X)
include $(call all-subdir-makefiles)
endif
endif
