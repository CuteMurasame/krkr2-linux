#!/bin/bash
#
# Build script for Kirikiroid2 on Linux
# This script automates the build process
#

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Print with color
print_info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

print_warn() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Check if a command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Detect distribution
detect_distro() {
    if [ -f /etc/os-release ]; then
        . /etc/os-release
        echo "$ID"
    else
        echo "unknown"
    fi
}

# Check dependencies
check_dependencies() {
    print_info "Checking build dependencies..."
    
    local missing_deps=0
    
    if ! command_exists cmake; then
        print_error "CMake is not installed"
        missing_deps=1
    fi
    
    if ! command_exists pkg-config; then
        print_error "pkg-config is not installed"
        missing_deps=1
    fi
    
    if ! command_exists g++ && ! command_exists clang++; then
        print_error "No C++ compiler found (g++ or clang++)"
        missing_deps=1
    fi
    
    # Check for SDL2
    if ! pkg-config --exists sdl2; then
        print_error "SDL2 development files not found"
        missing_deps=1
    fi
    
    # Check for OpenGL
    if ! pkg-config --exists gl; then
        print_warn "OpenGL development files not found (may be required)"
    fi
    
    # Check for FreeType
    if ! pkg-config --exists freetype2; then
        print_error "FreeType2 development files not found"
        missing_deps=1
    fi
    
    if [ $missing_deps -eq 1 ]; then
        print_error "Missing required dependencies. Please install them first."
        print_info "See BUILD_LINUX.md for installation instructions."
        return 1
    fi
    
    print_info "All required dependencies found!"
    return 0
}

# Show help
show_help() {
    cat << EOF
Kirikiroid2 Linux Build Script

Usage: $0 [OPTIONS]

OPTIONS:
    -h, --help          Show this help message
    -c, --clean         Clean build directory before building
    -d, --debug         Build in Debug mode (default: Release)
    -j, --jobs N        Use N parallel jobs (default: number of CPU cores)
    -i, --install       Install after building
    --check-deps        Only check dependencies and exit
    --install-deps      Attempt to install dependencies (requires sudo)

EXAMPLES:
    $0                  # Build in Release mode
    $0 -d               # Build in Debug mode
    $0 -c               # Clean and build
    $0 -j 4             # Build with 4 parallel jobs
    $0 --check-deps     # Check if dependencies are installed

EOF
}

# Install dependencies
install_dependencies() {
    local distro=$(detect_distro)
    print_info "Detected distribution: $distro"
    
    case "$distro" in
        ubuntu|debian)
            print_info "Installing dependencies for Ubuntu/Debian..."
            sudo apt-get update
            sudo apt-get install -y \
                build-essential cmake git pkg-config \
                libsdl2-dev libgl1-mesa-dev libfreetype6-dev \
                zlib1g-dev libpng-dev libjpeg-dev
            ;;
        fedora|rhel|centos)
            print_info "Installing dependencies for Fedora/RHEL/CentOS..."
            sudo dnf install -y \
                gcc gcc-c++ cmake git pkgconfig \
                SDL2-devel mesa-libGL-devel freetype-devel \
                zlib-devel libpng-devel libjpeg-turbo-devel
            ;;
        arch|manjaro)
            print_info "Installing dependencies for Arch Linux..."
            sudo pacman -S --needed \
                base-devel cmake git \
                sdl2 mesa freetype2 zlib libpng libjpeg-turbo
            ;;
        *)
            print_error "Unknown distribution. Please install dependencies manually."
            print_info "See BUILD_LINUX.md for more information."
            return 1
            ;;
    esac
    
    print_info "Dependencies installed successfully!"
}

# Main build function
build() {
    local BUILD_TYPE="Release"
    local CLEAN=0
    local JOBS=$(nproc)
    local INSTALL=0
    
    # Parse arguments
    while [[ $# -gt 0 ]]; do
        case $1 in
            -h|--help)
                show_help
                exit 0
                ;;
            -c|--clean)
                CLEAN=1
                shift
                ;;
            -d|--debug)
                BUILD_TYPE="Debug"
                shift
                ;;
            -j|--jobs)
                JOBS="$2"
                shift 2
                ;;
            -i|--install)
                INSTALL=1
                shift
                ;;
            --check-deps)
                check_dependencies
                exit $?
                ;;
            --install-deps)
                install_dependencies
                exit $?
                ;;
            *)
                print_error "Unknown option: $1"
                show_help
                exit 1
                ;;
        esac
    done
    
    # Check dependencies first
    if ! check_dependencies; then
        print_info "Hint: Run '$0 --install-deps' to attempt automatic installation"
        exit 1
    fi
    
    # Clean if requested
    if [ $CLEAN -eq 1 ] && [ -d "build" ]; then
        print_info "Cleaning build directory..."
        rm -rf build
    fi
    
    # Create build directory
    if [ ! -d "build" ]; then
        print_info "Creating build directory..."
        mkdir build
    fi
    
    # Configure
    print_info "Configuring with CMake (Build type: $BUILD_TYPE)..."
    cd build
    cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
    
    # Build
    print_info "Building with $JOBS parallel jobs..."
    make -j$JOBS
    
    print_info "Build completed successfully!"
    print_info "Executable: build/kirikiroid2"
    
    # Install if requested
    if [ $INSTALL -eq 1 ]; then
        print_info "Installing..."
        sudo make install
        print_info "Installation completed!"
    else
        print_info "To install, run: sudo make install"
        print_info "Or run: $0 --install"
    fi
    
    cd ..
}

# Run main build function
build "$@"
