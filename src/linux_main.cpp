/**
 * Linux main entry point for Kirikiroid2
 * 
 * This is a minimal stub implementation that doesn't require Cocos2d-x.
 * When Cocos2d-x is available, replace this with the full implementation
 * that includes cocos2d/AppDelegate.h
 */

#include <iostream>

// Platform detection - ensure we're on Linux
#ifndef __linux__
#error "This file is intended for Linux builds only"
#endif

int main(int argc, char* argv[]) {
    // Print startup message
    std::cout << "Kirikiroid2 for Linux (Minimal Build)" << std::endl;
    std::cout << "Based on Kirikiri2/KirikiriZ" << std::endl;
    std::cout << "========================" << std::endl;
    std::cout << std::endl;
    std::cout << "This is a minimal build without Cocos2d-x integration." << std::endl;
    std::cout << "To run the full application, install Cocos2d-x and rebuild." << std::endl;
    std::cout << std::endl;
    std::cout << "See BUILD_LINUX.md and CONTRIBUTING.md for more information." << std::endl;
    
    // Parse command line arguments if provided
    if (argc > 1) {
        std::cout << std::endl << "Command line arguments:" << std::endl;
        for (int i = 1; i < argc; i++) {
            std::cout << "  Arg[" << i << "]: " << argv[i] << std::endl;
        }
    }
    
    return 0;
}
