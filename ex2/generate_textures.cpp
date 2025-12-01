// 简单的纹理生成程序
#include <fstream>
#include <vector>
#include <cmath>

// 生成BMP文件头
void writeBMPHeader(std::ofstream& file, int width, int height) {
    int fileSize = 54 + 3 * width * height;

    // BMP文件头
    unsigned char bmpFileHeader[14] = {
        'B', 'M',  // 签名
        0, 0, 0, 0,  // 文件大小
        0, 0,  // 保留
        0, 0,  // 保留
        54, 0, 0, 0  // 数据偏移
    };
    bmpFileHeader[2] = (unsigned char)(fileSize);
    bmpFileHeader[3] = (unsigned char)(fileSize >> 8);
    bmpFileHeader[4] = (unsigned char)(fileSize >> 16);
    bmpFileHeader[5] = (unsigned char)(fileSize >> 24);

    // BMP信息头
    unsigned char bmpInfoHeader[40] = {
        40, 0, 0, 0,  // 信息头大小
        0, 0, 0, 0,  // 宽度
        0, 0, 0, 0,  // 高度
        1, 0,  // 平面数
        24, 0,  // 位深度
        0, 0, 0, 0,  // 压缩
        0, 0, 0, 0,  // 图像大小
        0, 0, 0, 0,  // X分辨率
        0, 0, 0, 0,  // Y分辨率
        0, 0, 0, 0,  // 使用的颜色
        0, 0, 0, 0   // 重要的颜色
    };
    bmpInfoHeader[4] = (unsigned char)(width);
    bmpInfoHeader[5] = (unsigned char)(width >> 8);
    bmpInfoHeader[6] = (unsigned char)(width >> 16);
    bmpInfoHeader[7] = (unsigned char)(width >> 24);
    bmpInfoHeader[8] = (unsigned char)(height);
    bmpInfoHeader[9] = (unsigned char)(height >> 8);
    bmpInfoHeader[10] = (unsigned char)(height >> 16);
    bmpInfoHeader[11] = (unsigned char)(height >> 24);

    file.write((char*)bmpFileHeader, 14);
    file.write((char*)bmpInfoHeader, 40);
}

// 生成地球纹理
void generateEarthTexture(const char* filename) {
    int width = 512;
    int height = 512;

    std::ofstream file(filename, std::ios::binary);
    writeBMPHeader(file, width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // 创建一个简单的地球纹理（蓝绿色）
            float fx = (float)x / width;
            float fy = (float)y / height;

            // 简单的陆地和海洋
            float noise = sin(fx * 20.0f) * cos(fy * 20.0f);

            unsigned char b, g, r;
            if (noise > 0.3) {
                // 陆地（绿棕色）
                r = 34 + (unsigned char)(noise * 50);
                g = 139 + (unsigned char)(noise * 50);
                b = 34;
            } else {
                // 海洋（蓝色）
                r = 0;
                g = 105 + (unsigned char)((1.0f + noise) * 50);
                b = 148 + (unsigned char)((1.0f + noise) * 50);
            }

            file.write((char*)&b, 1);
            file.write((char*)&g, 1);
            file.write((char*)&r, 1);
        }
    }

    file.close();
}

// 生成月球纹理
void generateMoonTexture(const char* filename) {
    int width = 512;
    int height = 512;

    std::ofstream file(filename, std::ios::binary);
    writeBMPHeader(file, width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float fx = (float)x / width;
            float fy = (float)y / height;

            // 创建月球表面（灰色带陨石坑）
            float crater = sin(fx * 30.0f) * cos(fy * 30.0f);

            unsigned char gray = 140 + (unsigned char)(crater * 40);

            file.write((char*)&gray, 1);
            file.write((char*)&gray, 1);
            file.write((char*)&gray, 1);
        }
    }

    file.close();
}

// 生成太阳纹理
void generateSunTexture(const char* filename) {
    int width = 512;
    int height = 512;

    std::ofstream file(filename, std::ios::binary);
    writeBMPHeader(file, width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float fx = (float)x / width;
            float fy = (float)y / height;

            // 创建太阳表面（黄橙色带纹理）
            float flare = sin(fx * 25.0f) * sin(fy * 25.0f);

            unsigned char r = 255;
            unsigned char g = 200 + (unsigned char)(flare * 55);
            unsigned char b = 0 + (unsigned char)(flare * 100);

            file.write((char*)&b, 1);
            file.write((char*)&g, 1);
            file.write((char*)&r, 1);
        }
    }

    file.close();
}

int main() {
    generateEarthTexture("textures/earth.bmp");
    generateMoonTexture("textures/moon.bmp");
    generateSunTexture("textures/sun.bmp");

    return 0;
}
