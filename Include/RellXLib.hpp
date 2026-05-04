#pragma once
#define RELLX_LIB_VERSION_MAJOR 0
#define RELLX_LIB_VERSION_MINOR 0
#define RELLX_LIB_VERSION_PATCH 1
#define RELLX_LIB_VERSION_STRING "0.0.1"
// Version Statue : dev - alpha - beta - stable
#define RELLX_LIB_VERSION_STATUE "dev"
#include "Core/GameLoop.hpp"


namespace Rellx{
    Rellx::GameLoop* CreateGameLoopInstance();
    
};