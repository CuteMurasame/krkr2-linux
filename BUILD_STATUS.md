# Build Status and Missing Dependencies

This document describes the current build status and what features are excluded due to missing dependencies.

## Current Build Status

✅ **Core library builds successfully** - The krkr2_core static library compiles with system dependencies only.  
✅ **Minimal executable builds** - A minimal `kirikiroid2` executable is produced.  
⚠️ **Limited functionality** - Many features are disabled due to missing vendor libraries.

## Missing Vendor Dependencies

The following external libraries are not included in this repository and must be obtained separately for full functionality:

### 1. Cocos2d-x (CRITICAL)

**Status:** Not included  
**Impact:** UI, rendering, and main application loop are disabled  
**Files excluded:**
- `src/core/environ/cocos2d/*.cpp` (13 files)
- `src/core/environ/ui/*.cpp` (15+ files)
- `src/linux_main.cpp` (using minimal stub instead)

**To enable:**
1. Install Cocos2d-x v3.17.2 or compatible version
2. Update CMakeLists.txt to find Cocos2d-x headers and libraries
3. Uncomment the cocos2d and UI source sections in CMakeLists.txt
4. Replace `src/linux_main.cpp` with the full version from git history

**Installation:**
```bash
# Download Cocos2d-x
git clone https://github.com/cocos2d/cocos2d-x.git vendor/cocos2d-x
cd vendor/cocos2d-x
git checkout v3.17.2

# Then update CMakeLists.txt to add:
# find_package(Cocos2d-x REQUIRED)
# or manually add include directories and link libraries
```

### 2. 7-Zip SDK

**Status:** Not included  
**Impact:** 7z archive support disabled, XP3 archive repacking disabled  
**Files excluded:**
- `src/core/base/7zArchive.cpp`
- `src/core/environ/XP3ArchiveRepack.cpp`
- `src/core/environ/ui/XP3RepackForm.cpp`
- `src/core/environ/ui/MainFileSelectorForm.cpp`

**To enable:**
1. Download 7-Zip SDK from https://www.7-zip.org/sdk.html
2. Extract to `src/core/base/7zip/` (should contain C/ and CPP/ directories)
3. Uncomment the 7zip source sections in CMakeLists.txt

**Required structure:**
```
src/core/base/7zip/
├── C/
│   ├── 7z.h
│   ├── 7zFile.h
│   ├── 7zCrc.h
│   └── *.c files
└── CPP/
    └── 7zip/
        └── ... (archive and compression modules)
```

## Included Components

The following components are currently included and build successfully:

### Core Components ✅
- Base utilities (excluding 7zip)
- Binary stream handling
- Character set support
- Event system
- Plugin interface
- Script manager
- Storage interface
- System initialization
- Text streams
- XP3 and TAR archive reading (basic)
- ZIP archive support

### Environment ✅
- Application framework (core only)
- CPU detection
- Linux platform layer (if implemented)

### Extensions ✅
- Core extensions

### Movie/Video ✅
- Video playback modules (if dependencies met)

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

### Visual ✅
- Graphics core
- OpenGL rendering
- Texture compression (ETC, PVRTC, ASTC)
- Layer management
- Transform support

## Build Options

### Current (Minimal) Build
```bash
./build.sh
# or
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
```

Produces: Minimal executable that shows library builds successfully

### Future (Full) Build
After installing Cocos2d-x and 7-Zip SDK:
```bash
# Update CMakeLists.txt to uncomment excluded sections
# Then build normally
./build.sh
```

Produces: Fully functional Kirikiroid2 application

## Dependencies Status

| Dependency | Required | Status | Notes |
|------------|----------|--------|-------|
| SDL2 | ✅ Yes | ✅ System | Window/input handling |
| OpenGL | ✅ Yes | ✅ System | Graphics rendering |
| FreeType | ✅ Yes | ✅ System | Font rendering |
| zlib | ✅ Yes | ✅ System | Compression |
| libpng | ✅ Yes | ✅ System | PNG images |
| libjpeg | ✅ Yes | ✅ System | JPEG images |
| Cocos2d-x | ✅ Yes | ❌ Missing | UI framework |
| 7-Zip SDK | ⚠️ Optional | ❌ Missing | 7z archive support |
| FFmpeg | ⚠️ Optional | ✅ System | Video playback |
| OpenAL | ⚠️ Optional | ✅ System | 3D audio |
| Opus | ⚠️ Optional | ✅ System | Audio codec |
| Vorbis | ⚠️ Optional | ✅ System | Audio codec |

## Next Steps

1. **For Developers:**
   - Integrate Cocos2d-x properly (highest priority)
   - Add 7-Zip SDK for archive support
   - Test on actual visual novel games
   - Implement missing Linux platform features

2. **For Users:**
   - Current build demonstrates successful compilation
   - Wait for Cocos2d-x integration for usable application
   - Or manually integrate dependencies following this guide

## Related Documentation

- [BUILD_LINUX.md](BUILD_LINUX.md) - Build instructions
- [CONTRIBUTING.md](CONTRIBUTING.md) - Development guide with vendor library info
- [CMakeLists.txt](CMakeLists.txt) - Build configuration with commented sections

## CI/CD

GitHub Actions workflow automatically builds this minimal configuration on:
- Ubuntu 20.04
- Ubuntu 22.04

Both Release and Debug builds are tested. Build artifacts are available for download from workflow runs.
