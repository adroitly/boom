LOCAL_PATH := $(call my-dir)
CLASS_PATH_LIBS := $(LOCAL_PATH)/../../../../libs
CLASS_PATH_3RD := $(LOCAL_PATH)/../../../../../3rd
CLASS_PATH_SKIA := $(LOCAL_PATH)/../../../../../3rd/skia_src

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dlua_shared

LOCAL_MODULE_FILENAME := libcocos2dlua

define game-cpp-dir-libs
$(patsubst ./%,%, $(shell find $(CLASS_PATH_LIBS) -name "mac" -prune -o -name "*.cpp" -o -name "*.c" -and -not -name ".*"))
endef  

define game-cpp-dir-3rd
$(patsubst ./%,%, $(shell find $(CLASS_PATH_3RD) -name "FileSystemWatcher" -prune -o -name "skia_src" -prune -o -name "sqlite" -prune -o -name "cocoa" -prune -o -name "*.cpp" -o -name "*.c" -and -not -name ".*"))
endef

define game-cpp-dir-skia
$(patsubst ./%,%, $(shell find $(CLASS_PATH_SKIA)/src -name "opts" -prune -o -name "utils" -prune -o  -name "ports" -prune -o  -name "*.cpp" -o -name "*.c" -and -not -name ".*"))
endef

CPP_FILE_LIST += $(call game-cpp-dir-3rd,.) 
CPP_FILE_LIST += $(call game-cpp-dir-libs,.) 
CPP_FILE_LIST += $(call game-cpp-dir-skia,.)

LOCAL_SRC_FILES := \
../../../../../3rd/skia_src/platform/android_src_include.cpp \
../../Classes/protobuf-lite/google/protobuf/io/coded_stream.cc \
../../Classes/protobuf-lite/google/protobuf/stubs/common.cc \
../../Classes/protobuf-lite/google/protobuf/extension_set.cc \
../../Classes/protobuf-lite/google/protobuf/generated_message_util.cc \
../../Classes/protobuf-lite/google/protobuf/message_lite.cc \
../../Classes/protobuf-lite/google/protobuf/stubs/once.cc \
../../Classes/protobuf-lite/google/protobuf/stubs/atomicops_internals_x86_gcc.cc \
../../Classes/protobuf-lite/google/protobuf/repeated_field.cc \
../../Classes/protobuf-lite/google/protobuf/wire_format_lite.cc \
../../Classes/protobuf-lite/google/protobuf/io/zero_copy_stream.cc \
../../Classes/protobuf-lite/google/protobuf/io/zero_copy_stream_impl_lite.cc \
../../Classes/protobuf-lite/google/protobuf/stubs/stringprintf.cc \
../../Classes/runtime/ConnectWaitLayer.cpp \
../../Classes/runtime/ConsoleCommand.cpp \
../../Classes/runtime/FileServer.cpp \
../../Classes/runtime/Landscape_png.cpp \
../../Classes/runtime/lua_debugger.c \
../../Classes/runtime/PlayDisable_png.cpp \
../../Classes/runtime/PlayEnable_png.cpp \
../../Classes/runtime/Portrait_png.cpp \
../../Classes/runtime/Protos.pb.cc \
../../Classes/runtime/Runtime.cpp \
../../Classes/runtime/Shine_png.cpp \
../../Classes/VisibleRect.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/ConfigParser.cpp \
hellolua/Runtime_android.cpp \
hellolua/main.cpp

LOCAL_SRC_FILES += $(CPP_FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/../../../cocos2d-x/jpeg/external/include/android \
$(LOCAL_PATH)/../../../cocos2d-x/png/external/include/android \
$(LOCAL_PATH)/../../Classes/protobuf-lite \
$(LOCAL_PATH)/../../Classes/runtime \
$(LOCAL_PATH)/../../Classes \
$(LOCAL_PATH)/../../../cocos2d-x/external \
$(CLASS_PATH_LIBS) \
$(CLASS_PATH_LIBS)/game \
$(CLASS_PATH_LIBS)/bridge \
$(CLASS_PATH_LIBS)/platform \
$(CLASS_PATH_LIBS)/rpc \
$(CLASS_PATH_LIBS)/sdklib \
$(CLASS_PATH_LIBS)/sdklib/umeng \
$(CLASS_PATH_3RD) \
$(CLASS_PATH_3RD)/flash_sdk_src/flash_cocos2dx \
$(CLASS_PATH_3RD)/flash_sdk_src/ \
$(CLASS_PATH_3RD)/flash_sdk_src/core/base \
$(CLASS_PATH_SKIA)/include/config \
$(CLASS_PATH_SKIA)/include/core \
$(CLASS_PATH_SKIA)/include/effects \
$(CLASS_PATH_SKIA)/include/images \
$(CLASS_PATH_SKIA)/include/pathops \
$(CLASS_PATH_SKIA)/include/ports \
$(CLASS_PATH_SKIA)/include/utils \
$(CLASS_PATH_SKIA)/include/utils/android \
$(CLASS_PATH_SKIA)/src/utils \
$(CLASS_PATH_SKIA)/src/effects \
$(CLASS_PATH_SKIA)/src/core \
$(CLASS_PATH_SKIA)/src/image \
$(CLASS_PATH_SKIA)/src/opts \
/boost 

LOCAL_CFLAGS     := -std=c++11

LOCAL_STATIC_LIBRARIES := cocos2d_lua_static
LOCAL_WHOLE_STATIC_LIBRARIES += mobclickcpp_static

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path,$(CLASS_PATH_3RD))
$(call import-module,scripting/lua-bindings/proj.android)
$(call import-module,libMobClickCpp)
