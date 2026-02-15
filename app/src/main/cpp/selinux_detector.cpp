#include "native_detector.h"
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <sys/stat.h>

namespace selinux {

std::string getSelfSelinuxContext() {
    std::ifstream file("/proc/self/attr/current");
    if (!file.is_open()) {
        return "unknown";
    }
    
    std::string context;
    std::getline(file, context);
    return context;
}

bool getSelinuxEnforceStatus() {
    std::ifstream file("/sys/fs/selinux/enforce");
    if (!file.is_open()) {
        return false;
    }
    
    int enforce = 0;
    file >> enforce;
    return enforce == 1;
}

bool hasSuspiciousSelfContext() {
    std::string context = getSelfSelinuxContext();
    
    // Check for suspicious contexts
    if (context.find("magisk") != std::string::npos ||
        context.find("init") != std::string::npos ||
        context.find("su") != std::string::npos ||
        context.find("shell") != std::string::npos) {
        return true;
    }
    
    return false;
}

std::vector<std::string> scanProcessSelinuxContexts() {
    std::vector<std::string> suspicious;
    
    // Scan /proc for suspicious process contexts
    // This is a simplified implementation
    // Full implementation would iterate through /proc/*/attr/current
    
    return suspicious;
}

bool detectSelinuxFull() {
    // Comprehensive SELinux detection
    if (hasSuspiciousSelfContext()) {
        return true;
    }
    
    if (!getSelinuxEnforceStatus()) {
        // SELinux is in permissive mode - suspicious
        return true;
    }
    
    return false;
}

bool hasRootSelinuxContext() {
    std::string context = getSelfSelinuxContext();
    return context.find(":r:su:") != std::string::npos ||
           context.find(":r:magisk:") != std::string::npos;
}

std::string getSelinuxDetectionDetails() {
    std::ostringstream details;
    details << "SELinux Context: " << getSelfSelinuxContext() << "\n";
    details << "Enforce Status: " << (getSelinuxEnforceStatus() ? "Enforcing" : "Permissive") << "\n";
    details << "Suspicious Context: " << (hasSuspiciousSelfContext() ? "Yes" : "No");
    return details.str();
}

} // namespace selinux
