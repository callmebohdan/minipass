@echo off

echo vcpkg...
set VCPKG_ROOT=C:\Program Files\vcpkg
if not exist "%VCPKG_ROOT%" (
    echo Cloning vcpkg repository...
    git clone https://github.com/microsoft/vcpkg.git "%VCPKG_ROOT%"
)

cd "%VCPKG_ROOT%"

if not exist "%VCPKG_ROOT%\vcpkg.exe" (
    echo Bootstrapping vcpkg...
    .\bootstrap-vcpkg.bat
)

vcpkg install cmake qt6 gtest

setx PATH "%VCPKG_ROOT%;%PATH%"

echo Installation complete. CMake, Qt6, and GTest are now installed via vcpkg.

pause
