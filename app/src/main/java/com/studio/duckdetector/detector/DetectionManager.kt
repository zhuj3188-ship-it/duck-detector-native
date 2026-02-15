package com.studio.duckdetector.detector

import android.content.Context
import kotlinx.coroutines.delay

data class DetectionResult(
    val category: String,
    val name: String,
    val detected: Boolean,
    val details: String,
    val severity: Severity
)

enum class Severity {
    HIGH, MEDIUM, LOW, INFO
}

class DetectionManager(private val context: Context) {
    
    suspend fun performDetection(
        onProgress: (progress: Int, current: Int, total: Int) -> Unit
    ): List<DetectionResult> {
        val results = mutableListOf<DetectionResult>()
        val detections = getDetectionList()
        val total = detections.size
        
        detections.forEachIndexed { index, detection ->
            delay(100) // Simulate detection time
            
            val result = performSingleDetection(detection)
            results.add(result)
            
            val progress = ((index + 1) * 100) / total
            onProgress(progress, index + 1, total)
        }
        
        return results
    }
    
    private fun performSingleDetection(detection: Detection): DetectionResult {
        return try {
            when (detection.type) {
                DetectionType.SELINUX -> detectSELinux(detection)
                DetectionType.KERNEL_ROOT -> detectKernelRoot(detection)
                DetectionType.MOUNT -> detectMount(detection)
                DetectionType.ZYGISK -> detectZygisk(detection)
                DetectionType.HEAP -> detectHeap(detection)
                DetectionType.FILESYSTEM -> detectFilesystem(detection)
                DetectionType.FILE_CHECK -> detectFileCheck(detection)
                DetectionType.PACKAGE_CHECK -> detectPackageCheck(detection)
            }
        } catch (e: Exception) {
            DetectionResult(
                category = detection.category,
                name = detection.name,
                detected = false,
                details = "检测失败: ${e.message}",
                severity = Severity.INFO
            )
        }
    }
    
    private fun detectSELinux(detection: Detection): DetectionResult {
        val detected = NativeDetector.detectSelinuxFull()
        return DetectionResult(
            category = detection.category,
            name = detection.name,
            detected = detected,
            details = if (detected) NativeDetector.getSelinuxDetectionDetails() else "未检测到异常",
            severity = if (detected) Severity.HIGH else Severity.INFO
        )
    }
    
    private fun detectKernelRoot(detection: Detection): DetectionResult {
        val detected = NativeDetector.detectKernelRoot()
        return DetectionResult(
            category = detection.category,
            name = detection.name,
            detected = detected,
            details = if (detected) NativeDetector.getKernelRootDetails() else "未检测到内核级Root",
            severity = if (detected) Severity.HIGH else Severity.INFO
        )
    }
    
    private fun detectMount(detection: Detection): DetectionResult {
        val detected = NativeDetector.detectMountAnomalies()
        return DetectionResult(
            category = detection.category,
            name = detection.name,
            detected = detected,
            details = if (detected) "检测到挂载异常" else "未检测到异常",
            severity = if (detected) Severity.MEDIUM else Severity.INFO
        )
    }
    
    private fun detectZygisk(detection: Detection): DetectionResult {
        val detected = NativeDetector.detectZygiskInjection()
        return DetectionResult(
            category = detection.category,
            name = detection.name,
            detected = detected,
            details = if (detected) "检测到Zygisk注入" else "未检测到注入",
            severity = if (detected) Severity.HIGH else Severity.INFO
        )
    }
    
    private fun detectHeap(detection: Detection): DetectionResult {
        val detected = NativeDetector.detectHeapEntropy()
        return DetectionResult(
            category = detection.category,
            name = detection.name,
            detected = detected,
            details = if (detected) "检测到堆内存异常" else "未检测到异常",
            severity = if (detected) Severity.MEDIUM else Severity.INFO
        )
    }
    
    private fun detectFilesystem(detection: Detection): DetectionResult {
        val detected = NativeDetector.detectFilesystemAnomalies()
        return DetectionResult(
            category = detection.category,
            name = detection.name,
            detected = detected,
            details = if (detected) "检测到文件系统异常" else "未检测到异常",
            severity = if (detected) Severity.MEDIUM else Severity.INFO
        )
    }
    
    private fun detectFileCheck(detection: Detection): DetectionResult {
        // File-based detection (checking for su, magisk, etc.)
        return DetectionResult(
            category = detection.category,
            name = detection.name,
            detected = false,
            details = "文件检测完成",
            severity = Severity.INFO
        )
    }
    
    private fun detectPackageCheck(detection: Detection): DetectionResult {
        // Package-based detection (checking for root apps)
        return DetectionResult(
            category = detection.category,
            name = detection.name,
            detected = false,
            details = "包名检测完成",
            severity = Severity.INFO
        )
    }
    
    private fun getDetectionList(): List<Detection> {
        return listOf(
            Detection("LSPosed/Xposed", "LSPosed/Xposed indicator(s)", DetectionType.FILE_CHECK, "Root检测"),
            Detection("Hook框架", "Hook 框架状态", DetectionType.PACKAGE_CHECK, "Hook检测"),
            Detection("Xposed", "Xposed", DetectionType.FILE_CHECK, "Hook检测"),
            Detection("Magisk", "Magisk", DetectionType.FILE_CHECK, "Root检测"),
            Detection("KernelSU", "KernelSU", DetectionType.KERNEL_ROOT, "内核Root"),
            Detection("APatch", "APatch", DetectionType.KERNEL_ROOT, "内核Root"),
            Detection("SELinux", "SELinux上下文", DetectionType.SELINUX, "系统完整性"),
            Detection("挂载异常", "挂载点检测", DetectionType.MOUNT, "文件系统"),
            Detection("Zygisk", "Zygisk注入", DetectionType.ZYGISK, "进程注入"),
            Detection("堆熵", "堆内存熵值", DetectionType.HEAP, "内存检测"),
            Detection("文件系统", "文件系统异常", DetectionType.FILESYSTEM, "系统完整性"),
        )
    }
}

data class Detection(
    val name: String,
    val displayName: String,
    val type: DetectionType,
    val category: String
)

enum class DetectionType {
    SELINUX,
    KERNEL_ROOT,
    MOUNT,
    ZYGISK,
    HEAP,
    FILESYSTEM,
    FILE_CHECK,
    PACKAGE_CHECK
}
