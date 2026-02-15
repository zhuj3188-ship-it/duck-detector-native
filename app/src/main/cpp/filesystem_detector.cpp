#include "native_detector.h"
namespace filesystem {
    bool detectFilesystemAnomalies() { return false; }
    bool detectOverlayfsKernelSupport() { return false; }
    bool detectSystemFsTypeAnomaly() { return false; }
    bool detectTmpfsSizeAnomaly() { return false; }
    bool detectBindMountByRoot() { return false; }
    bool detectMountOptionsAnomaly() { return false; }
    bool detectStatxMountRootAnomaly() { return false; }
}
