@echo off
cd /d %~dp0
echo Starting Sun-Earth-Moon System with Textures and Lighting...
echo.
if not exist "build\bin\SunEarthMoon.exe" (
    echo Error: SunEarthMoon.exe not found!
    echo Please run rebuild.bat first to build the project.
    pause
    exit /b 1
)

build\bin\SunEarthMoon.exe
