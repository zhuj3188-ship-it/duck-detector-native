# Duck Detector Native - 开发任务清单

## 已完成
- [x] 创建原生Android项目结构（Kotlin + JNI/NDK）
- [x] 配置GitHub Actions自动构建
- [x] 提取并替换原APK的真实图标

## 核心Root检测功能（173个JNI函数）
- [ ] 实现SELinux上下文检测
- [ ] 实现KernelSU/APatch检测
- [ ] 实现Zygisk注入检测
- [ ] 实现挂载异常检测
- [ ] 实现文件描述符陷阱
- [ ] 实现内存异常检测
- [ ] 实现Root管理工具检测（Magisk、SuperSU、KingRoot）
- [ ] 实现Hook框架检测（LSPosed、Xposed、EdXposed、Frida）
- [ ] 实现系统完整性检测（Boot Integrity、System Partition）
- [ ] 实现危险二进制文件检测
- [ ] 实现危险应用扫描
- [ ] 实现审计日志完整性检测
- [ ] 实现TEE状态检测
- [ ] 实现SafetyNet检测

## UI界面还原
- [ ] 实现欢迎引导页面（使用须知对话框）
- [ ] 实现测试版本警告对话框
- [ ] 实现主扫描界面
- [ ] 实现扫描动画（旋转图标）
- [ ] 实现进度条显示
- [ ] 实现检测结果卡片（可展开）
- [ ] 实现问题检测提示对话框
- [ ] 实现设置页面
- [ ] 匹配原版颜色方案
- [ ] 实现所有动画效果

## 构建和测试
- [ ] 修复当前GitHub Actions构建错误
- [ ] 本地测试APK功能
- [ ] 优化性能
- [ ] 生成最终发布版APK
