#include "native_detector.h"
namespace preload {
    bool hasEarlyDetectionRun() { return false; }
    bool isPreloadContextValid() { return false; }
    bool nativeWasDetected() { return false; }
    bool nativeWasFutileHideDetected() { return false; }
    bool nativeWasMinorDevGapDetected() { return false; }
    bool nativeWasMountIdGapDetected() { return false; }
    bool nativeWasMntStringsDetected() { return false; }
    bool nativeWasPeerGroupGapDetected() { return false; }
    std::string nativeGetDetectionMethod() { return ""; }
    std::string nativeGetDetails() { return ""; }
    std::vector<std::string> nativeGetFindings() { return {}; }
    long nativeGetNsMntCtimeDeltaNs() { return 0; }
    long nativeGetMountInfoCtimeDeltaNs() { return 0; }
    std::string nativeGetMntStringsSource() { return ""; }
    std::string nativeGetMntStringsTarget() { return ""; }
    void nativeReset() {}
}
