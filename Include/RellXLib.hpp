#pragma once
#define RELLX_LIB_VERSION_MAJOR 0
#define RELLX_LIB_VERSION_MINOR 0
#define RELLX_LIB_VERSION_PATCH 2
#define RELLX_LIB_VERSION_STRING "0.0.2"
#define RELLX_LIB_VERSION_STATUS "Dev" // Version Statue : Dev - Alpha - Beta - Stable


#include "Core/Variants/Vector2.hpp"
#include "Core/Variants/Color.hpp"
#include "Core/GameLoop.hpp"
#include "Core/Utility.hpp"

#include "Interfaces/IRenderer.hpp"
#include "Renderer/OpenGL33RD.hpp"

#include "Servers/DisplayServer.hpp"
#include "Servers/RenderingServer.hpp"


namespace Rellx{
    void Initialize();
    void CleanUp();

    Rellx::GameLoop* CreateGameLoopInstance();
    void DestroyGameLoopInstance(Rellx::GameLoop* gameloop);
    
};