#include "native_detector.h"
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

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
    
    DIR* dir = opendir("/proc");
    if (!dir) return suspicious;
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        // Check if directory name is numeric (PID)
        if (entry->d_type != DT_DIR) continue;
        
        std::string pid = entry->d_name;
        if (pid.empty() || !isdigit(pid[0])) continue;
        
        std::string context_path = "/proc/" + pid + "/attr/current";
        std::ifstream file(context_path);
        if (!file.is_open()) continue;
        
        std::string context;
        std::getline(file, context);
        
        // Check for suspicious contexts
        if (context.find("u:r:su:") != std::string::npos ||
            context.find("u:r:magisk:") != std::string::npos ||
            context.find("u:r:init:") != std::string::npos) {
            suspicious.push_back("PID " + pid + ": " + context);
        }
    }
    
    closedir(dir);
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
    details << "Suspicious Context: " << (hasSuspiciousSelfContext() ? "Yes" : "No") << "\n";
    
    auto findings = scanProcessSelinuxContexts();
    if (!findings.empty()) {
        details << "Suspicious Processes:\n";
        for (const auto& finding : findings) {
            details << "  " << finding << "\n";
        }
    }
    
    return details.str();
}

} // namespace selinux
