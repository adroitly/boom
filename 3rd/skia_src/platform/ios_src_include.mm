// port
#include "../src/SkImageDecoder_FactoryDefault.cpp"
#include "../src/ports/SkFontHost_none.cpp"
#include "../src/ports/SkDebug_stdio.cpp"
#include "../src/ports/SkGlobalInitialization_default.cpp"
#include "../src/ports/SkTLS_pthread.cpp"
#include "../src/ports/SkMemory_malloc.cpp"
#include "../src/ports/SkOSFile_stdio.cpp"
#include "../src/ports/SkOSFile_posix.cpp"

// opts
#include "../src/opts/SkBitmapProcState_opts_arm.cpp"
#include "../src/opts/SkMorphology_opts_arm.cpp"
#include "../src/opts/SkBlurImage_opts_arm.cpp"
#include "../src/opts/SkBlitMask_opts_arm.cpp"
#include "../src/opts/SkBlitRow_opts_none.cpp"
#include "../src/opts/SkUtils_opts_arm.cpp"
#include "../src/opts/SkXfermode_opts_arm.cpp"

// utils
#include "../src/utils/mac/SkCreateCGImageRef.cpp"
#include "../src/utils/mac/SkStream_mac.cpp"