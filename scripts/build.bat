@echo off

setlocal

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

pushd %~dp0
cd ..
set PROJECT_DIR=%cd%
popd

set BUILD_DIR=%PROJECT_DIR%\build
set BIN_DIR=%PROJECT_DIR%\bin
set OUT_DIR=%PROJECT_DIR%\out
set QT_PATH=C:\Qt\6.7.2\msvc2019_64

if exist "%BIN_DIR%" (
    echo Cleaning bin directory...
    rd /s /q "%BIN_DIR%"
)

if exist "%BUILD_DIR%" (
    echo Cleaning build directory...
    rd /s /q "%BUILD_DIR%"
)

if exist "%OUT_DIR%" (
    echo Cleaning out directory...
    rd /s /q "%OUT_DIR%"
)

echo Creating build directory...
mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

echo Configuring the project with MSBuild...
cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH="%QT_PATH%" "%PROJECT_DIR%"

echo Building the project with MSBuild...
msbuild "%BUILD_DIR%\minipass.sln" /p:Configuration=Release

if exist "%BUILD_DIR%\src\Release\minipassGUI.exe" (
    echo Deploying Qt libraries for minipassGUI.exe...
    "%QT_PATH%\bin\windeployqt.exe" --release --compiler-runtime "%BUILD_DIR%\src\Release\minipassGUI.exe"
) else (
    echo Warning: minipassGUI.exe does not exist. Skipping Qt deployment.
)

if exist "%BUILD_DIR%\src\Release\minipassCLI.exe" (
    echo Deploying Qt libraries for minipassCLI.exe...
    "%QT_PATH%\bin\windeployqt.exe" --release --compiler-runtime "%BUILD_DIR%\src\Release\minipassCLI.exe"
) else (
    echo Warning: minipassCLI.exe does not exist. Skipping Qt deployment.
)

if exist "%BUILD_DIR%\src\Release\minipassCLI.exe" (
    echo Copying the application into the bin directory...
    mkdir "%BIN_DIR%"    
    xcopy /s /e /y "%BUILD_DIR%\src\Release\minipassGUI.exe" "%BIN_DIR%"
    xcopy /s /e /y "%BUILD_DIR%\src\Release\minipassCLI.exe" "%BIN_DIR%"
    xcopy /s /e /y "%BUILD_DIR%\src\Release\*.dll" "%BIN_DIR%"
    xcopy /s /e /y "%BUILD_DIR%\src\Release\generic" "%BIN_DIR%\generic"
    xcopy /s /e /y "%BUILD_DIR%\src\Release\iconengines" "%BIN_DIR%\iconengines"
    xcopy /s /e /y "%BUILD_DIR%\src\Release\imageformats" "%BIN_DIR%\imageformats"
    xcopy /s /e /y "%BUILD_DIR%\src\Release\multimedia" "%BIN_DIR%\multimedia"
    xcopy /s /e /y "%BUILD_DIR%\src\Release\networkinformation" "%BIN_DIR%\networkinformation"
    xcopy /s /e /y "%BUILD_DIR%\src\Release\platforms" "%BIN_DIR%\platforms"
    xcopy /s /e /y "%BUILD_DIR%\src\Release\styles" "%BIN_DIR%\styles"
    xcopy /s /e /y "%BUILD_DIR%\src\Release\tls" "%BIN_DIR%\tls"
) else (
    echo Error: minipassCLI.exe was not created.
)

if exist "%BUILD_DIR%\test\Release\" (
    echo Copying the tests into the bin directory...
    copy "%BUILD_DIR%\test\Release\TestMinipass.exe" "%BIN_DIR%"
    copy "%BUILD_DIR%\test\Release\TestUtils.exe" "%BIN_DIR%"
) else (
    echo Error: tests were not created.
)

endlocal

pause
