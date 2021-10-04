# Mod(C++) Fundamentals

## Install tools
### All Platforms:
* Follow the instructions to install VSCode from https://code.visualstudio.com/

### Ubuntu 20.04 or newer
* Install the build tools
```bash
sudo apt-get install ninja-build pkg-config curl zip unzip tar cmake build-essential libx11-dev libxrandr-dev libxi-dev libudev-dev libgl1-mesa-dev
```

### Windows:
* Follow the instructions to install cmake (3.21) from https://cmake.org/download/
* Install Visual Studio https://visualstudio.microsoft.com/
  You might have to reboot your computer once that's done.

### Mac
* Install clang by typing `xcode-select --install` in a terminal and following the instructions
* Install the build tools
```bash
brew install cmake ninja
```
* Follow the instructions for [Launching VSCode from the command line](https://code.visualstudio.com/docs/setup/mac#_launching-from-the-command-line)

## Configure and build project

### All Platforms:

```bash
git clone https://github.com/mod-cpp/pacman.git
cd pacman
code .
```
