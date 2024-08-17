# minipass

A minimalistic command-line password generator with customizable settings.

## Requirements

Windows:

1. Install [Cmake](https://cmake.org/download).
2. Install [gtest](https://github.com/google/googletest/blob/main/googletest/README.md):

    ```powershell
    $ cd C:\Program Files
    $ git clone https://github.com/microsoft/vcpkg.git
    $ cd vcpkg 
    $ .\bootstrap-vcpkg.bat
    $ $env:VCPKG_ROOT = "C:\Program Files\vcpkg"
    $ $env:PATH = "$env:VCPKG_ROOT;$env:PATH"
    $ vcpkg install gtest
    ```

Linux:

1. Install Cmake:

    ```bash
    $ sudo apt-get install cmake -y
    ```

2. Install gtest:

    ```bash
    $ sudo apt-get install libgtest-dev -y
    ```

## Installation

Windows:

```powershell
$ git clone https://github.com/callmebohdan/minipass.git
$ cd minipass
$ if (Test-Path build) {cmake --build build --target clean}
$ cmake -S . -B build
$ cmake --build build --config Release
```

Linux:

```bash
$ git clone https://github.com/callmebohdan/minipass.git
$ cd minipass
$ [ -d "build" ] && cmake --build build --target clean 
$ cmake -S . -B build
$ cmake --build build --config Release
```

## Usage

Windows:

```powershell
$ .\build\src\Release\MiniPass.exe [options]
```

Linux:

```bash
$ .\build\src\MiniPass [options]
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

## Testing with gtest

Windows:

1. Test minipass.cpp:
    ```powershell
    .\build\test\Release\TestMinipass.exe
    ```

2. Test utils.cpp:
    ```powershell
    .\build\test\Release\TestUtils.exe
    ```

Linux:

1. Test minipass.cpp:
    ```bash
    ./build/test/TestMinipass
    ```

2. Test utils.cpp:
    ```bash
    ./build/test/TestUtils
    ```
