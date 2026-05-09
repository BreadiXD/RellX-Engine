#include "RellXLib.hpp"
#include "Core/Utility.hpp"
#include "Core/GameLoop.hpp"
//namespace Rellx{
//    class Rellx::GameLoop;
//};
namespace Rellx{
    Rellx::GameLoop* CreateGameLoopInstance(){
        RELLX_LOG("RellXLib v%s - %s",RELLX_LIB_VERSION_STRING,RELLX_LIB_VERSION_STATUS)
        return Rellx::Memory::New<Rellx::GameLoop>();
    };
    void DestroyGameLoopInstance(Rellx::GameLoop* gameloop){
        Rellx::Memory::Delete(gameloop);
    };

};
