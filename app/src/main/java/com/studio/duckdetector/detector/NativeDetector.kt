package com.studio.duckdetector.detector

object NativeDetector {
    
    init {
        System.loadLibrary("duckdetector")
    }
    
    // SELinux Detection
    external fun getSelfSelinuxContext(): String
    external fun getSelinuxEnforceStatus(): Boolean
    external fun hasSuspiciousSelfContext(): Boolean
    external fun scanProcessSelinuxContexts(): Array<String>
    external fun detectSelinuxFull(): Boolean
    external fun hasRootSelinuxContext(): Boolean
    external fun getSelinuxDetectionDetails(): String
    
    // Kernel Root Detection
    external fun detectKernelRoot(): Boolean
    external fun detectKernelSu(): Boolean
    external fun detectAPatch(): Boolean
    external fun getKernelRootDetails(): String
    
    // Mount Anomaly Detection
    external fun detectMountAnomalies(): Boolean
    external fun detectMagiskMounts(): Boolean
    
    // Zygisk Injection Detection
    external fun detectZygiskInjection(): Boolean
    external fun setupZygiskTrapFd(): Boolean
    external fun verifyZygiskTrapFd(): Boolean
    
    // Heap Entropy Detection
    external fun detectHeapEntropy(): Boolean
    
    // Filesystem Anomaly Detection
    external fun detectFilesystemAnomalies(): Boolean
}
