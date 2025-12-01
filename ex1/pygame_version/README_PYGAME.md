# Pygame 简化版 - 安装和运行指南

## 🎯 为什么选择这个版本？

如果你的电脑**没有独立显卡**，这个Pygame版本是**最佳选择**：

✅ **安装简单** - 只需要Python和一个库
✅ **运行流畅** - 在集成显卡上也能稳定60FPS
✅ **功能完整** - 满足所有实验要求
✅ **易于修改** - Python代码简单易懂

## 📦 安装步骤

### 1. 安装Python

下载并安装Python 3.8或更高版本：
- 官网：https://www.python.org/downloads/
- **重要**：安装时勾选 "Add Python to PATH"

验证安装：
```bash
python --version
```

### 2. 安装Pygame

打开命令提示符（CMD），运行：
```bash
pip install pygame
```

如果速度慢，可以使用国内镜像：
```bash
pip install pygame -i https://pypi.tuna.tsinghua.edu.cn/simple
```

### 3. 运行程序

```bash
cd D:\homework\graphics\sun\pygame_version
python sun_earth_moon_pygame.py
```

## 🎮 操作说明

| 按键 | 功能 |
|------|------|
| **↑ / ↓** | 加速/减速动画 |
| **空格** | 暂停/继续 |
| **H** | 显示/隐藏帮助 |
| **ESC** | 退出程序 |

## ✨ 功能特性

### 满足实验要求：

1. ✅ **运动关系正确**
   - 地球绕太阳公转（XZ平面模拟）
   - 月球绕地球公转（倾斜15°）

2. ✅ **相对速度合理**
   - 地球公转速度：0.3 rad/s
   - 月球公转速度：1.2 rad/s（4倍于地球）
   - 地球自转速度：2.0 rad/s

3. ✅ **轨道非共面**
   - 地球轨道：XY平面（屏幕平面）
   - 月球轨道：倾斜15°（通过Y轴缩放模拟）

4. ✅ **视觉效果**
   - 太阳辉光效果
   - 天体光照高光
   - 地球自转指示线
   - 轨道显示
   - 实时FPS和速度显示

## 📊 性能对比

| 版本 | 安装难度 | 运行要求 | 视觉效果 | 推荐度 |
|------|---------|---------|---------|--------|
| **Pygame版** | ⭐ | 集成显卡 | ⭐⭐⭐ | ⭐⭐⭐⭐⭐ |
| OpenGL版 | ⭐⭐⭐⭐⭐ | 独立显卡 | ⭐⭐⭐⭐⭐ | ⭐⭐ |

## 🛠️ 自定义参数

在代码中可以轻松修改这些参数：

```python
# 速度调整
EARTH_ORBIT_SPEED = 0.3    # 地球公转速度
MOON_ORBIT_SPEED = 1.2     # 月球公转速度

# 轨道大小
EARTH_ORBIT_RADIUS = 200   # 地球轨道半径
MOON_ORBIT_RADIUS = 40     # 月球轨道半径

# 倾角
MOON_TILT = 15             # 月球轨道倾斜角度

# 天体大小
SUN_RADIUS = 30
EARTH_RADIUS = 12
MOON_RADIUS = 5
```

## 📸 截图功能

添加截图功能（在代码中添加）：

```python
# 在事件处理部分添加
elif event.key == pygame.K_F12:
    pygame.image.save(screen, f"screenshot_{int(time)}.png")
    print("Screenshot saved!")
```

## 🆘 常见问题

### Q: pip不是内部或外部命令
**A**: Python没有添加到PATH，重新安装Python并勾选"Add to PATH"

### Q: 导入pygame失败
**A**:
```bash
# 方法1：升级pip
python -m pip install --upgrade pip
pip install pygame

# 方法2：使用conda（如果安装了Anaconda）
conda install pygame
```

### Q: 窗口闪退
**A**: 从命令行运行，查看错误信息

### Q: 帧率不稳定
**A**: 关闭其他占用CPU的程序

## 📝 实验报告要点

### 技术实现
- **语言**: Python 3.x
- **图形库**: Pygame
- **渲染方式**: 2D + 透视模拟

### 运动模型
- 地球轨道：圆形，半径200像素
- 月球轨道：圆形，半径40像素，倾斜15°
- 速度比：月球公转速度是地球的4倍

### 数学原理
```python
# 地球位置（XY平面）
earth_x = center_x + R * cos(θ)
earth_y = center_y + R * sin(θ)

# 月球位置（倾斜平面）
moon_x = earth_x + r * cos(φ)
moon_y = earth_y + r * sin(φ) * cos(15°)  # 倾斜效果
```

## 🎓 对比OpenGL版本

| 特性 | Pygame版 | OpenGL版 |
|------|----------|----------|
| 3D效果 | 模拟 | 真实3D |
| 光照 | 简化 | Phong模型 |
| 性能要求 | 低 | 高 |
| 代码复杂度 | 简单 | 复杂 |
| 安装难度 | 容易 | 困难 |

## 💡 扩展建议

想要更好的效果？可以添加：
1. 轨道轨迹线
2. 更多行星
3. 背景星空
4. 时间缩放UI
5. 轨道参数调节器

## ✅ 完整性检查

运行前确认：
- [x] Python 3.8+ 已安装
- [x] Pygame 已安装
- [x] 代码文件在正确位置
- [x] 从命令行运行（不要双击）

全部完成？运行命令：
```bash
python sun_earth_moon_pygame.py
```

祝实验成功！ 🚀
