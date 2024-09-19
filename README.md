# minipass

A minimalistic command-line password generator with customizable settings.

## Requirements

 - Cmake v3.30.2
 - MSVC2019_64 (Windows)
 - GCC v14.2 (Linux)
 - Qt6 v6.7.2
 - GTest v1.12.1

## Requirements installation

Windows:

1. [Install Cmake](https://cmake.org/download).

2. [Install GTest](https://github.com/google/googletest/blob/main/googletest/README.md):

    ```powershell
    cd C:\Program Files
    ```
    
    ```powershell
    git clone https://github.com/microsoft/vcpkg.git
    ```
    
    ```powershell
    cd vcpkg
    ```

    ```powershell
    .\bootstrap-vcpkg.bat
    ```
    
    ```powershell
    $env:VCPKG_ROOT = "C:\Program Files\vcpkg"
    ```

    ```powershell
    $env:PATH = "$env:VCPKG_ROOT;$env:PATH"
    ```

    ```powershell
    vcpkg install gtest
    ```

2. [Install Qt6 via Qt Online Installer](https://doc.qt.io/qt-6/qt-online-installation.html).
Also install MSVC2019_64 (Qt Maintenance Tool -> Add or remove components -> Qt -> Qt 6.7.2 -> MSVC 2019 64-bit).

3. Add the Qt6 install location to PATH:

    ```powershell
    $env:PATH = "C:\Qt\6.7.2\mingw_64\bin;$env:PATH"
    ```

Linux:

1. Install Cmake:

    ```bash
    sudo apt-get -y install cmake
    ```

2. Install GTest:

    ```bash
    sudo apt-get -y install libgtest-dev
    ```

   Build and install static libraries:
   
    ```bash
    cd /usr/src/gtest && sudo cmake . && sudo make && sudo mv libg* /usr/lib/ && cd -
    ```
   
3. Install gcc:

    ```bash
    sudo apt-get -y install build-essential
    ```

4. Install Qt6:

    ```bash
    sudo apt-get -y install libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev mesa-common-dev qt6-base-dev qt6-base-dev-tools libxcb-cursor0
    ```

## Build

Windows:

1. Clone the repository:

    ```powershell
    git clone https://github.com/callmebohdan/minipass.git
    ```

2. Navigate to the project directory:

    ```powershell
    cd minipass
    ```

3. Build and run the project:

    ```powershell
    .\scripts\build_and_run.bat
    ```

4. Clean the project:

    ```powershell
    .\scripts\clean.bat
    ```

Linux:

1. Clone the repository:

    ```bash
    git clone https://github.com/callmebohdan/minipass.git
    ```

2. Navigate to the project directory:

    ```bash
    cd minipass
    ```

3. Build and run the project:

    ```bash
    sh ./scripts/build_and_run.sh
    ```

4. Clean the project:

    ```bash
    sh ./scripts/clean.sh
    ```

5. To fix the **Warning: Ignoring XDG_SESSION_TYPE=wayland on Gnome. Use QT_QPA_PLATFORM=wayland to run on Wayland anyway** run:

    ```bash
    export QT_QPA_PLATFORM=xcb
    ```

## Usage

Windows GUI:

```powershell
.\bin\minipassGUI.exe
```

Windows CLI:

```powershell
.\bin\minipassCLI.exe [options]
```

Linux GUI:

```bash
./bin/minipassGUI
```

Linux CLI:

```bash
./bin/minipassCLI [options]
```

## Options

| Short  | Long         | Purpose                                              | Output |
|:------:|:------------:|------------------------------------------------------|--------|
| -h     | --help       | Display this help message and exit.                  | 
| -d     | --default    | Generate a password with default settings.           | Random Password: 5n\`Dt\|x\]\]WU1JHy> |
| -l N   | --length N   | Set the length (N) of the password (default: 16).    | Random Password: I.aOo^s9SPJ-.QI=9rolZJ^55 |
| -n     | --numbers    | Exclude numbers from the password.                   | Random Password: Pw\|/X-KfXNnF.o&m |
| -o     | --lower      | Exclude lowercase letters from the password.         | Random Password: CU!=[C[4@V_D\L\% |
| -u     | --upper      | Exclude uppercase letters from the password.         | Random Password: o"lh?eg;l2gb`3%. |
| -s     | --special    | Exclude special characters from the password.        | Random Password: 8UqA7b260Od9Zd7m |
| -k     | --history    | Save generated passwords in history.                 | Random Password: &%8Oi\f1_W3bPw`@ |
|        |              |                                                      | Password saved to /build/bin/PasswordsHistory.csv |
| -m     | --mnemonic   | Create a mnemonic password.                          | Random Password: kupsxettpiaizjmx |
|        |              |                                                      | Mnemonic Phrase: kingdom update pressure study xerox era terminal type preview icon axis insight zucchini justice media xerox |
| -c STR | --custom STR | Exclude specific characters (STR) from the password. | Random Password: 9"Y"9yzyy`"}~ZY~ |

## Example

Windows:

![minipass-example-windows-gui](assets/examples/windows/minipass-example-windows-gui.png)

Linux:

![minipass-example-linux-gui](assets/examples/linux/minipass-example-linux-gui.png)

## Testing with GTest

Windows:

1. Test minipass.cpp:
    ```powershell
    .\bin\TestMinipass.exe
    ```

2. Test utils.cpp:
    ```powershell
    .\bin\TestUtils.exe
    ```

Linux:

1. Test minipass.cpp:
    ```bash
    ./bin/TestMinipass
    ```

2. Test utils.cpp:
    ```bash
    ./bin/TestUtils
    ```

