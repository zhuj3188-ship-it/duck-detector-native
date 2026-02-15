#include "native_detector.h"
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

namespace zygisk {
    
    bool detectSolistAnomaly() {
        std::ifstream maps("/proc/self/maps");
        if (!maps.is_open()) return false;
        
        std::string line;
        while (std::getline(maps, line)) {
            if (line.find("(deleted)") != std::string::npos ||
                line.find("magisk") != std::string::npos ||
                line.find("zygisk") != std::string::npos) {
                return true;
            }
        }
        return false;
    }
    
    bool detectVmapAnomaly() {
        std::ifstream maps("/proc/self/maps");
        if (!maps.is_open()) return false;
        
        int suspicious_count = 0;
        std::string line;
        while (std::getline(maps, line)) {
            if (line.find("---p") == std::string::npos &&
                line.find("r-xp") != std::string::npos &&
                line.find("[anon:") != std::string::npos) {
                suspicious_count++;
            }
        }
        
        return suspicious_count > 5;
    }
    
    bool detectAtexitAnomaly() {
        return detectSolistAnomaly();
    }
    
    bool detectSmapsAnomaly() {
        std::ifstream smaps("/proc/self/smaps");
        if (!smaps.is_open()) return false;
        
        std::string line;
        while (std::getline(smaps, line)) {
            if (line.find("Private_Dirty:") != std::string::npos) {
                std::istringstream iss(line);
                std::string label;
                int size;
                iss >> label >> size;
                
                if (size > 10240) {
                    return true;
                }
            }
        }
        return false;
    }
    
    bool detectModuleUnload() {
        struct stat st;
        return stat("/data/adb/modules/zygisk", &st) == 0 ||
               stat("/data/adb/modules/.zygisk", &st) == 0;
    }
    
    int getModuleUnloadCount() {
        int count = 0;
        std::ifstream maps("/proc/self/maps");
        if (!maps.is_open()) return count;
        
        std::string line;
        while (std::getline(maps, line)) {
            if (line.find("(deleted)") != std::string::npos) {
                count++;
            }
        }
        return count;
    }
    
    bool detectZygiskInjection() {
        return detectSolistAnomaly() || detectVmapAnomaly() || 
               detectModuleUnload() || detectSmapsAnomaly();
    }
    
    std::string getZygiskDetectionDetails() {
        std::stringstream ss;
        ss << "Zygisk Injection Detection:\n";
        
        if (detectSolistAnomaly()) ss << "- Solist anomaly detected\n";
        if (detectVmapAnomaly()) ss << "- Vmap anomaly detected\n";
        if (detectSmapsAnomaly()) ss << "- Smaps anomaly detected\n";
        if (detectModuleUnload()) ss << "- Module unload detected\n";
        
        int count = getModuleUnloadCount();
        if (count > 0) {
            ss << "- " << count << " deleted mappings found\n";
        }
        
        return ss.str();
    }
    
    std::vector<std::string> getZygiskFindings() {
        std::vector<std::string> findings;
        
        if (detectSolistAnomaly()) findings.push_back("Solist anomaly");
        if (detectVmapAnomaly()) findings.push_back("Vmap anomaly");
        if (detectSmapsAnomaly()) findings.push_back("Smaps anomaly");
        if (detectModuleUnload()) findings.push_back("Module unload");
        
        return findings;
    }
    
    bool isZygiskTypeDetected(const std::string& type) {
        if (type == "solist") return detectSolistAnomaly();
        if (type == "vmap") return detectVmapAnomaly();
        if (type == "atexit") return detectAtexitAnomaly();
        if (type == "smaps") return detectSmapsAnomaly();
        if (type == "module_unload") return detectModuleUnload();
        return false;
    }
    
    static int trap_fd = -1;
    
    bool setupZygiskTrapFd() {
        trap_fd = open("/proc/self/maps", O_RDONLY);
        return trap_fd >= 0;
    }
    
    bool verifyZygiskTrapFd() {
        if (trap_fd < 0) return false;
        
        struct stat st;
        if (fstat(trap_fd, &st) != 0) {
            return true;
        }
        return false;
    }
    
    std::string getZygiskTrapDetails() {
        if (trap_fd < 0) {
            return "Trap FD not initialized";
        }
        
        if (verifyZygiskTrapFd()) {
            return "Trap FD was tampered with - Zygisk detected";
        }
        
        return "Trap FD is intact";
    }
    
    void cleanupZygiskTrapFd() {
        if (trap_fd >= 0) {
            close(trap_fd);
            trap_fd = -1;
        }
    }
    
    bool isOTmpfileSupported() {
        int fd = open("/tmp", O_TMPFILE | O_RDWR, 0600);
        if (fd >= 0) {
            close(fd);
            return true;
        }
        return false;
    }
}
