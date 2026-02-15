#include <jni.h>
#include <android/log.h>
#include "native_detector.h"

#define LOG_TAG "DuckDetector"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

extern "C" {

// SELinux Detection Functions
JNIEXPORT jstring JNICALL
Java_com_studio_duckdetector_detector_NativeDetector_getSelfSelinuxContext(JNIEnv *env, jobject /* this */) {
    std::string context = selinux::getSelfSelinuxContext();
    return env->NewStringUTF(context.c_str());
}

JNIEXPORT jboolean JNICALL
Java_com_studio_duckdetector_detector_NativeDetector_getSelinuxEnforceStatus(JNIEnv *env, jobject /* this */) {
    return selinux::getSelinuxEnforceStatus();
}

JNIEXPORT jboolean JNICALL
Java_com_studio_duckdetector_detector_NativeDetector_hasSuspiciousSelfContext(JNIEnv *env, jobject /* this */) {
    return selinux::hasSuspiciousSelfContext();
}

JNIEXPORT jobjectArray JNICALL
Java_com_studio_duckdetector_detector_NativeDetector_scanProcessSelinuxContexts(JNIEnv *env, jobject /* this */) {
    std::vector<std::string> contexts = selinux::scanProcessSelinuxContexts();
    jobjectArray result = env->NewObjectArray(contexts.size(), env->FindClass("java/lang/String"), nullptr);
    for (size_t i = 0; i < contexts.size(); i++) {
        env->SetObjectArrayElement(result, i, env->NewStringUTF(contexts[i].c_str()));
    }
    return result;
}

JNIEXPORT jboolean JNICALL
Java_com_studio_duckdetector_detector_NativeDetector_detectSelinuxFull(JNIEnv *env, jobject /* this */) {
    return selinux::detectSelinuxFull();
}

JNIEXPORT jboolean JNICALL
Java_com_studio_duckdetector_detector_NativeDetector_hasRootSelinuxContext(JNIEnv *env, jobject /* this */) {
    return selinux::hasRootSelinuxContext();
}

JNIEXPORT jstring JNICALL
Java_com_studio_duckdetector_detector_NativeDetector_getSelinuxDetectionDetails(JNIEnv *env, jobject /* this */) {
    std::string details = selinux::getSelinuxDetectionDetails();
    return env->NewStringUTF(details.c_str());
}

// Kernel Root Detection Functions
JNIEXPORT jboolean JNICALL
Java_com_studio_duckdetector_detector_NativeDetector_detectKernelRoot(JNIEnv *env, jobject /* this */) {
    return kernel::detectKernelRoot();
}

JNIEXPORT jboolean JNICALL
Java_com_studio_duckdetector_detector_NativeDetector_detectKernelSu(JNIEnv *env, jobject /* this */) {
    return kernel::detectKernelSu();
}

JNIEXPORT jboolean JNICALL
Java_com_studio_duckdetector_detector_NativeDetector_detectAPatch(JNIEnv *env, jobject /* this */) {
    return kernel::detectAPatch();
}

JNIEXPORT jstring JNICALL
Java_com_studio_duckdetector_detector_NativeDetector_getKernelRootDetails(JNIEnv *env, jobject /* this */) {
    std::string details = kernel::getKernelRootDetails();
    return env->NewStringUTF(details.c_str());
}

// Mount Anomaly Detection Functions
JNIEXPORT jboolean JNICALL
Java_com_studio_duckdetector_detector_NativeDetector_detectMountAnomalies(JNIEnv *env, jobject /* this */) {
    return mount::detectMountAnomalies();
}

JNIEXPORT jboolean JNICALL
Java_com_studio_duckdetector_detector_NativeDetector_detectMagiskMounts(JNIEnv *env, jobject /* this */) {
    return mount::detectMagiskMounts();
}

// Zygisk Injection Detection Functions
JNIEXPORT jboolean JNICALL
Java_com_studio_duckdetector_detector_NativeDetector_detectZygiskInjection(JNIEnv *env, jobject /* this */) {
    return zygisk::detectZygiskInjection();
}

JNIEXPORT jboolean JNICALL
Java_com_studio_duckdetector_detector_NativeDetector_setupZygiskTrapFd(JNIEnv *env, jobject /* this */) {
    return zygisk::setupZygiskTrapFd();
}

JNIEXPORT jboolean JNICALL
Java_com_studio_duckdetector_detector_NativeDetector_verifyZygiskTrapFd(JNIEnv *env, jobject /* this */) {
    return zygisk::verifyZygiskTrapFd();
}

// Heap Entropy Detection Functions
JNIEXPORT jboolean JNICALL
Java_com_studio_duckdetector_detector_NativeDetector_detectHeapEntropy(JNIEnv *env, jobject /* this */) {
    return heap::detectHeapEntropy();
}

// Filesystem Anomaly Detection Functions
JNIEXPORT jboolean JNICALL
Java_com_studio_duckdetector_detector_NativeDetector_detectFilesystemAnomalies(JNIEnv *env, jobject /* this */) {
    return filesystem::detectFilesystemAnomalies();
}

// Preload Detection Functions
JNIEXPORT jboolean JNICALL
Java_com_studio_duckdetector_preload_PreloadDetector_hasEarlyDetectionRun(JNIEnv *env, jobject /* this */) {
    return preload::hasEarlyDetectionRun();
}

JNIEXPORT jboolean JNICALL
Java_com_studio_duckdetector_preload_PreloadDetector_nativeWasDetected(JNIEnv *env, jobject /* this */) {
    return preload::nativeWasDetected();
}

} // extern "C"
