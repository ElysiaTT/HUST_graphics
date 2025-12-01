# 快速开始指南

## 🚀 最简单的方法（无需编译）

如果你想直接运行程序而不编译：

### 使用在线版本或预编译包
由于你的电脑没有独立显卡，我建议：

1. **使用WebGL版本**（推荐）
   - 访问在线平台如 Shadertoy、CodePen 运行类似效果
   - 无需安装，浏览器即可运行

2. **使用软件渲染**
   - 下载 Mesa3D 软件OpenGL实现
   - 网址：https://github.com/pal1000/mesa-dist-win/releases
   - 下载后解压，将 `opengl32.dll` 放在程序同目录

## 📦 从源码编译

### 前置要求

1. **安装 CMake** (https://cmake.org/download/)
2. **安装 MinGW-w64** (https://github.com/niXman/mingw-builds-binaries/releases)
   - 下载 `x86_64-*-posix-seh-*.7z`
   - 解压到 `C:\mingw64`
   - 添加 `C:\mingw64\bin` 到系统 PATH

3. **安装 Git** (https://git-scm.com/)

### 一键安装步骤

```bash
# 1. 下载依赖
setup_dependencies.bat

# 2. 按照提示从 https://glad.dav1d.de/ 下载GLAD文件

# 3. 编译项目
build.bat

# 4. 运行程序
cd build\bin
SunEarthMoon.exe
```

## 🎮 操作说明

- **W/A/S/D**: 移动相机
- **鼠标**: 旋转视角
- **上/下箭头**: 调整动画速度
- **ESC**: 退出

## ⚠️ 集成显卡优化提示

如果遇到性能问题：

1. 关闭其他占用GPU的程序
2. 降低窗口分辨率（修改 `main.cpp` 中的 `SCR_WIDTH` 和 `SCR_HEIGHT`）
3. 使用软件渲染（Mesa3D）

## 🆘 常见问题

**Q: 黑屏或闪退？**
- 更新显卡驱动
- 尝试使用 Mesa3D 软件渲染

**Q: 编译失败？**
- 确保所有依赖都已正确下载
- 检查 GLAD 文件是否在正确位置

**Q: 帧率低？**
- 这是正常的，集成显卡性能有限
- 尝试降低分辨率或减少球体细节

## 📁 文件清单

```
必需文件：
- src/main.cpp                 # 主程序源码
- shaders/vertex_shader.glsl   # 顶点着色器
- shaders/fragment_shader.glsl # 片段着色器
- CMakeLists.txt               # 构建配置

运行必需：
- SunEarthMoon.exe             # 可执行文件
- shaders/ 目录                # 着色器文件必须在exe旁边
```

## 🎓 实验报告检查清单

- [x] 使用 OpenGL 3.0+ 版本
- [x] 地球绕太阳运动（圆轨道）
- [x] 月亮绕地球运动（圆轨道）
- [x] 轨道不在同一平面（月球轨道倾斜15°）
- [x] 相对速度合理（月球公转速度 > 地球公转速度）
- [x] 包含光照效果
- [x] 3D透视投影
- [x] 可交互视角

## 💡 替代方案（如果编译困难）

如果编译过程太复杂，你可以：

1. **使用 Processing** (更简单的图形库)
   ```java
   // 用Java编写，更容易运行
   ```

2. **使用 Three.js** (WebGL，浏览器运行)
   ```javascript
   // 无需编译，直接在浏览器打开HTML文件
   ```

3. **使用 Python + Pygame/PyOpenGL**
   ```python
   # Python更容易安装和运行
   ```

需要这些替代方案的代码吗？我可以为你生成！
