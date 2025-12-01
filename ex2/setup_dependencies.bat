@echo off
echo ====================================
echo   Dependency Setup Script
echo ====================================
echo.

REM 检查git是否安装
where git >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] Git is not installed or not in PATH
    echo Please install Git from: https://git-scm.com/download/win
    pause
    exit /b 1
)

REM 创建external目录
if not exist external mkdir external
cd external

echo [STEP 1/4] Downloading GLFW...
if exist glfw (
    echo [INFO] GLFW already exists, skipping
) else (
    git clone --depth 1 https://github.com/glfw/glfw.git
    if errorlevel 1 goto error
    echo [OK] GLFW downloaded
)

echo.
echo [STEP 2/4] Downloading GLM...
if exist glm (
    echo [INFO] GLM already exists, skipping
) else (
    git clone --depth 1 https://github.com/g-truc/glm.git
    if errorlevel 1 goto error
    echo [OK] GLM downloaded
)

echo.
echo [STEP 3/4] Setting up GLAD directory structure...
if not exist glad mkdir glad
cd glad
if not exist include\glad mkdir include\glad
if not exist include\KHR mkdir include\KHR
if not exist src mkdir src
cd ..\..

echo [OK] GLAD directories created

echo.
echo [STEP 4/4] GLAD files need manual download
echo.
echo Please follow these steps:
echo   1. Visit: https://glad.dav1d.de/
echo   2. Select:
echo      - Language: C/C++
echo      - Specification: OpenGL
echo      - Profile: Core
echo      - API gl: Version 3.3 or higher
echo   3. Click "GENERATE"
echo   4. Download the ZIP file
echo   5. Extract contents:
echo      - Copy 'include/glad' to 'external/glad/include/'
echo      - Copy 'include/KHR' to 'external/glad/include/'
echo      - Copy 'src/glad.c' to 'external/glad/src/'
echo.
echo Press any key when GLAD files are in place...
pause >nul

REM 验证文件是否存在
if not exist external\glad\src\glad.c (
    echo [WARNING] glad.c not found in external/glad/src/
    echo Build may fail. Please check GLAD setup.
    pause
    goto end
)

if not exist external\glad\include\glad\glad.h (
    echo [WARNING] glad.h not found in external/glad/include/glad/
    echo Build may fail. Please check GLAD setup.
    pause
    goto end
)

echo.
echo ====================================
echo   SETUP COMPLETE!
echo ====================================
echo.
echo All dependencies are ready.
echo You can now run build.bat to compile the project.
echo.
goto end

:error
echo.
echo [ERROR] Failed to download dependencies
echo Please check your internet connection and try again.
echo.
pause
exit /b 1

:end
pause
