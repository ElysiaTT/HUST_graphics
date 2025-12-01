@echo off
echo ====================================
echo   Sun-Earth-Moon System Builder
echo ====================================
echo.

REM 检查是否存在build目录
if exist build (
    echo [INFO] Found existing build directory
    choice /C YN /M "Do you want to clean and rebuild"
    if errorlevel 2 goto build
    if errorlevel 1 goto clean
) else (
    mkdir build
    echo [INFO] Created build directory
)

:clean
echo [INFO] Cleaning build directory...
rmdir /S /Q build
mkdir build

:build
cd build

echo.
echo [STEP 1/3] Configuring CMake...
echo.

REM 尝试使用MinGW
where mingw32-make >nul 2>&1
if %errorlevel% equ 0 (
    echo [INFO] Using MinGW Makefiles
    cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
    if errorlevel 1 goto error
    goto compile_mingw
)

REM 尝试使用Visual Studio 2022
where msbuild >nul 2>&1
if %errorlevel% equ 0 (
    echo [INFO] Using Visual Studio 2022
    cmake -G "Visual Studio 17 2022" ..
    if errorlevel 1 goto error
    goto compile_vs
)

REM 尝试使用Visual Studio 2019
echo [INFO] Trying Visual Studio 2019
cmake -G "Visual Studio 16 2019" ..
if errorlevel 1 goto no_compiler
goto compile_vs

:compile_mingw
echo.
echo [STEP 2/3] Compiling with MinGW...
echo.
mingw32-make -j4
if errorlevel 1 goto error
goto success

:compile_vs
echo.
echo [STEP 2/3] Compiling with Visual Studio...
echo.
cmake --build . --config Release
if errorlevel 1 goto error
goto success

:success
echo.
echo [STEP 3/3] Copying resources...
echo.
cd ..
if not exist build\bin mkdir build\bin
xcopy /Y /I shaders build\bin\shaders\
if exist build\bin\Release\SunEarthMoon.exe (
    move /Y build\bin\Release\SunEarthMoon.exe build\bin\
)

echo.
echo ====================================
echo   BUILD SUCCESSFUL!
echo ====================================
echo.
echo Executable location: build\bin\SunEarthMoon.exe
echo.
echo Run the program? (Y/N)
choice /C YN /M "Your choice"
if errorlevel 2 goto end
if errorlevel 1 goto run

:run
cd build\bin
start SunEarthMoon.exe
goto end

:no_compiler
echo.
echo [ERROR] No suitable compiler found!
echo.
echo Please install one of the following:
echo   - MinGW-w64: https://github.com/niXman/mingw-builds-binaries/releases
echo   - Visual Studio 2019/2022 with C++ Desktop Development
echo.
goto error_end

:error
echo.
echo [ERROR] Build failed!
echo.
echo Common issues:
echo   1. Missing dependencies (GLFW, GLM, GLAD)
echo   2. Compiler not in PATH
echo   3. CMake version too old (need 3.10+)
echo.
echo Check README.md for detailed setup instructions.
echo.
goto error_end

:error_end
pause
exit /b 1

:end
pause
