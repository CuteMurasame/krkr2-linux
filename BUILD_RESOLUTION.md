# Build Issue Resolution - libarchive/archive.h Error

## Problem
The build was failing with:
```
/home/runner/work/krkr2-linux/krkr2-linux/src/core/base/UtilStreams.cpp:374:10: fatal error: libarchive/archive.h: No such file or directory
```

## Root Causes
1. **Include path**: Included `libarchive/archive.h` instead of the system `archive.h`
2. **Missing include directories**: libarchive headers not in compiler's search path
3. **Optional dependency not guarded**: Builds without libarchive still tried to include its headers

## Solutions Applied

### 1. Fixed Include Path (Commit 892c16c)
**File**: `src/core/base/UtilStreams.cpp`

Changed from the libarchive-prefixed headers:
```cpp
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>
```

To the system libarchive headers:
```cpp
#include <archive.h>
#include <archive_entry.h>
```

**Why**: libarchive typically installs headers as `archive.h` and `archive_entry.h`, not under a `libarchive/` subdirectory.

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

### 3. Guarded Optional Headers
**File**: `src/core/base/UtilStreams.cpp`

Wrapped libarchive includes with a compile-time guard:
```cpp
#ifdef HAVE_LIBARCHIVE
extern "C" {
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>
}
#endif
```

**File**: `CMakeLists.txt`

Defined the guard when libarchive is available:
```cmake
if(ARCHIVE_FOUND)
    target_compile_definitions(krkr2_core PRIVATE HAVE_LIBARCHIVE)
endif()
```

**Why**: Builds without libarchive should skip optional headers rather than fail to compile.

### 4. Dependency Configuration (Already Present)
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
4. ✅ Optional headers are only included when libarchive is present
5. ✅ Header files use the system libarchive include paths

## Additional Context
- This issue only occurred during CI builds, not local builds where paths might differ
- The fix follows the same pattern used for SDL2, FREETYPE, and other dependencies
- Both angle bracket syntax and global include directories were needed for the complete fix
