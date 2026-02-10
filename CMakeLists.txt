cmake_minimum_required(VERSION 3.10)
project(kirikiroid2 VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)

# Platform detection
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(WARNING "This CMake configuration is designed for Linux. Other platforms may not work correctly.")
endif()

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-inconsistent-missing-override")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
add_definitions(-DTJS_TEXT_OUT_CRLF -D__STDC_CONSTANT_MACROS -DUSE_UNICODE_FSTRING -Dtypeof=decltype)
add_definitions(-D_7ZIP_ST)

# Find required packages
find_package(PkgConfig REQUIRED)

# Core dependencies
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(OPENGL REQUIRED gl)
pkg_check_modules(FREETYPE REQUIRED freetype2)
pkg_check_modules(ZLIB REQUIRED zlib)
pkg_check_modules(PNG REQUIRED libpng)
pkg_check_modules(JPEG REQUIRED libjpeg)

# Optional dependencies (continue if not found)
pkg_check_modules(FFMPEG libavcodec libavformat libavutil libswscale libswresample)
pkg_check_modules(OPENAL openal)
pkg_check_modules(OPUS opus opusfile)
pkg_check_modules(VORBIS vorbis vorbisfile)
pkg_check_modules(CAIRO cairo)
pkg_check_modules(PIXMAN pixman-1)
pkg_check_modules(EXPAT expat)
pkg_check_modules(ARCHIVE libarchive)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src/core/base
    ${CMAKE_SOURCE_DIR}/src/core/base/win32
    ${CMAKE_SOURCE_DIR}/src/core/environ
    ${CMAKE_SOURCE_DIR}/src/core/environ/win32
    ${CMAKE_SOURCE_DIR}/src/core/environ/android
    ${CMAKE_SOURCE_DIR}/src/core/environ/linux
    ${CMAKE_SOURCE_DIR}/src/core/environ/sdl
    ${CMAKE_SOURCE_DIR}/src/core/msg
    ${CMAKE_SOURCE_DIR}/src/core/msg/win32
    ${CMAKE_SOURCE_DIR}/src/core/extension
    ${CMAKE_SOURCE_DIR}/src/core/sound
    ${CMAKE_SOURCE_DIR}/src/core/sound/win32
    ${CMAKE_SOURCE_DIR}/src/core/tjs2
    ${CMAKE_SOURCE_DIR}/src/core/utils
    ${CMAKE_SOURCE_DIR}/src/core/utils/win32
    ${CMAKE_SOURCE_DIR}/src/core/visual
    ${CMAKE_SOURCE_DIR}/src/core/visual/win32
    ${CMAKE_SOURCE_DIR}/src/core/visual/gl
    ${CMAKE_SOURCE_DIR}/src/core/visual/ogl
    ${CMAKE_SOURCE_DIR}/src/plugins
    ${SDL2_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
)

# Source files - Base
file(GLOB BASE_SOURCES 
    "src/core/base/*.cpp"
)
# Exclude 7zArchive.cpp as it requires external 7zip SDK not included in repo
list(FILTER BASE_SOURCES EXCLUDE REGEX ".*/7zArchive\\.cpp$")

# 7zip SDK sources - commented out as not included in repository
# When 7zip SDK is added to src/core/base/7zip/, uncomment these lines:
# file(GLOB BASE_7ZIP_C_SOURCES 
#     "src/core/base/7zip/*.c"
#     "src/core/base/7zip/C/*.c"
# )
# file(GLOB_RECURSE BASE_7ZIP_CPP_SOURCES 
#     "src/core/base/7zip/CPP/*.cpp"
# )
# list(APPEND BASE_SOURCES ${BASE_7ZIP_C_SOURCES} ${BASE_7ZIP_CPP_SOURCES})

# Source files - Base win32 (some compatibility code)
file(GLOB BASE_WIN32_SOURCES "src/core/base/win32/*.cpp")
list(FILTER BASE_WIN32_SOURCES EXCLUDE REGEX ".*/(FuncStubs|SusieArchive)\\.cpp$")

