# Build Fix: Missing Protect.h

## Issue

The build was failing with the following error:

```
/home/runner/work/krkr2-linux/krkr2-linux/src/core/base/SysInitIntf.cpp:21:10: fatal error: Protect.h: No such file or directory
   21 | #include "Protect.h"
      |          ^~~~~~~~~~~
compilation terminated.
```

## Root Cause

The `Protect.h` header file was missing from the repository. This file provides DRM/protection functionality that is:
- Platform-specific (primarily for Windows/commercial builds)
- Not essential for Linux open-source builds
- Used conditionally in `SysInitIntf.cpp` for system initialization

## Solution

Created a stub implementation at `src/core/base/Protect.h` with:

```cpp
inline bool TVPProtectInit(void)
{
    // No-op protection initialization for Linux
    // Always return true to allow system initialization to proceed
    return true;
}

inline void TVPUpdateLicense(void)
{
    // No-op license update for Linux
}
```

## Impact

- ✅ Build now compiles successfully
- ✅ System initialization proceeds normally
- ✅ No functionality lost (protection system not used on Linux)
- ✅ Minimal change - single stub header file added

## Testing

The fix allows `SysInitIntf.cpp` to compile, which was the blocking issue. The stub functions are only called during system initialization and return success immediately, allowing the build process to continue.

## Files Changed

- `src/core/base/Protect.h` (new file) - Stub protection system interface

## Related Code

The protection system is referenced in:
- `src/core/base/SysInitIntf.cpp` - System initialization
- `src/core/base/XP3Archive.cpp` - Protected storage flags (different feature)

Only `SysInitIntf.cpp` required the missing header file.
