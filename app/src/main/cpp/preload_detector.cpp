#include "native_detector.h"
#include <fstream>
#include <sys/stat.h>

namespace preload {
    
    static bool early_detection_run = false;
    static bool was_detected = false;
    static bool futile_hide_detected = false;
    static bool minor_dev_gap_detected = false;
    static bool mount_id_gap_detected = false;
    static bool mnt_strings_detected = false;
    static bool peer_group_gap_detected = false;
    static std::string detection_method = "";
    static std::string details = "";
    static std::vector<std::string> findings;
    static long ns_mnt_ctime_delta_ns = 0;
    static long mount_info_ctime_delta_ns = 0;
    static std::string mnt_strings_source = "";
    static std::string mnt_strings_target = "";
    
    bool hasEarlyDetectionRun() {
        return early_detection_run;
    }
    
    bool isPreloadContextValid() {
        // Check if we're running in a valid preload context
        return getenv("LD_PRELOAD") != nullptr;
    }
    
    bool nativeWasDetected() {
        if (!early_detection_run) {
            // Run early detection checks
            early_detection_run = true;
            
            // Check for various hiding techniques
            struct stat mnt_stat, mountinfo_stat;
            if (stat("/proc/self/ns/mnt", &mnt_stat) == 0 &&
                stat("/proc/self/mountinfo", &mountinfo_stat) == 0) {
                
                // Check ctime delta
                ns_mnt_ctime_delta_ns = abs(mnt_stat.st_ctim.tv_nsec - mountinfo_stat.st_ctim.tv_nsec);
                mount_info_ctime_delta_ns = ns_mnt_ctime_delta_ns;
                
                if (ns_mnt_ctime_delta_ns > 1000000) { // > 1ms
                    was_detected = true;
                    detection_method = "Ctime delta anomaly";
                }
            }
            
            // Check for mount ID gaps
            std::ifstream mountinfo("/proc/self/mountinfo");
            if (mountinfo.is_open()) {
                int prev_id = -1;
                int gap_count = 0;
                std::string line;
                
                while (std::getline(mountinfo, line)) {
                    int mount_id;
                    if (sscanf(line.c_str(), "%d", &mount_id) == 1) {
                        if (prev_id >= 0 && mount_id - prev_id > 10) {
                            gap_count++;
                        }
                        prev_id = mount_id;
                    }
                }
                
                if (gap_count > 3) {
                    mount_id_gap_detected = true;
                    was_detected = true;
                    detection_method = "Mount ID gap";
                }
            }
        }
        
        return was_detected;
    }
    
    bool nativeWasFutileHideDetected() {
        return futile_hide_detected;
    }
    
    bool nativeWasMinorDevGapDetected() {
        return minor_dev_gap_detected;
    }
    
    bool nativeWasMountIdGapDetected() {
        return mount_id_gap_detected;
    }
    
    bool nativeWasMntStringsDetected() {
        return mnt_strings_detected;
    }
    
    bool nativeWasPeerGroupGapDetected() {
        return peer_group_gap_detected;
    }
    
    std::string nativeGetDetectionMethod() {
        return detection_method;
    }
    
    std::string nativeGetDetails() {
        return details;
    }
    
    std::vector<std::string> nativeGetFindings() {
        return findings;
    }
    
    long nativeGetNsMntCtimeDeltaNs() {
        return ns_mnt_ctime_delta_ns;
    }
    
    long nativeGetMountInfoCtimeDeltaNs() {
        return mount_info_ctime_delta_ns;
    }
    
    std::string nativeGetMntStringsSource() {
        return mnt_strings_source;
    }
    
    std::string nativeGetMntStringsTarget() {
        return mnt_strings_target;
    }
    
    void nativeReset() {
        early_detection_run = false;
        was_detected = false;
        futile_hide_detected = false;
        minor_dev_gap_detected = false;
        mount_id_gap_detected = false;
        mnt_strings_detected = false;
        peer_group_gap_detected = false;
        detection_method = "";
        details = "";
        findings.clear();
        ns_mnt_ctime_delta_ns = 0;
        mount_info_ctime_delta_ns = 0;
        mnt_strings_source = "";
        mnt_strings_target = "";
    }
}
