# Build Status and Dependencies

This document describes the current build status and dependency management.

## Current Build Status

✅ **Full 7zip support** - Complete 7zip SDK integrated (all archive functionality)  
✅ **Core library builds** - The krkr2_core static library compiles successfully  
✅ **Executable builds** - A working `kirikiroid2` executable is produced  
✅ **Conditional Cocos2d-x** - Builds with or without Cocos2d-x automatically  
⚠️ **UI requires Cocos2d-x** - Full UI functionality needs Cocos2d-x installation

## Integrated Dependencies

### 1. 7-Zip SDK ✅ INCLUDED

**Status:** Fully integrated in repository  
**Location:** `src/core/base/7zip/` (from p7zip project)  
**Features enabled:**
- Full 7z archive reading and writing
- XP3 archive repacking with compression
- All compression algorithms (LZMA, LZMA2, etc.)

**Files now working:**
- `src/core/base/7zArchive.cpp` - 7z archive support
- `src/core/environ/XP3ArchiveRepack.cpp` - XP3 repacking with 7z compression
- Complete SDK: C sources (7zip/C/*) and C++ sources (7zip/CPP/*)

**No additional installation needed** - works out of the box!

## Optional Dependencies

### 2. Cocos2d-x (UI Framework)

**Status:** Optional - build works with or without it  
**Impact:** UI and rendering features require Cocos2d-x  
**Build behavior:**
- **Without Cocos2d-x:** Builds core engine library successfully, minimal executable
- **With Cocos2d-x:** Full featured build with UI, rendering, main application loop

**Files enabled when Cocos2d-x available:**
- `src/core/environ/cocos2d/*.cpp` (13 files) - Cocos2d-x integration
- `src/core/environ/ui/*.cpp` (15+ files) - UI components
- `src/linux_main.cpp` - Full application mode with SDL and Cocos2d-x

**To enable Cocos2d-x features:**

The build system automatically detects Cocos2d-x in these locations:
- `/usr/include/cocos2d` (system install)
- `/usr/local/include/cocos2d` (local install)
- `vendor/cocos2d-x/cocos` (repository vendor directory)
- `../cocos2d-x/cocos` (sibling directory)

Install Cocos2d-x to any of these locations:
```bash
# Option 1: Clone to vendor directory (recommended)
mkdir -p vendor
git clone https://github.com/cocos2d/cocos2d-x.git vendor/cocos2d-x
cd vendor/cocos2d-x
git checkout cocos2d-x-4.0  # or compatible version

# Option 2: Clone as sibling directory
cd ..
git clone https://github.com/cocos2d/cocos2d-x.git
```

Then rebuild - CMake will automatically detect and use it!

### 3. System Dependencies ✅ REQUIRED

These must be installed via package manager - see BUILD_LINUX.md for details.

**Core dependencies** (required):
- SDL2, OpenGL, FreeType, zlib, libpng, libjpeg

**Optional dependencies** (recommended):
- FFmpeg (video playback)
- OpenAL (3D audio)
- Opus, Vorbis (audio codecs)
- Cairo, Pixman (graphics)
- LibArchive, Expat (utilities)

## Included Components

All components build successfully:

### Core Components ✅
- Base utilities (with 7zip support!)
- Binary stream handling
- Character set support
- Event system
- Plugin interface
- Script manager
- Storage interface (XP3, ZIP, TAR, 7z archives)
- System initialization
- Text streams

### Environment ✅
- Application framework
- CPU detection
- Linux platform layer
- **Cocos2d-x integration** (when available)
- **UI components** (when Cocos2d-x available)

### Extensions ✅
- Core extensions

### Movie/Video ✅
- Video playback modules

### Messaging ✅
- Messaging system
- Options handling

### Sound ✅
- Audio engine core
- Sound processing

### TJS2 ✅
- TJS2 scripting engine (complete)

### Utils ✅
- Utility functions
- Encoding support
- Minizip library
- **7zip compression** ✅

### Visual ✅
- Graphics core
- OpenGL rendering
- Texture compression (ETC, PVRTC, ASTC)
- Layer management
- Transform support

## Build Options

### Default Build (without Cocos2d-x)
```bash
./build.sh
# or
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
```

**Produces:** Core engine library + minimal executable  
**Features:** All archive support (including 7z), scripting, utilities  
**Missing:** UI, rendering, full application

### Full Build (with Cocos2d-x)
```bash
# After installing Cocos2d-x to vendor/ or system
./build.sh
```

**Produces:** Fully functional Kirikiroid2 application  
**Features:** Everything including UI, rendering, full game engine

## Dependencies Summary

| Dependency | Status | Required | Location |
|------------|--------|----------|----------|
| **7-Zip SDK** | ✅ Included | Optional | src/core/base/7zip/ |
| **SDL2** | System pkg | ✅ Yes | libsdl2-dev |
| **OpenGL** | System pkg | ✅ Yes | libgl1-mesa-dev |
| **FreeType** | System pkg | ✅ Yes | libfreetype6-dev |
| **zlib** | System pkg | ✅ Yes | zlib1g-dev |
| **libpng** | System pkg | ✅ Yes | libpng-dev |
| **libjpeg** | System pkg | ✅ Yes | libjpeg-dev |
| **Cocos2d-x** | Optional | ⚠️ UI | vendor/cocos2d-x/ |
| **FFmpeg** | System pkg | Optional | libavcodec-dev, etc. |
| **OpenAL** | System pkg | Optional | libopenal-dev |
| **Opus** | System pkg | Optional | libopus-dev |
| **Vorbis** | System pkg | Optional | libvorbis-dev |

## CI/CD

GitHub Actions workflow automatically builds on:
- Ubuntu 20.04 (Release + Debug)
- Ubuntu 22.04 (Release + Debug)

Current CI builds succeed with:
- ✅ Full 7zip support
- ✅ Core engine compilation
- ⚠️ Without Cocos2d-x (minimal mode)

When Cocos2d-x is added to CI, it will build the full application.

## Next Steps

**For immediate use:**
- ✅ Build works now - core engine functional
- ✅ All archive formats supported (XP3, ZIP, TAR, 7z)
- ✅ Scripting engine ready

**For full functionality:**
1. Install or build Cocos2d-x
2. Place in vendor/cocos2d-x/ or system location
3. Rebuild - features activate automatically!

## Related Documentation

- [BUILD_LINUX.md](BUILD_LINUX.md) - Build instructions and dependencies
- [CONTRIBUTING.md](CONTRIBUTING.md) - Development guide
- [CMakeLists.txt](CMakeLists.txt) - Build configuration with auto-detection
- [readme.md](readme.md) - Project overview
