#ifndef DUCKDETECTOR_NATIVE_DETECTOR_H
#define DUCKDETECTOR_NATIVE_DETECTOR_H

#include <jni.h>
#include <string>
#include <vector>

// SELinux Detection
namespace selinux {
    std::string getSelfSelinuxContext();
    bool getSelinuxEnforceStatus();
    bool hasSuspiciousSelfContext();
    std::vector<std::string> scanProcessSelinuxContexts();
    bool detectSelinuxFull();
    bool hasRootSelinuxContext();
    std::string getSelinuxDetectionDetails();
}

// Kernel Root Detection
namespace kernel {
    bool detectKernelRoot();
    bool detectKernelSu();
    bool detectAPatch();
    std::string getKernelRootDetails();
    std::vector<std::string> getKernelRootFindings();
    std::string getKernelRootDetectionMethod();
    bool isKernelRootTypeDetected(const std::string& type);
    bool detectSusfs();
    std::string getSusfsDetails();
    bool wasSusfsChildKilled();
}

// Mount Anomaly Detection
namespace mount {
    bool detectMountAnomalies();
    std::string getMountDetectionDetails();
    bool detectBusybox();
    bool detectMagiskMounts();
    bool detectZygiskCache();
    bool detectSystemRwMount();
    bool detectOverlayMounts();
    bool detectMountNamespaceAnomaly();
    bool detectDataAdbMounts();
    std::vector<std::string> getMountFindings();
    bool isMountTypeDetected(const std::string& type);
}

// Zygisk Injection Detection
namespace zygisk {
    bool detectZygiskInjection();
    std::string getZygiskDetectionDetails();
    bool detectSolistAnomaly();
    bool detectVmapAnomaly();
    bool detectAtexitAnomaly();
    bool detectSmapsAnomaly();
    bool detectModuleUnload();
    int getModuleUnloadCount();
    std::vector<std::string> getZygiskFindings();
    bool isZygiskTypeDetected(const std::string& type);
    
    // Trap FD Detection
    bool setupZygiskTrapFd();
    bool verifyZygiskTrapFd();
    std::string getZygiskTrapDetails();
    void cleanupZygiskTrapFd();
    bool isOTmpfileSupported();
}

// Heap Entropy Detection
namespace heap {
    bool detectHeapEntropy();
    std::string getHeapEntropyDetails();
}

// Filesystem Anomaly Detection
namespace filesystem {
    bool detectFilesystemAnomalies();
    bool detectOverlayfsKernelSupport();
    bool detectSystemFsTypeAnomaly();
    bool detectTmpfsSizeAnomaly();
    bool detectBindMountByRoot();
    bool detectMountOptionsAnomaly();
    bool detectStatxMountRootAnomaly();
}

// Preload Detection
namespace preload {
    bool hasEarlyDetectionRun();
    bool isPreloadContextValid();
    bool nativeWasDetected();
    bool nativeWasFutileHideDetected();
    bool nativeWasMinorDevGapDetected();
    bool nativeWasMountIdGapDetected();
    bool nativeWasMntStringsDetected();
    bool nativeWasPeerGroupGapDetected();
    std::string nativeGetDetectionMethod();
    std::string nativeGetDetails();
    std::vector<std::string> nativeGetFindings();
    long nativeGetNsMntCtimeDeltaNs();
    long nativeGetMountInfoCtimeDeltaNs();
    std::string nativeGetMntStringsSource();
    std::string nativeGetMntStringsTarget();
    void nativeReset();
}

#endif // DUCKDETECTOR_NATIVE_DETECTOR_H
