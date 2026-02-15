#include "native_detector.h"
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>

namespace mount {
    
    bool detectMagiskMounts() {
        std::ifstream mounts("/proc/self/mounts");
        if (!mounts.is_open()) return false;
        
        std::string line;
        while (std::getline(mounts, line)) {
            if (line.find("magisk") != std::string::npos ||
                line.find("/sbin/.magisk") != std::string::npos ||
                line.find("/data/adb/magisk") != std::string::npos) {
                return true;
            }
        }
        return false;
    }
    
    bool detectBusybox() {
        struct stat st;
        return stat("/system/xbin/busybox", &st) == 0 ||
               stat("/system/bin/busybox", &st) == 0 ||
               stat("/sbin/busybox", &st) == 0;
    }
    
    bool detectZygiskCache() {
        struct stat st;
        return stat("/data/adb/modules/.zygisk", &st) == 0;
    }
    
    bool detectSystemRwMount() {
        std::ifstream mounts("/proc/self/mounts");
        if (!mounts.is_open()) return false;
        
        std::string line;
        while (std::getline(mounts, line)) {
            if (line.find("/system ") != std::string::npos &&
                line.find(" rw,") != std::string::npos) {
                return true;
            }
        }
        return false;
    }
    
    bool detectOverlayMounts() {
        std::ifstream mounts("/proc/self/mounts");
        if (!mounts.is_open()) return false;
        
        std::string line;
        while (std::getline(mounts, line)) {
            if (line.find("overlay") != std::string::npos) {
                return true;
            }
        }
        return false;
    }
    
    bool detectMountNamespaceAnomaly() {
        // Check if mount namespace is different from init
        std::ifstream self("/proc/self/ns/mnt");
        std::ifstream init("/proc/1/ns/mnt");
        
        if (!self.is_open() || !init.is_open()) return false;
        
        struct stat self_stat, init_stat;
        if (fstat(fileno(self._M_filebuf._M_file.file()), &self_stat) != 0 ||
            fstat(fileno(init._M_filebuf._M_file.file()), &init_stat) != 0) {
            return false;
        }
        
        return self_stat.st_ino != init_stat.st_ino;
    }
    
    bool detectDataAdbMounts() {
        std::ifstream mounts("/proc/self/mounts");
        if (!mounts.is_open()) return false;
        
        std::string line;
        while (std::getline(mounts, line)) {
            if (line.find("/data/adb") != std::string::npos) {
                return true;
            }
        }
        return false;
    }
    
    bool detectMountAnomalies() {
        return detectMagiskMounts() || detectSystemRwMount() ||
               detectOverlayMounts() || detectDataAdbMounts();
    }
    
    std::string getMountDetectionDetails() {
        std::stringstream ss;
        ss << "Mount Anomaly Detection:\n";
        if (detectMagiskMounts()) ss << "- Magisk mounts detected\n";
        if (detectBusybox()) ss << "- Busybox binary found\n";
        if (detectZygiskCache()) ss << "- Zygisk cache detected\n";
        if (detectSystemRwMount()) ss << "- System mounted as RW\n";
        if (detectOverlayMounts()) ss << "- Overlay mounts detected\n";
        if (detectDataAdbMounts()) ss << "- /data/adb mounts detected\n";
        return ss.str();
    }
    
    std::vector<std::string> getMountFindings() {
        std::vector<std::string> findings;
        if (detectMagiskMounts()) findings.push_back("Magisk mounts");
        if (detectBusybox()) findings.push_back("Busybox binary");
        if (detectZygiskCache()) findings.push_back("Zygisk cache");
        if (detectSystemRwMount()) findings.push_back("System RW mount");
        if (detectOverlayMounts()) findings.push_back("Overlay mounts");
        if (detectDataAdbMounts()) findings.push_back("/data/adb mounts");
        return findings;
    }
    
    bool isMountTypeDetected(const std::string& type) {
        if (type == "magisk") return detectMagiskMounts();
        if (type == "busybox") return detectBusybox();
        if (type == "zygisk") return detectZygiskCache();
        if (type == "system_rw") return detectSystemRwMount();
        if (type == "overlay") return detectOverlayMounts();
        if (type == "data_adb") return detectDataAdbMounts();
        return false;
    }
}