# Source files - Environ
# Most environ files depend on Cocos2d-x which is not included
# Only include files that don't have Cocos2d-x dependencies
set(ENVIRON_SOURCES
    "src/core/environ/Application.cpp"
    "src/core/environ/DetectCPU.cpp"
)

# Cocos2d-x sources - commented out as Cocos2d-x is not included in repository
# When Cocos2d-x is installed, add these back and add find_package(Cocos2d-x)
# file(GLOB ENVIRON_COCOS2D_SOURCES "src/core/environ/cocos2d/*.cpp")
# file(GLOB ENVIRON_UI_SOURCES 
#     "src/core/environ/ui/*.cpp"
#     "src/core/environ/ui/extension/*.cpp"
# )
# And add: DumpSend.cpp, MainFormUnit.cpp, XP3ArchiveRepack.cpp (requires 7zip too)

file(GLOB ENVIRON_LINUX_SOURCES "src/core/environ/linux/*.cpp")

list(APPEND ENVIRON_SOURCES 
    ${ENVIRON_LINUX_SOURCES}
    src/core/environ/win32/SystemControl.cpp
)

# Source files - Extension
file(GLOB EXTENSION_SOURCES "src/core/extension/*.cpp")

# Source files - Movie
file(GLOB MOVIE_SOURCES "src/core/movie/*.cpp")
file(GLOB_RECURSE MOVIE_SUB_SOURCES "src/core/movie/*/*.cpp")
list(APPEND MOVIE_SOURCES ${MOVIE_SUB_SOURCES})

# Source files - Msg
file(GLOB MSG_SOURCES "src/core/msg/*.cpp")
list(APPEND MSG_SOURCES 
    src/core/msg/win32/MsgImpl.cpp
    src/core/msg/win32/OptionsDesc.cpp
)

# Source files - Sound
file(GLOB SOUND_SOURCES "src/core/sound/*.cpp")
list(FILTER SOUND_SOURCES EXCLUDE REGEX ".*/(xmmlib|WaveFormatConverter_SSE)\\.cpp$")
file(GLOB SOUND_WIN32_SOURCES "src/core/sound/win32/*.cpp")
list(APPEND SOUND_SOURCES ${SOUND_WIN32_SOURCES})

# Source files - TJS2
file(GLOB TJS2_SOURCES "src/core/tjs2/*.cpp")

# Source files - Utils
file(GLOB UTILS_SOURCES 
    "src/core/utils/*.c"
    "src/core/utils/*.cpp"
    "src/core/utils/encoding/*.c"
    "src/core/utils/minizip/*.c"
    "src/core/utils/minizip/*.cpp"
    "src/core/utils/win32/*.cpp"
)

# Source files - Visual
file(GLOB VISUAL_SOURCES "src/core/visual/*.cpp")
list(FILTER VISUAL_SOURCES EXCLUDE REGEX ".*/Resampler\\.cpp$")
file(GLOB VISUAL_GL_SOURCES "src/core/visual/gl/*.cpp")
file(GLOB VISUAL_OGL_SOURCES "src/core/visual/ogl/*.cpp")
file(GLOB VISUAL_WIN32_SOURCES "src/core/visual/win32/*.cpp")
list(FILTER VISUAL_WIN32_SOURCES EXCLUDE REGEX ".*/(GDIFontRasterizer|NativeFreeTypeFace|TVPSysFont|VSyncTimingThread)\\.cpp$")
list(APPEND VISUAL_SOURCES 
    ${VISUAL_GL_SOURCES}
    ${VISUAL_OGL_SOURCES}
    ${VISUAL_WIN32_SOURCES}
)

# Combine all sources
set(KRKR2_SOURCES
    ${BASE_SOURCES}
    ${BASE_WIN32_SOURCES}
    ${ENVIRON_SOURCES}
    ${EXTENSION_SOURCES}
    ${MOVIE_SOURCES}
    ${MSG_SOURCES}
    ${SOUND_SOURCES}
    ${TJS2_SOURCES}
    ${UTILS_SOURCES}
    ${VISUAL_SOURCES}
)

