#include "native_detector.h"
#include <fstream>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/vfs.h>

namespace filesystem {
    
    bool detectOverlayfsKernelSupport() {
        // Check if overlayfs is supported in kernel
        std::ifstream filesystems("/proc/filesystems");
        if (!filesystems.is_open()) return false;
        
        std::string line;
        while (std::getline(filesystems, line)) {
            if (line.find("overlay") != std::string::npos) {
                return true;
            }
        }
        return false;
    }
    
    bool detectSystemFsTypeAnomaly() {
        // Check /system filesystem type
        struct statfs buf;
        if (statfs("/system", &buf) != 0) {
            return false;
        }
        
        // Check for unusual filesystem types
        // ext4 is 0xEF53, f2fs is 0xF2F52010
        if (buf.f_type != 0xEF53 && buf.f_type != 0xF2F52010) {
            return true;
        }
        
        return false;
    }
    
    bool detectTmpfsSizeAnomaly() {
        // Check /data/local/tmp size
        struct statfs buf;
        if (statfs("/data/local/tmp", &buf) != 0) {
            return false;
        }
        
        // tmpfs type is 0x01021994
        if (buf.f_type == 0x01021994) {
            // Check if size is unusually large
            unsigned long long total_size = buf.f_blocks * buf.f_bsize;
            if (total_size > 1024 * 1024 * 1024) { // > 1GB
                return true;
            }
        }
        
        return false;
    }
    
    bool detectBindMountByRoot() {
        // Check for bind mounts in /proc/self/mountinfo
        std::ifstream mountinfo("/proc/self/mountinfo");
        if (!mountinfo.is_open()) return false;
        
        std::string line;
        while (std::getline(mountinfo, line)) {
            // Look for bind mounts
            if (line.find("bind") != std::string::npos) {
                return true;
            }
        }
        return false;
    }
    
    bool detectMountOptionsAnomaly() {
        // Check for suspicious mount options
        std::ifstream mounts("/proc/self/mounts");
        if (!mounts.is_open()) return false;
        
        std::string line;
        while (std::getline(mounts, line)) {
            // Check for remount or rw on system
            if (line.find("/system ") != std::string::npos &&
                line.find(" rw,") != std::string::npos) {
                return true;
            }
        }
        return false;
    }
    
    bool detectStatxMountRootAnomaly() {
        // Check mount root using stat
        struct stat system_stat, root_stat;
        
        if (stat("/system", &system_stat) != 0 ||
            stat("/", &root_stat) != 0) {
            return false;
        }
        
        // /system should be on a different device than /
        if (system_stat.st_dev == root_stat.st_dev) {
            return true;
        }
        
        return false;
    }
    
    bool detectFilesystemAnomalies() {
        return detectSystemFsTypeAnomaly() || 
               detectTmpfsSizeAnomaly() ||
               detectBindMountByRoot() ||
               detectMountOptionsAnomaly();
    }
}
