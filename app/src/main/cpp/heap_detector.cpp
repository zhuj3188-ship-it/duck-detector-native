#include "native_detector.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

namespace heap {
    
    bool detectHeapEntropy() {
        // Check heap randomization by allocating memory and checking addresses
        void* ptr1 = malloc(1024);
        void* ptr2 = malloc(1024);
        void* ptr3 = malloc(1024);
        
        if (!ptr1 || !ptr2 || !ptr3) {
            if (ptr1) free(ptr1);
            if (ptr2) free(ptr2);
            if (ptr3) free(ptr3);
            return false;
        }
        
        // Calculate address differences
        long diff1 = (char*)ptr2 - (char*)ptr1;
        long diff2 = (char*)ptr3 - (char*)ptr2;
        
        free(ptr1);
        free(ptr2);
        free(ptr3);
        
        // If differences are too predictable, ASLR might be disabled
        if (diff1 == diff2) {
            return true; // Suspicious - heap is too predictable
        }
        
        return false;
    }
    
    std::string getHeapEntropyDetails() {
        if (detectHeapEntropy()) {
            return "Heap entropy is low - possible ASLR bypass or memory manipulation";
        }
        return "Heap entropy appears normal";
    }
}
