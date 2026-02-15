#include "native_detector.h"
#include <android/log.h>

#define LOG_TAG "DuckDetector"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

// This file serves as the main entry point for native detection
// Individual detection implementations are in separate files

void initNativeDetector() {
    LOGD("Native Detector initialized");
}
