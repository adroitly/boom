NDK_TOOLCHAIN_VERSION=4.8
APP_STL:=c++_static
LIBCXX_USE_GABIXX:=true
APP_ABI := armeabi-v7a

APP_CPPFLAGS := -frtti -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -std=c++11 -fsigned-char
LOCAL_C_INCLUDES += ${ANDROID_NDK}/sources/cxx-stl/gnu-libstdc++/4.8/include
APP_LDFLAGS := -latomic

APP_CPPFLAGS += -DCLOVER_USE_PTHREAD=1
APP_CPPFLAGS += -DFLA_USE_LUA_BINDING=1

ifeq ($(NDK_DEBUG),1)
  APP_CPPFLAGS += -DCOCOS2D_DEBUG=1
  APP_OPTIM := debug
else
  APP_CPPFLAGS += -DNDEBUG
  APP_OPTIM := release
endif