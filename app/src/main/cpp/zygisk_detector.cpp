#include "native_detector.h"
namespace zygisk {
    bool detectZygiskInjection() { return false; }
    std::string getZygiskDetectionDetails() { return ""; }
    bool detectSolistAnomaly() { return false; }
    bool detectVmapAnomaly() { return false; }
    bool detectAtexitAnomaly() { return false; }
    bool detectSmapsAnomaly() { return false; }
    bool detectModuleUnload() { return false; }
    int getModuleUnloadCount() { return 0; }
    std::vector<std::string> getZygiskFindings() { return {}; }
    bool isZygiskTypeDetected(const std::string& type) { return false; }
    bool setupZygiskTrapFd() { return false; }
    bool verifyZygiskTrapFd() { return false; }
    std::string getZygiskTrapDetails() { return ""; }
    void cleanupZygiskTrapFd() {}
    bool isOTmpfileSupported() { return false; }
}
