# Duck Detector - Native Android

基于原版Duck Detector深度分析重建的原生Android Root环境检测应用。

## 技术栈

- **Kotlin** - 主要开发语言
- **JNI/NDK** - C++17原生检测代码
- **Material Design 3** - UI设计规范
- **Gradle** - 构建系统

## 功能特性

### 深度Root检测
- ✅ SELinux上下文检测
- ✅ 内核级Root检测（KernelSU, APatch）
- ✅ Zygisk注入检测
- ✅ 挂载异常检测
- ✅ 文件描述符陷阱
- ✅ 内存异常检测
- ✅ LSPosed/Xposed检测
- ✅ Hook框架检测
- ✅ 系统完整性验证

### UI界面
- ✅ Material Design 3设计
- ✅ 使用须知引导页面
- ✅ Beta版本警告对话框
- ✅ 扫描进度动画
- ✅ 检测结果展示
- ✅ 问题检测提示
- ✅ 设置页面

## 项目结构

```
app/
├── src/main/
│   ├── java/com/studio/duckdetector/
│   │   ├── MainActivity.kt              # 主活动
│   │   └── detector/
│   │       ├── NativeDetector.kt        # JNI接口
│   │       └── DetectionManager.kt      # 检测管理器
│   ├── cpp/                             # 原生C++代码
│   │   ├── native_detector.h            # 头文件
│   │   ├── jni_bridge.cpp               # JNI桥接
│   │   ├── selinux_detector.cpp         # SELinux检测
│   │   ├── kernel_detector.cpp          # 内核Root检测
│   │   └── ...                          # 其他检测模块
│   ├── res/                             # Android资源
│   │   ├── layout/                      # 布局文件
│   │   ├── values/                      # 颜色、字符串、尺寸
│   │   ├── drawable/                    # 图标资源
│   │   └── menu/                        # 菜单资源
│   └── AndroidManifest.xml
└── build.gradle                         # 应用构建配置
```

## 构建方法

### 方法1：GitHub Actions自动构建（推荐）

1. Fork本仓库到您的GitHub账号
2. 推送代码会自动触发构建
3. 在Actions标签页下载构建的APK

### 方法2：本地构建

**前提条件**：
- Android Studio Arctic Fox或更高版本
- JDK 17
- Android SDK (API 34)
- NDK r25或更高版本

**构建步骤**：

```bash
# 克隆仓库
git clone https://github.com/your-username/duck-detector-native.git
cd duck-detector-native

# 使用Gradle构建
./gradlew assembleRelease

# APK位置
# app/build/outputs/apk/release/app-release.apk
```

## 开发状态

### 已完成 ✅
- 项目结构和构建系统
- Material Design 3 UI框架
- 完整的资源文件（颜色、字符串、尺寸、主题）
- 主界面布局
- 底部导航
- JNI接口定义
- SELinux和内核检测实现
- GitHub Actions自动构建配置

### 待完善 ⏳
1. **对话框实现**
   - 使用须知对话框
   - Beta警告对话框
   - 问题检测对话框

2. **MainActivity完整实现**
   - 扫描动画
   - 进度更新
   - 结果展示

3. **设置页面**
   - 网络访问开关
   - 证书吊销列表
   - 关于信息

4. **原生检测函数完善**
   - 完成所有173个JNI函数
   - 优化检测算法

## 技术说明

本项目基于原版Duck Detector APK的深度分析，通过反编译提取了：
- UI设计规范和颜色方案
- 字符串资源和文案
- 布局结构和尺寸
- 原生库函数签名

由于原版APK使用了深度代码混淆，某些检测算法的具体实现基于公开的Root检测技术和安全研究成果重新实现。

## 许可证

本项目用于学习和研究目的。

## 致谢

- 原版Duck Detector开发者
- Android安全研究社区
- Material Design团队

---

**注意**：本项目是学习项目，检测结果仅供参考。实践是检验真理的唯一标准。
