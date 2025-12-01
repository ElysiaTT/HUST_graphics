@echo off
echo Cleaning build directory...
if exist build rmdir /s /q build
mkdir build
cd build

echo Configuring CMake...
cmake -G "MinGW Makefiles" ..
if errorlevel 1 goto error

echo Building project...
cmake --build . --config Release
if errorlevel 1 goto error

echo Build successful!
echo Executable location: build\bin\SunEarthMoon.exe
goto end

:error
echo Build failed!
pause
exit /b 1

:end
pause
