#pragma once
#define RELLX_LIB_VERSION_MAJOR 0
#define RELLX_LIB_VERSION_MINOR 0
#define RELLX_LIB_VERSION_PATCH 2
#define RELLX_LIB_VERSION_STRING "0.0.2"
#define RELLX_LIB_VERSION_STATUS "Dev" // Version Statue : Dev - Alpha - Beta - Stable


#include "Core/Variants.hpp"
#include "Core/GameLoop.hpp"
#include "Core/Utility.hpp"
#include "Core/FileSystem.hpp"

#include "Interfaces/IRenderer.hpp"
#include "Renderer/OpenGL33RD.hpp"

#include "Servers/DisplayServer.hpp"
#include "Servers/RenderingServer.hpp"
#include "Servers/SceneServer.hpp"
#include "Servers/InputServer.hpp"
#include "Servers/AssetsServer.hpp"

#ifdef RELLX_EDITOR
#include "Servers/EditorServer.hpp"
#endif





namespace Rellx{
    void Initialize();
    void CleanUp();

    Rellx::GameLoop* CreateGameLoopInstance();
    void DestroyGameLoopInstance(Rellx::GameLoop* gameloop);
    
};