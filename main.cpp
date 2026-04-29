#include <iostream>
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
int main(int argc,char* argv[]){
    // Initalize SDL
    if (!SDL_Init(SDL_INIT_VIDEO)){
        std::cout << "Error Initalize Video !!!" << std::endl;
        return 1;
    }
    std::cout << "Video Initalized !" << std::endl;
    // Creating Window
    SDL_Window* window = SDL_CreateWindow("Hello SDL !!!",800,600,0);
    if (!window){
        std::cout << "Error Creating Window !!!" << std::endl;
        return 1;
    };
    std::cout << "Window Created !" << std::endl;

    // Game Loop
    bool running = true;
    SDL_Event event;
    std::cout << "Start GameLoop !" << std::endl;

    while(running){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_EVENT_QUIT){
                running = false;
            };
        };
    };
    // Clean Up
    std::cout << "Clean Up !" << std::endl;

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}