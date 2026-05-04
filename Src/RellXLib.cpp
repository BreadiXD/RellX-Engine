#include "RellXLib.hpp"
#include "Core/Utility.hpp"
#include "Core/GameLoop.hpp"
//namespace Rellx{
//    class Rellx::GameLoop;
//};
namespace Rellx{
    Rellx::GameLoop* CreateGameLoopInstance(){
        RELLX_LOG("RellXLib v%d.%d.%d - %s",RELLX_LIB_VERSION_MAJOR,RELLX_LIB_VERSION_MINOR,RELLX_LIB_VERSION_PATCH,RELLX_LIB_VERSION_STATUE)
        RELLX_LOG("RellXLib v%s - %s",RELLX_LIB_VERSION_STRING,RELLX_LIB_VERSION_STATUE)
        
        return Rellx::Memory::New<Rellx::GameLoop>();
    };
};
