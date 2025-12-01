# 快速开始指南 - 日地月系统（带纹理和光照）

## 🚀 最简单的方法（推荐）

### 直接运行已编译程序

```bash
# 在项目根目录下运行
run.bat

# 或者进入bin目录运行
cd build\bin
.\SunEarthMoon.exe
```

**注意**: 程序必须从 `build\bin` 目录运行，因为它需要访问同目录下的 `shaders/` 和 `textures/` 文件夹。

## 📦 重新编译

如果需要修改代码后重新编译：

```bash
# 方法1: 使用重新构建脚本（推荐）
rebuild.bat

# 方法2: 手动编译
cd D:\homework\graphics\ex2
rm -f CMakeCache.txt
rm -rf build
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build . --config Release
```

## 🎨 新功能说明

### 纹理系统
- **地球纹理**: 蓝绿色，显示海洋和陆地
- **月球纹理**: 灰色，显示陨石坑表面
- **太阳纹理**: 黄橙色，显示耀斑效果

所有纹理都是程序自动生成的BMP文件（位于 `textures/` 目录）

### 双光源光照
- **主光源**: 位于太阳中心 (0,0,0)，照亮地球和月球
- **背光源**: 位于太阳侧后方 (-30,20,-30)，增强太阳的显示效果
- **Phong光照模型**: 环境光 + 漫反射 + 镜面反射 + 距离衰减

## 🎮 操作说明

### 相机控制
- **W/S/A/D**: 前后左右移动
- **Space**: 上升
- **Shift**: 下降
- **鼠标移动**: 旋转视角
- **ESC**: 退出程序

### 速度控制
- **上箭头/下箭头**: 加快/减慢动画速度
- **鼠标滚轮**: 调整动画速度

## 📁 文件结构

程序运行时需要以下文件：

```
build/bin/
├── SunEarthMoon.exe          # 可执行文件（519KB）
├── shaders/                  # 着色器文件夹
│   ├── vertex_shader.glsl    # 顶点着色器
│   └── fragment_shader.glsl  # 片段着色器
└── textures/                 # 纹理文件夹
    ├── earth.bmp             # 地球纹理（768KB）
    ├── moon.bmp              # 月球纹理（768KB）
    └── sun.bmp               # 太阳纹理（768KB）
```

**重要**: 不要移动 `SunEarthMoon.exe`，必须在 `build\bin` 目录下运行！

## 🔧 前置要求（仅首次编译需要）

1. **CMake** 3.10+ (https://cmake.org/download/)
2. **MinGW-w64** GCC 8.1.0+ (https://github.com/niXman/mingw-builds-binaries/releases)
3. **Git** (用于下载依赖库)

### 依赖库（已包含在项目中）
- GLFW 3.x（窗口管理）
- GLM（数学库）
- GLAD（OpenGL加载器）
- 自定义BMP加载器（纹理加载）

## ⚠️ 集成显卡优化

针对**没有独立显卡**的情况，本程序已优化：

1. ✅ 低多边形球体（20段细分）
2. ✅ 简化的光照计算
3. ✅ 无抗锯齿和后处理
4. ✅ 固定分辨率 1280x720

**预期性能**: 在集成显卡上可达到 60 FPS

## 🆘 常见问题

### Q: 运行时提示找不到着色器或纹理文件
**A**: 确保从 `build\bin` 目录运行程序，不要移动exe文件。

### Q: 黑屏或全黑显示
**A**:
1. 检查是否看到纹理加载成功的消息
2. 更新显卡驱动
3. 确认OpenGL版本支持（需要3.3+）

### Q: 编译时提示找不到CMake缓存
**A**:
```bash
cd D:\homework\graphics\ex2
rm -f CMakeCache.txt
rm -rf build
rebuild.bat
```

### Q: 纹理文件不存在
**A**:
```bash
# 重新生成纹理
cd D:\homework\graphics\ex2
.\generate_textures.exe
```

### Q: 程序无法启动，提示缺少DLL
**A**: 将以下DLL复制到exe同目录（从MinGW的bin目录）：
- libgcc_s_seh-1.dll
- libstdc++-6.dll
- libwinpthread-1.dll

### Q: 帧率很低
**A**:
1. 关闭其他占用GPU的程序
2. 降低窗口分辨率（修改 `main.cpp` 中的 `SCR_WIDTH` 和 `SCR_HEIGHT`）
3. 减少球体细分（修改 `createSphere` 函数的参数从20改为15）

## 🎓 实验报告检查清单

### 基础要求（实验一）
- [x] 使用 OpenGL 3.3+ Core Profile
- [x] 地球绕太阳公转（XZ平面圆轨道）
- [x] 月球绕地球公转
- [x] 轨道不共面（月球轨道倾斜15°）
- [x] 相对速度合理
- [x] 3D透视投影
- [x] 自由视角相机
- [x] 光照效果

### 新增要求（实验二）
- [x] **球体纹理贴图**
  - 地球有纹理（蓝绿色海陆）
  - 月球有纹理（灰色陨石坑）
  - 太阳有纹理（黄橙色耀斑）
- [x] **光照处理**
  - 光源设在太阳位置
  - Phong光照模型
  - 距离衰减
- [x] **双光源系统**
  - 主光源照亮行星
  - 背光源增强太阳显示效果

## 📊 技术特性

### 纹理系统
- **格式**: BMP 24位真彩色
- **分辨率**: 512x512
- **UV映射**: 球面坐标映射
- **过滤**: Linear Mipmap过滤
- **自动生成**: 使用 `generate_textures.cpp` 生成

### 光照系统
- **模型**: Phong光照
- **环境光**: 0.15强度
- **漫反射**: 基于法线和光线方向
- **镜面反射**: 0.4强度，32光泽度
- **衰减**: 1.0 / (1.0 + 0.003*d + 0.00005*d²)

### 着色器
- **顶点着色器**: 处理位置、法线、纹理坐标
- **片段着色器**:
  - 纹理采样
  - 双光源计算
  - Phong光照
  - 太阳自发光特殊处理

## 💾 提交清单

确保提交以下内容：

1. **源代码**
   - `src/main.cpp`
   - `shaders/vertex_shader.glsl`
   - `shaders/fragment_shader.glsl`
   - `generate_textures.cpp`
   - `CMakeLists.txt`

2. **可执行文件包**（整个 `build/bin` 目录）
   - `SunEarthMoon.exe`
   - `shaders/` 文件夹
   - `textures/` 文件夹

3. **运行截图**（3-5张不同角度）

4. **文档**
   - `README.md`
   - `QUICKSTART.md`（本文件）

## 🎯 快速测试

运行后应该看到：

```
Texture loaded successfully: textures/earth.bmp (512x512)
Texture loaded successfully: textures/moon.bmp (512x512)
Texture loaded successfully: textures/sun.bmp (512x512)
```

然后出现窗口显示：
- 中间的黄色太阳（带纹理）
- 绕太阳公转的蓝色地球（带纹理）
- 绕地球公转的灰色月球（带纹理）
- 明暗分明的光照效果

## 🚀 性能提示

在集成显卡上获得最佳性能：

1. **降低分辨率**: 改为 1024x576
2. **减少细分**: 球体段数改为 15
3. **简化光照**: 移除背光源（如果需要）
4. **关闭垂直同步**: 在驱动设置中

## 📞 需要帮助？

如果遇到问题：
1. 检查README.md的"常见问题"部分
2. 确保所有文件结构正确
3. 验证MinGW和CMake已正确安装
4. 确认显卡驱动是最新版本
