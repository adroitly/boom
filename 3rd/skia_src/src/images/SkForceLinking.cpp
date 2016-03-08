/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "SkForceLinking.h"
#include "SkImageDecoder.h"

// This method is required to fool the linker into not discarding the pre-main
// initialization and registration of the decoder classes. Passing true will
// cause memory leaks.
int SkForceLinking(bool doNotPassTrue) {
    if (doNotPassTrue) {
        SkASSERT(false);
        CreateJPEGImageDecoder();
        CreatePNGImageDecoder();
        return -1;
    }
    return 0;
}
