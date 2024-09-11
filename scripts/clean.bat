@echo off

setlocal

pushd %~dp0
cd ..
set PROJECT_DIR=%cd%
popd

set BIN_DIR=%PROJECT_DIR%\bin
set BUILD_DIR=%PROJECT_DIR%\build
set OUT_DIR=%PROJECT_DIR%\out

if exist "%BIN_DIR%" (
    echo Cleaning bin/ directory...
    rd /s /q "%BIN_DIR%"
)

if exist "%BUILD_DIR%" (
    echo Cleaning build/ directory...
    rd /s /q "%BUILD_DIR%"
)

if exist "%OUT_DIR%" (
    echo Cleaning out/ directory...
    rd /s /q "%OUT_DIR%"
)

endlocal
