#pragma once
#define RELLX_LIB_VERSION_MAJOR 0
#define RELLX_LIB_VERSION_MINOR 0
#define RELLX_LIB_VERSION_PATCH 1
#define RELLX_LIB_VERSION_STRING "0.0.1"
#define RELLX_LIB_VERSION_STATUS "dev" // Version Statue : dev - alpha - beta - stable


#include "Core/Variants/Vector2.hpp"
#include "Core/GameLoop.hpp"
#include "Core/Utility.hpp"

#include "Servers/DisplayServer.hpp"
namespace Rellx{
    Rellx::GameLoop* CreateGameLoopInstance();
    void DestroyGameLoopInstance(Rellx::GameLoop* gameloop);
    
};