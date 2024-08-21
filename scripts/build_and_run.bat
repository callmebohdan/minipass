@echo off

setlocal

pushd %~dp0
cd ..
set PROJECT_DIR=%cd%
popd

set BUILD_DIR=%PROJECT_DIR%\build
set BIN_DIR=%PROJECT_DIR%\bin
set OUT_DIR=%PROJECT_DIR%\out
set QT_PATH=C:\Qt\6.7.2\mingw_64

if exist "%BUILD_DIR%" (
    echo Cleaning previous build...
    rd /s /q "%BUILD_DIR%"
)

if exist "%OUT_DIR%" (
    echo Cleaning previous build's output...
    rd /s /q "%OUT_DIR%"
)

if exist "%BIN_DIR%" (
    echo Cleaning previous build bin/...
    rd /s /q "%BIN_DIR%"
)

echo Creating build directory...
mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

echo Configuring the project with CMake...
cmake -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="%QT_PATH%" "%PROJECT_DIR%"

echo Building the project...
mingw32-make

if exist "%QT_PATH%\bin\windeployqt.exe" (
    echo Deploying Qt libraries...
    "%QT_PATH%\bin\windeployqt.exe" "%BUILD_DIR%\src\minipass.exe"
)

if exist "%BUILD_DIR%\src\minipass.exe" (
    echo Copying the application into bin/ directory...
    mkdir "%BIN_DIR%\platforms"    
    copy "%BUILD_DIR%\src\minipass.exe" "%BIN_DIR%"
    copy "%BUILD_DIR%\src\Qt6Core.dll" "%BIN_DIR%"
    copy "%BUILD_DIR%\src\Qt6Gui.dll" "%BIN_DIR%"
    copy "%BUILD_DIR%\src\Qt6Widgets.dll" "%BIN_DIR%"
    copy "%BUILD_DIR%\src\platforms" "%BIN_DIR%\platforms"    
    "%BIN_DIR%\minipass.exe"
) else (
    echo Error: minipass.exe was not created.
)

endlocal

pause
