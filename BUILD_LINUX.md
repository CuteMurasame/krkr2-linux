# Building Kirikiroid2 for Linux

This document describes how to build and run Kirikiroid2 on Linux systems.

## Prerequisites

### System Requirements
- Linux distribution (Ubuntu 20.04+, Debian 11+, Fedora 34+, or similar)
- CMake 3.10 or higher
- GCC 7+ or Clang 6+ with C++11 support
- Git (for cloning the repository)

### Required Dependencies

Install the following packages using your distribution's package manager:

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    cmake \
    git \
    libsdl2-dev \
    libgl1-mesa-dev \
    libfreetype6-dev \
    zlib1g-dev \
    libpng-dev \
    libjpeg-dev \
    pkg-config
```

#### Fedora/RHEL/CentOS
```bash
sudo dnf install -y \
    gcc \
    gcc-c++ \
    cmake \
    git \
    SDL2-devel \
    mesa-libGL-devel \
    freetype-devel \
    zlib-devel \
    libpng-devel \
    libjpeg-turbo-devel \
    pkgconfig
```

#### Arch Linux
```bash
sudo pacman -S --needed \
    base-devel \
    cmake \
    git \
    sdl2 \
    mesa \
    freetype2 \
    zlib \
    libpng \
    libjpeg-turbo
```

### Optional Dependencies (Recommended)

For full multimedia support, install these additional packages:

#### Ubuntu/Debian
```bash
sudo apt-get install -y \
    libavcodec-dev \
    libavformat-dev \
    libavutil-dev \
    libswscale-dev \
    libswresample-dev \
    libopenal-dev \
    libopus-dev \
    libopusfile-dev \
    libvorbis-dev \
    libcairo2-dev \
    libpixman-1-dev \
    libexpat1-dev \
    libarchive-dev
```

#### Fedora/RHEL/CentOS
```bash
sudo dnf install -y \
    ffmpeg-devel \
    openal-soft-devel \
    opus-devel \
    opusfile-devel \
    libvorbis-devel \
    cairo-devel \
    pixman-devel \
    expat-devel \
    libarchive-devel
```

#### Arch Linux
```bash
sudo pacman -S --needed \
    ffmpeg \
    openal \
    opus \
    opusfile \
    libvorbis \
    cairo \
    pixman \
    expat \
    libarchive
```

## Building

### 1. Clone the Repository

```bash
git clone https://github.com/CuteMurasame/krkr2-linux.git
cd krkr2-linux
```

### 2. Create Build Directory

```bash
mkdir build
cd build
```

### 3. Configure with CMake

```bash
cmake ..
```

For a debug build:
```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

For a release build with optimizations:
```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
```

### 4. Compile

```bash
make -j$(nproc)
```

The `-j$(nproc)` flag enables parallel compilation using all available CPU cores.

### 5. Install (Optional)

```bash
sudo make install
```

This will install:
- The `kirikiroid2` executable to `/usr/local/bin`
- Resources to `/usr/local/share/kirikiroid2`

## Running

### From Build Directory

```bash
./kirikiroid2
```

### After Installation

```bash
kirikiroid2
```

## Troubleshooting

### CMake Cannot Find Dependencies

If CMake cannot find required packages, make sure pkg-config is installed and the development packages are properly installed:

```bash
pkg-config --list-all | grep -E "sdl2|freetype2|gl"
```

### Missing Cocos2d-x

**Note**: This project depends on Cocos2d-x, which is not included in the repository. You may need to:

1. Clone Cocos2d-x separately:
   ```bash
   git clone https://github.com/cocos2d/cocos2d-x.git vendor/cocos2d-x/current
   cd vendor/cocos2d-x/current
   git checkout v3.17.2
   ```

2. Or install it system-wide if your distribution provides it.

The CMakeLists.txt will need to be updated to find and link Cocos2d-x properly.

### Compilation Errors

1. **"error: 'typeof' was not declared"**
   - This should be fixed by the `-Dtypeof=decltype` flag in CMakeLists.txt
   - Ensure you're using a C++11 compatible compiler

2. **Missing header files**
   - Some vendor dependencies may not be available as system packages
   - You may need to compile them from source and place them in the `vendor/` directory

3. **Linker errors**
   - Make sure all required libraries are installed
   - Check that pkg-config can find them: `pkg-config --modversion <package>`

### Performance Issues

For best performance, ensure you're building with:
```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
```

This enables `-O3` optimization and disables debug symbols.

## Development

### Cleaning Build Files

```bash
cd build
make clean
```

Or remove the entire build directory:
```bash
rm -rf build
```

### Rebuild from Scratch

```bash
rm -rf build
mkdir build
cd build
cmake ..
make -j$(nproc)
```

## Current Limitations

This is an initial Linux port. Some features may not be fully functional:

1. **Vendor Dependencies**: Many vendor libraries (listed in Android.mk) are not yet integrated
2. **Cocos2d-x Integration**: Full integration with Cocos2d-x needs to be completed
3. **Platform-Specific Code**: Some Windows-specific code may need Linux alternatives
4. **Testing**: Comprehensive testing on Linux is needed

## Contributing

Contributions are welcome! Please:
1. Test your changes on multiple Linux distributions if possible
2. Update this documentation if you add new dependencies
3. Follow the existing code style
4. Submit pull requests with clear descriptions

## License

See the LICENSE file in the repository root.
