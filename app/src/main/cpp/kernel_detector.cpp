#include "native_detector.h"
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>

namespace kernel {

bool detectKernelRoot() {
    // Check for kernel-level root modifications
    return detectKernelSu() || detectAPatch();
}

bool detectKernelSu() {
    // Check for KernelSU presence
    struct stat st;
    
    // Check for KernelSU kernel module
    if (stat("/dev/ksu", &st) == 0) {
        return true;
    }
    
    // Check for KernelSU in kernel version
    std::ifstream version("/proc/version");
    if (version.is_open()) {
        std::string line;
        std::getline(version, line);
        if (line.find("KernelSU") != std::string::npos) {
            return true;
        }
    }
    
    return false;
}

bool detectAPatch() {
    // Check for APatch presence
    struct stat st;
    
    // Check for APatch markers
    if (stat("/dev/apatch", &st) == 0) {
        return true;
    }
    
    // Check kernel version for APatch
    std::ifstream version("/proc/version");
    if (version.is_open()) {
        std::string line;
        std::getline(version, line);
        if (line.find("APatch") != std::string::npos) {
            return true;
        }
    }
    
    return false;
}

std::string getKernelRootDetails() {
    std::string details = "Kernel Root Detection:\n";
    
    if (detectKernelSu()) {
        details += "- KernelSU detected\n";
    }
    
    if (detectAPatch()) {
        details += "- APatch detected\n";
    }
    
    return details;
}

std::vector<std::string> getKernelRootFindings() {
    std::vector<std::string> findings;
    
    if (detectKernelSu()) {
        findings.push_back("KernelSU detected");
    }
    
    if (detectAPatch()) {
        findings.push_back("APatch detected");
    }
    
    return findings;
}

std::string getKernelRootDetectionMethod() {
    if (detectKernelSu()) {
        return "KernelSU device node detection";
    }
    if (detectAPatch()) {
        return "APatch device node detection";
    }
    return "No kernel root detected";
}

bool isKernelRootTypeDetected(const std::string& type) {
    if (type == "kernelsu") {
        return detectKernelSu();
    }
    if (type == "apatch") {
        return detectAPatch();
    }
    return false;
}

bool detectSusfs() {
    // Check for Susfs (hiding filesystem)
    struct stat st;
    return stat("/dev/susfs", &st) == 0;
}

std::string getSusfsDetails() {
    if (detectSusfs()) {
        return "Susfs hiding filesystem detected";
    }
    return "No Susfs detected";
}

bool wasSusfsChildKilled() {
    // This would require tracking child processes
    // Simplified implementation
    return false;
}

} // namespace kernel
