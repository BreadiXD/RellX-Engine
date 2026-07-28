#include "RellXLib.hpp"
#include "Core/Utility.hpp"
#include "Core/GameLoop.hpp"
#include "Core/FileSystem.hpp"
#include "SDL3/SDL.h"
//namespace Rellx{
//    class Rellx::GameLoop;
//};
namespace Rellx{
    void Initialize(){
        Memory::Initialize();
        SDL_Init(SDL_INIT_VIDEO);
        FileSystem::Initialize();
    };
    void CleanUp(){
        Memory::CleanUp();
        SDL_Quit();
    };

    Rellx::GameLoop* CreateGameLoopInstance(){
        RELLX_LOG("RellXLib v%s - %s",RELLX_LIB_VERSION_STRING,RELLX_LIB_VERSION_STATUS)
        return Rellx::Memory::New<Rellx::GameLoop>();
    };
    void DestroyGameLoopInstance(Rellx::GameLoop* gameloop){
        Rellx::Memory::Delete(gameloop);
    };

};
