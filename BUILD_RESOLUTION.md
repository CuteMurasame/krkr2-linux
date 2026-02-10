# Build Issue Resolution - libarchive/archive.h Error

## Problem
The build was failing with:
```
/home/runner/work/krkr2-linux/krkr2-linux/src/core/base/UtilStreams.cpp:374:10: fatal error: libarchive/archive.h: No such file or directory
```

## Root Causes
1. **Include syntax**: Used quoted includes instead of angle brackets for system headers
2. **Missing include directories**: libarchive headers not in compiler's search path
3. **CMake configuration**: Include directories added to target after compilation started

## Solutions Applied

### 1. Fixed Include Syntax (Commit 892c16c)
**File**: `src/core/base/UtilStreams.cpp`

Changed from quoted includes:
```cpp
#include "libarchive/archive.h"
#include "libarchive/archive_entry.h"
```

To angle bracket includes:
```cpp
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>
```

**Why**: Angle brackets tell the compiler to search system include paths, while quotes search local directories first.

### 2. Added Include Directories (Commit cff04ca)
**File**: `CMakeLists.txt`

Added `${ARCHIVE_INCLUDE_DIRS}` to the global `include_directories()` call:
```cmake
include_directories(
    ...
    ${SDL2_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
    ${ARCHIVE_INCLUDE_DIRS}  # Added this line
)
```

**Why**: The include directories must be available globally before source files are compiled. Previously, they were only added to `target_include_directories` after the target was created, which was too late.

### 3. Dependency Configuration (Already Present)
**File**: `.github/workflows/build.yml`
- `libarchive-dev` package is installed

**File**: `CMakeLists.txt`
- `pkg_check_modules(ARCHIVE libarchive)` detects the library
- Library is linked when found: `target_link_libraries(krkr2_core ${ARCHIVE_LIBRARIES})`

## Verification
The build should now succeed because:
1. ✅ libarchive-dev is installed by GitHub Actions
2. ✅ pkg-config finds libarchive and sets ARCHIVE_INCLUDE_DIRS
3. ✅ Include directories are added globally before compilation
4. ✅ Header files use proper system include syntax

## Additional Context
- This issue only occurred during CI builds, not local builds where paths might differ
- The fix follows the same pattern used for SDL2, FREETYPE, and other dependencies
- Both angle bracket syntax and global include directories were needed for the complete fix
