@echo off
setlocal

REM Save the current directory
pushd %~dp0

REM Navigate up one level from the scripts directory
cd ..

REM Store the current directory (project root) in PROJECT_DIR
set PROJECT_DIR=%cd%

REM Return to the original directory (scripts directory)
popd

set BUILD_DIR=%PROJECT_DIR%\build
set OUT_DIR=%PROJECT_DIR%\out
set BIN_DIR=%PROJECT_DIR%\bin

:: Clean previous build if exists
if exist "%BUILD_DIR%" (
    echo Cleaning previous build...
    rd /s /q "%BUILD_DIR%"
)

:: Clean previous build if exists
if exist "%OUT_DIR%" (
    echo Cleaning previous build output...
    rd /s /q "%OUT_DIR%"
)

:: Clean previous build bin directory if exists
if exist "%BIN_DIR%" (
    echo Cleaning previous build bin directory...
    rd /s /q "%BIN_DIR%"
)

endlocal
pause
