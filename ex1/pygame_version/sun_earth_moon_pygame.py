"""
日地月运动模型 - Pygame简化版
适合没有独立显卡的电脑运行
"""

import pygame
import math
import sys

# 初始化Pygame
pygame.init()

# 窗口设置
WIDTH, HEIGHT = 1280, 720
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("日地月运动系统 - Pygame版")

# 颜色定义
BLACK = (10, 10, 20)
SUN_COLOR = (255, 230, 50)
EARTH_COLOR = (50, 100, 200)
MOON_COLOR = (180, 180, 180)
ORBIT_COLOR = (40, 40, 60)

# 时钟
clock = pygame.time.Clock()
FPS = 60

# 缩放和偏移
SCALE = 1.5
OFFSET_X = WIDTH // 2
OFFSET_Y = HEIGHT // 2

# 天体参数
SUN_RADIUS = 30
EARTH_RADIUS = 12
MOON_RADIUS = 5

EARTH_ORBIT_RADIUS = 200
MOON_ORBIT_RADIUS = 40

# 速度（弧度/秒）
EARTH_ORBIT_SPEED = 0.3  # 地球公转速度
EARTH_ROTATION_SPEED = 2.0  # 地球自转速度
MOON_ORBIT_SPEED = 1.2  # 月球公转速度（相对于地球更快）

# 轨道倾角（用于3D效果）
MOON_TILT = 15  # 度

# 时间和速度控制
time = 0
speed_multiplier = 1.0

def draw_circle_3d(surface, color, pos, radius, tilt_y=0):
    """
    绘制带3D效果的圆（通过Y轴缩放模拟透视）
    """
    # 添加简单的光照效果
    x, y = pos

    # 主体
    pygame.draw.circle(surface, color, (int(x), int(y)), int(radius))

    # 高光效果
    highlight_color = tuple(min(255, c + 50) for c in color)
    highlight_radius = radius // 3
    pygame.draw.circle(surface, highlight_color,
                      (int(x - radius//4), int(y - radius//4)),
                      int(highlight_radius))

def draw_orbit_3d(surface, color, center, radius, tilt=0):
    """
    绘制带倾斜的轨道椭圆
    """
    points = []
    segments = 100

    for i in range(segments + 1):
        angle = (i / segments) * 2 * math.pi
        x = center[0] + radius * math.cos(angle)

        # 倾斜效果：Y轴根据倾角进行缩放
        y_offset = radius * math.sin(angle) * math.cos(math.radians(tilt))
        y = center[1] + y_offset

        points.append((int(x), int(y)))

    if len(points) > 1:
        pygame.draw.lines(surface, color, True, points, 1)

def main():
    global time, speed_multiplier

    running = True
    show_help = True

    while running:
        # 事件处理
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False
                elif event.key == pygame.K_h:
                    show_help = not show_help
                elif event.key == pygame.K_UP:
                    speed_multiplier = min(5.0, speed_multiplier + 0.1)
                elif event.key == pygame.K_DOWN:
                    speed_multiplier = max(0.1, speed_multiplier - 0.1)
                elif event.key == pygame.K_SPACE:
                    speed_multiplier = 1.0 if speed_multiplier > 0 else 0

        # 更新时间
        dt = clock.tick(FPS) / 1000.0  # 转换为秒
        time += dt * speed_multiplier

        # 清屏
        screen.fill(BLACK)

        # 计算位置
        # 地球轨道 (XZ平面，这里用XY表示)
        earth_angle = time * EARTH_ORBIT_SPEED
        earth_x = OFFSET_X + EARTH_ORBIT_RADIUS * math.cos(earth_angle) * SCALE
        earth_y = OFFSET_Y + EARTH_ORBIT_RADIUS * math.sin(earth_angle) * SCALE

        # 月球轨道（相对地球，带倾角）
        moon_angle = time * MOON_ORBIT_SPEED
        moon_local_x = MOON_ORBIT_RADIUS * math.cos(moon_angle)
        moon_local_y = MOON_ORBIT_RADIUS * math.sin(moon_angle) * math.cos(math.radians(MOON_TILT))

        moon_x = earth_x + moon_local_x * SCALE
        moon_y = earth_y + moon_local_y * SCALE

        # 绘制轨道
        draw_orbit_3d(screen, ORBIT_COLOR, (OFFSET_X, OFFSET_Y),
                     EARTH_ORBIT_RADIUS * SCALE, 0)
        draw_orbit_3d(screen, ORBIT_COLOR, (int(earth_x), int(earth_y)),
                     MOON_ORBIT_RADIUS * SCALE, MOON_TILT)

        # 绘制太阳（中心）
        # 太阳辉光效果
        for i in range(3, 0, -1):
            glow_color = (255, 230 - i*30, 50 - i*10)
            pygame.draw.circle(screen, glow_color, (OFFSET_X, OFFSET_Y),
                             int(SUN_RADIUS + i*5), i*2)
        draw_circle_3d(screen, SUN_COLOR, (OFFSET_X, OFFSET_Y), SUN_RADIUS)

        # 绘制地球
        draw_circle_3d(screen, EARTH_COLOR, (earth_x, earth_y), EARTH_RADIUS)

        # 地球自转指示线
        rotation_angle = time * EARTH_ROTATION_SPEED
        line_length = EARTH_RADIUS * 0.8
        line_end_x = earth_x + line_length * math.cos(rotation_angle)
        line_end_y = earth_y + line_length * math.sin(rotation_angle)
        pygame.draw.line(screen, (100, 150, 255), (earth_x, earth_y),
                        (line_end_x, line_end_y), 2)

        # 绘制月球
        draw_circle_3d(screen, MOON_COLOR, (moon_x, moon_y), MOON_RADIUS)

        # 绘制信息文本
        font = pygame.font.Font(None, 24)
        small_font = pygame.font.Font(None, 20)

        # 速度信息
        speed_text = font.render(f"Speed: {speed_multiplier:.1f}x", True, (255, 255, 255))
        screen.blit(speed_text, (10, 10))

        # FPS
        fps_text = small_font.render(f"FPS: {int(clock.get_fps())}", True, (150, 150, 150))
        screen.blit(fps_text, (10, 40))

        # 轨道倾角提示
        tilt_text = small_font.render(f"Moon Orbit Tilt: {MOON_TILT}°", True, (150, 200, 150))
        screen.blit(tilt_text, (10, 65))

        # 帮助信息
        if show_help:
            help_texts = [
                "Controls:",
                "UP/DOWN - Change speed",
                "SPACE - Pause/Resume",
                "H - Toggle help",
                "ESC - Exit",
                "",
                "Features:",
                "- Earth orbits Sun (XZ plane)",
                "- Moon orbits Earth (tilted 15°)",
                "- Different orbital speeds"
            ]

            y_offset = HEIGHT - 20 * len(help_texts) - 10
            for i, text in enumerate(help_texts):
                color = (255, 255, 100) if i == 0 else (200, 200, 200)
                help_surface = small_font.render(text, True, color)
                screen.blit(help_surface, (WIDTH - 250, y_offset + i * 20))
        else:
            hint_text = small_font.render("Press H for help", True, (100, 100, 100))
            screen.blit(hint_text, (WIDTH - 150, HEIGHT - 30))

        # 更新显示
        pygame.display.flip()

    pygame.quit()
    sys.exit()

if __name__ == "__main__":
    print("=" * 50)
    print("日地月运动系统 - Pygame版")
    print("=" * 50)
    print("This version is optimized for integrated graphics")
    print("Press H in the window for controls")
    print("=" * 50)
    main()
