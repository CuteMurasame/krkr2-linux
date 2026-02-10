/**
 * Linux main entry point for Kirikiroid2
 * 
 * This file provides the main() function for the Linux build,
 * initializing the application and starting the Cocos2d-x engine.
 */

#include <SDL2/SDL.h>
#include <iostream>
#include <thread>
#include "cocos2d/AppDelegate.h"
#include "Application.h"

// External symbols
extern "C" void SDL_SetMainReady(void);
extern std::thread::id TVPMainThreadID;

// Platform detection - ensure we're on Linux
#ifndef __linux__
#error "This file is intended for Linux builds only"
#endif

int main(int argc, char* argv[]) {
    // Print startup message
    std::cout << "Kirikiroid2 for Linux" << std::endl;
    std::cout << "Based on Kirikiri2/KirikiriZ" << std::endl;
    std::cout << "========================" << std::endl;
    
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
    TVPAppDelegate app;
    
    // Run the application
    // Note: Cocos2d-x Application::run() handles the main event loop
    int ret = cocos2d::Application::getInstance()->run();
    
    // Cleanup SDL
    SDL_Quit();
    
    return ret;
}
