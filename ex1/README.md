# 日地月运动模型 (Sun-Earth-Moon System)

一个使用 OpenGL 3.3+ 实现的日地月三体运动系统动画程序。

## 功能特点

✨ **运动模型**
- 地球绕太阳公转（XZ平面圆轨道）
- 月球绕地球公转（倾斜15°的轨道，非共面）
- 地球自转
- 真实的相对速度关系

✨ **视觉效果**
- 太阳自发光效果
- Phong光照模型（环境光、漫反射、镜面反射）
- 距离衰减光照
- 自由视角相机

✨ **性能优化**
- **适配集成显卡**：使用低多边形球体（20段）
- 简化的光照计算
- 无复杂后处理效果
- 稳定60FPS（在集成显卡上）

## 系统要求

- **操作系统**：Windows 10/11
- **显卡**：支持 OpenGL 3.3+ 的集成显卡或独立显卡
  - Intel HD Graphics 4000 或更高
  - AMD Radeon HD 系列
  - NVIDIA GeForce 8 系列或更高
- **编译器**：支持 C++11 的编译器（推荐 MinGW-w64 或 MSVC）
- **CMake**：3.10 或更高版本

## 快速开始

### 方法一：使用预编译版本（推荐）

如果提供了预编译的可执行文件：

1. 解压到任意目录
2. 双击 `SunEarthMoon.exe` 运行

### 方法二：从源码编译

#### 准备工作

1. **安装 CMake**
   - 下载：https://cmake.org/download/
   - 安装时勾选"Add CMake to system PATH"

2. **安装编译器**
   - **选项A（推荐）**：MinGW-w64
     - 下载：https://github.com/niXman/mingw-builds-binaries/releases
     - 下载 `x86_64-*-release-posix-seh-*.7z`
     - 解压到 `C:\mingw64`
     - 添加 `C:\mingw64\bin` 到系统PATH

   - **选项B**：Visual Studio 2019/2022
     - 安装时选择"使用C++的桌面开发"

3. **下载第三方库**

   在项目根目录执行：
   ```bash
   # 创建external目录
   mkdir external
   cd external

   # 下载GLFW
   git clone https://github.com/glfw/glfw.git

   # 下载GLM
   git clone https://github.com/g-truc/glm.git

   # 创建GLAD目录结构
   mkdir -p glad/include/glad
   mkdir -p glad/include/KHR
   mkdir -p glad/src
   ```

   然后访问 https://glad.dav1d.de/
   - Language: C/C++
   - Specification: OpenGL
   - Profile: Core
   - API gl: Version 3.3 或更高
   - 点击 GENERATE
   - 下载zip文件，将内容放入 `external/glad/` 目录

#### 编译步骤

```bash
# 1. 回到项目根目录
cd D:\homework\graphics\ex1

# 2. 创建构建目录
mkdir build
cd build

# 3. 配置CMake（MinGW）
cmake -G "MinGW Makefiles" ..
# 或者（Visual Studio）
cmake -G "Visual Studio 17 2022" ..

# 4. 编译
cmake --build . --config Release

# 5. 运行
cd D:\homework\graphics\ex1
.\bin\SunEarthMoon.exe
```

## 操作说明

### 相机控制
- **W/S/A/D**：前后左右移动
- **Space/Shift**：上升/下降
- **鼠标移动**：旋转视角
- **ESC**：退出程序

### 速度控制
- **上箭头/下箭头**：加快/减慢动画速度
- **鼠标滚轮**：调整动画速度

## 技术实现

### 运动参数

```cpp
// 地球
轨道半径: 50 单位
公转周期: 约 12.6 秒（速度系数 0.5）
自转周期: 约 3.1 秒（速度系数 2.0）
半径: 3 单位

// 月球
轨道半径: 8 单位（相对地球）
公转周期: 约 3.1 秒（速度系数 2.0）
轨道倾角: 15°（相对地球轨道平面）
半径: 1 单位

// 太阳
半径: 10 单位
```

### 轨道平面

- **地球轨道**：XZ平面 (Y=0)
- **月球轨道**：倾斜15°的平面
  - X分量：`moonOrbitRadius * cos(angle)`
  - Y分量：`moonOrbitRadius * sin(angle) * sin(15°)` ← 倾斜效果
  - Z分量：`moonOrbitRadius * sin(angle) * cos(15°)`

### 光照模型

使用 Phong 光照模型：
- **环境光**：0.1 强度
- **漫反射**：基于光源方向和法线
- **镜面反射**：0.3 强度，32 光泽度
- **距离衰减**：二次衰减函数

## 性能优化说明

针对**没有独立显卡**的情况，本程序做了以下优化：

1. **低多边形模型**：球体使用20段细分（而非常见的50段）
2. **简化光照**：单一光源，无阴影
3. **无抗锯齿**：避免MSAA开销
4. **固定分辨率**：1280x720，在集成显卡上流畅运行
5. **批量渲染**：复用同一球体VAO

预期性能：
- **集成显卡**：60 FPS @ 1280x720
- **独立显卡**：60+ FPS @ 更高分辨率

## 项目结构

```
ex1/
├── src/
│   └── main.cpp              # 主程序
├── shaders/
│   ├── vertex_shader.glsl    # 顶点着色器
│   └── fragment_shader.glsl  # 片段着色器
├── external/                 # 第三方库
│   ├── glfw/                 # 窗口管理
│   ├── glad/                 # OpenGL加载器
│   └── glm/                  # 数学库
├── build/                    # 构建目录
├── CMakeLists.txt           # CMake配置
└── README.md                # 本文件
```

## 常见问题

### Q: 程序无法启动，提示缺少DLL
**A**: 确保MinGW的bin目录在系统PATH中，或将以下DLL复制到exe同目录：
- `libgcc_s_seh-1.dll`
- `libstdc++-6.dll`
- `libwinpthread-1.dll`

### Q: 编译时找不到OpenGL
**A**: Windows上OpenGL通常随显卡驱动安装。更新显卡驱动后重试。

### Q: 帧率很低
**A**:
1. 检查是否使用了独立显卡（笔记本双显卡用户）
2. 降低窗口分辨率（修改 `SCR_WIDTH` 和 `SCR_HEIGHT`）
3. 减少球体细分（`createSphere` 第三个参数改为 15 或 10）

### Q: 画面全黑
**A**:
1. 检查 `shaders/` 目录是否在exe同级目录
2. 查看控制台是否有着色器编译错误
3. 更新显卡驱动

## 实验报告要点

### 1. 运动关系
- ✅ 地球绕太阳公转（XZ平面）
- ✅ 月球绕地球公转（倾斜平面）
- ✅ 轨道不共面（15°倾角）
- ✅ 相对速度合理（月球比地球转得快）

### 2. 视觉效果
- ✅ 太阳发光
- ✅ 行星受光照影响
- ✅ 3D透视投影
- ✅ 自由视角

### 3. 技术要求
- ✅ OpenGL 3.3 Core Profile
- ✅ 现代着色器（GLSL 330）
- ✅ VAO/VBO/EBO
- ✅ 矩阵变换

## 作者

实验项目 - 计算机图形学

## 许可

仅供学习使用
