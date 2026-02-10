# Developer Guide

## Contributing to Kirikiroid2 Linux Port

This guide is for developers who want to contribute to the Linux port of Kirikiroid2.

## Project Structure

```
krkr2-linux/
├── src/
│   ├── core/                 # Core engine code
│   │   ├── base/             # Base utilities, 7zip, etc.
│   │   ├── environ/          # Platform-specific code
│   │   │   ├── android/      # Android platform
│   │   │   ├── linux/        # Linux platform (expand this!)
│   │   │   ├── win32/        # Windows compatibility layer
│   │   │   ├── cocos2d/      # Cocos2d-x integration
│   │   │   └── ui/           # UI components
│   │   ├── extension/        # Engine extensions
│   │   ├── movie/            # Video playback
│   │   ├── msg/              # Messaging system
│   │   ├── sound/            # Audio engine
│   │   ├── tjs2/             # TJS2 scripting engine
│   │   ├── utils/            # Utilities
│   │   └── visual/           # Graphics/rendering
│   ├── plugins/              # Plugin system
│   └── linux_main.cpp        # Linux entry point
├── project/
│   └── android/              # Android project files
├── cocos/                    # Cocos2d-x resources
├── CMakeLists.txt            # CMake build configuration
├── build.sh                  # Build automation script
└── BUILD_LINUX.md            # Build documentation
```

## Development Workflow

### Setting Up Development Environment

1. Install all dependencies (see BUILD_LINUX.md)
2. Install development tools:
   ```bash
   # Ubuntu/Debian
   sudo apt-get install build-essential gdb valgrind git
   
   # Additional useful tools
   sudo apt-get install clang-format clang-tidy cppcheck
   ```

3. Clone and build:
   ```bash
   git clone https://github.com/CuteMurasame/krkr2-linux.git
   cd krkr2-linux
   ./build.sh -d  # Debug build
   ```

### Building for Development

```bash
# Debug build with all symbols
./build.sh -d -c

# Or manually with CMake
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
make -j$(nproc)
```

The `CMAKE_EXPORT_COMPILE_COMMANDS` generates `compile_commands.json` for IDE integration.

### Code Style

The project uses a mix of styles due to its origins. For new code:

- **C++**: Follow existing style in the file you're modifying
- **Indentation**: Tabs or 4 spaces (match existing code)
- **Braces**: K&R style preferred
- **Naming**: 
  - Classes: `TVPClassName` or `ClassName`
  - Functions: `FunctionName` or `functionName`
  - Variables: `camelCase` or `snake_case` (match context)

### Key Areas for Development

#### 1. Platform Abstraction (`src/core/environ/linux/`)

Currently minimal. Needs expansion:
- Window management
- File system access
- System dialogs
- Input handling
- Clipboard operations

**Example**: Adding a Linux-specific function
```cpp
// In src/core/environ/linux/Platform.cpp
void TVPGetSystemInfo(TVPSystemInfo &info) {
    // Linux implementation using /proc, uname, etc.
}
```

#### 2. Dependency Integration

Many dependencies are referenced but not integrated:
- Cocos2d-x (critical - provides rendering/windowing)
- FFmpeg (video playback)
- OpenAL (3D audio)
- Various codec libraries

**To add a dependency:**
1. Update CMakeLists.txt with `pkg_check_modules`
2. Add include directories
3. Link the library
4. Add conditional compilation flags

#### 3. Build System Improvements

Current CMakeLists.txt is basic. Improvements needed:
- Better dependency management
- Support for system vs. bundled libraries
- Optional feature flags
- Install targets for resources
- CPack packaging support

#### 4. Testing

Currently no automated tests. Needed:
- Unit tests for core utilities
- Integration tests for platform code
- Regression tests for games

**Suggested framework**: Google Test or Catch2

```cmake
# Add to CMakeLists.txt
enable_testing()
add_subdirectory(tests)
```

### Debugging

#### Using GDB

```bash
# Build with debug symbols
./build.sh -d

# Run with GDB
gdb ./build/kirikiroid2

# Common GDB commands
(gdb) break main
(gdb) run
(gdb) backtrace
(gdb) print variable_name
```

#### Valgrind for Memory Leaks

```bash
valgrind --leak-check=full --show-leak-kinds=all ./build/kirikiroid2
```

#### Address Sanitizer

```bash
# Add to CMakeLists.txt or use:
cmake -DCMAKE_CXX_FLAGS="-fsanitize=address -g" \
      -DCMAKE_C_FLAGS="-fsanitize=address -g" ..
make
./kirikiroid2
```

### Platform-Specific Notes

#### Missing Dependencies

The original project expects many vendor libraries in `vendor/` that aren't included:
- `vendor/cocos2d-x/` - **Critical**: Must be obtained separately
- `vendor/freetype/`
- `vendor/ffmpeg/`
- etc.

**Workaround**: Use system libraries where possible (CMakeLists.txt does this).

**Cocos2d-x Integration**: Priority task
```bash
# One approach
git clone https://github.com/cocos2d/cocos2d-x.git vendor/cocos2d-x/current
cd vendor/cocos2d-x/current
git checkout v3.17.2
```

Then update CMakeLists.txt to find and link Cocos2d-x.

#### Compatibility Layer

Many files in `src/core/*/win32/` provide Windows compatibility:
- Some can be used as-is on Linux
- Some need Linux alternatives
- Some can be stubbed out

When porting, check if:
1. A Linux version exists in `environ/linux/`
2. A POSIX version works
3. A new implementation is needed

### Contribution Guidelines

1. **Fork** the repository
2. **Create a branch** for your feature: `git checkout -b feature/my-feature`
3. **Make changes** with clear, focused commits
4. **Test** your changes (manual testing for now)
5. **Document** new features or changes
6. **Submit a PR** with:
   - Description of changes
   - Why the change is needed
   - How you tested it
   - Any breaking changes

### Known Issues / TODO

See GitHub Issues for the full list. Key items:

- [ ] Integrate Cocos2d-x properly
- [ ] Complete Linux platform layer
- [ ] Add plugin support
- [ ] Implement resource loading
- [ ] Audio system integration
- [ ] Video playback support
- [ ] File dialog implementation
- [ ] Configuration UI
- [ ] Save/load system testing
- [ ] Multi-monitor support
- [ ] Gamepad/controller support
- [ ] Accessibility features

### Resources

- **Original KiriKiri**: http://kikyou.info/tvp/
- **KirikiriZ**: https://github.com/krkrz/krkrz
- **Cocos2d-x**: https://github.com/cocos2d/cocos2d-x
- **SDL2**: https://wiki.libsdl.org/
- **CMake**: https://cmake.org/documentation/

### Getting Help

- Open an issue on GitHub
- Check existing issues and PRs
- Review the original Kirikiri documentation (mostly Japanese)

### License

See LICENSE file. Kirikiroid2 inherits licenses from:
- Kirikiri2/KirikiriZ
- Cocos2d-x
- Various dependencies

Ensure your contributions are compatible with these licenses.
