/**
 * Linux main entry point for Kirikiroid2
 * 
 * This file provides the main() function for the Linux build.
 * It can build with or without Cocos2d-x depending on availability.
 */

#include <iostream>

// Check if Cocos2d-x support is enabled at build time
#ifdef HAVE_COCOS2DX

#include <SDL2/SDL.h>
#include <thread>
#include "cocos2d/AppDelegate.h"
#include "Application.h"

// External symbols
extern "C" void SDL_SetMainReady(void);
extern std::thread::id TVPMainThreadID;

#endif // HAVE_COCOS2DX

// Platform detection - ensure we're on Linux
#ifndef __linux__
#error "This file is intended for Linux builds only"
#endif

int main(int argc, char* argv[]) {
    // Print startup message
    std::cout << "Kirikiroid2 for Linux" << std::endl;
    std::cout << "Based on Kirikiri2/KirikiriZ" << std::endl;
    std::cout << "========================" << std::endl;
    
#ifdef HAVE_COCOS2DX
    // Full version with Cocos2d-x
    std::cout << "Running with Cocos2d-x support" << std::endl;
    
    // Parse command line arguments if needed
    for (int i = 1; i < argc; i++) {
        std::cout << "Arg[" << i << "]: " << argv[i] << std::endl;
    }
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    // Tell SDL that we've initialized it
    SDL_SetMainReady();
    
    // Set the main thread ID for the application
    TVPMainThreadID = std::this_thread::get_id();
    
    // Create the application delegate
    // The TVPAppDelegate instance registers itself with Cocos2d-x's singleton system
    static TVPAppDelegate app;
    
    // Run the application
    // Note: Cocos2d-x Application::run() handles the main event loop
    // The app instance created above is accessible via Application::getInstance()
    int ret = app.run();
    
    // Cleanup SDL
    SDL_Quit();
    
    return ret;
#else
    // Minimal version without Cocos2d-x
    std::cout << "Built without Cocos2d-x - core library only" << std::endl;
    std::cout << std::endl;
    std::cout << "This build demonstrates successful compilation of the core engine." << std::endl;
    std::cout << "For full functionality, install Cocos2d-x and rebuild." << std::endl;
    std::cout << std::endl;
    std::cout << "See BUILD_LINUX.md and BUILD_STATUS.md for more information." << std::endl;
    
    // Parse command line arguments if provided
    if (argc > 1) {
        std::cout << std::endl << "Command line arguments:" << std::endl;
        for (int i = 1; i < argc; i++) {
            std::cout << "  Arg[" << i << "]: " << argv[i] << std::endl;
        }
    }
    
    return 0;
#endif
}