# Create the library
add_library(krkr2_core STATIC ${KRKR2_SOURCES})

target_include_directories(krkr2_core PUBLIC
    ${CMAKE_SOURCE_DIR}/src/core
)

target_link_libraries(krkr2_core
    ${SDL2_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${FREETYPE_LIBRARIES}
    ${ZLIB_LIBRARIES}
    ${PNG_LIBRARIES}
    ${JPEG_LIBRARIES}
    pthread
    dl
    m
)

# Add optional libraries
if(FFMPEG_FOUND)
    target_include_directories(krkr2_core PUBLIC ${FFMPEG_INCLUDE_DIRS})
    target_link_libraries(krkr2_core ${FFMPEG_LIBRARIES})
    add_definitions(-DHAVE_FFMPEG)
endif()

if(OPENAL_FOUND)
    target_include_directories(krkr2_core PUBLIC ${OPENAL_INCLUDE_DIRS})
    target_link_libraries(krkr2_core ${OPENAL_LIBRARIES})
    add_definitions(-DHAVE_OPENAL)
endif()

if(OPUS_FOUND)
    target_include_directories(krkr2_core PUBLIC ${OPUS_INCLUDE_DIRS})
    target_link_libraries(krkr2_core ${OPUS_LIBRARIES})
    add_definitions(-DHAVE_OPUS)
endif()

if(VORBIS_FOUND)
    target_include_directories(krkr2_core PUBLIC ${VORBIS_INCLUDE_DIRS})
    target_link_libraries(krkr2_core ${VORBIS_LIBRARIES})
    add_definitions(-DHAVE_VORBIS)
endif()

if(CAIRO_FOUND)
    target_include_directories(krkr2_core PUBLIC ${CAIRO_INCLUDE_DIRS})
    target_link_libraries(krkr2_core ${CAIRO_LIBRARIES})
endif()

if(PIXMAN_FOUND)
    target_include_directories(krkr2_core PUBLIC ${PIXMAN_INCLUDE_DIRS})
    target_link_libraries(krkr2_core ${PIXMAN_LIBRARIES})
endif()

if(EXPAT_FOUND)
    target_include_directories(krkr2_core PUBLIC ${EXPAT_INCLUDE_DIRS})
    target_link_libraries(krkr2_core ${EXPAT_LIBRARIES})
endif()

if(ARCHIVE_FOUND)
    target_include_directories(krkr2_core PUBLIC ${ARCHIVE_INCLUDE_DIRS})
    target_link_libraries(krkr2_core ${ARCHIVE_LIBRARIES})
endif()

# Main executable
add_executable(kirikiroid2 src/linux_main.cpp)
target_link_libraries(kirikiroid2 krkr2_core)

# Install targets
install(TARGETS kirikiroid2 DESTINATION bin)
install(DIRECTORY cocos/kr2/Resources DESTINATION share/kirikiroid2)

message(STATUS "==================================")
message(STATUS "Kirikiroid2 Linux Build Configuration")
message(STATUS "==================================")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "SDL2: ${SDL2_FOUND}")
message(STATUS "OpenGL: ${OPENGL_FOUND}")
message(STATUS "FreeType: ${FREETYPE_FOUND}")
message(STATUS "FFmpeg: ${FFMPEG_FOUND}")
message(STATUS "OpenAL: ${OPENAL_FOUND}")
message(STATUS "Opus: ${OPUS_FOUND}")
message(STATUS "Vorbis: ${VORBIS_FOUND}")
message(STATUS "Cairo: ${CAIRO_FOUND}")
message(STATUS "Pixman: ${PIXMAN_FOUND}")
message(STATUS "Expat: ${EXPAT_FOUND}")
message(STATUS "LibArchive: ${ARCHIVE_FOUND}")
message(STATUS "==================================")
