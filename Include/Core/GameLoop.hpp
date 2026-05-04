#pragma once
#include "Core/Utility.hpp"
#include "Servers/DisplayServer.hpp"
/*
    GameLoop Is Main Application Startup That Will Manage Every Action Happend In The Program
    And Give A Way To Control Low Level Stuff With Readable APIs
*/
namespace Rellx{
    class GameLoop{
        private:
            Rellx::Servers::DisplayServer displayServer;
            bool running;
        public:
            void Initalize();
            //Rellx::Error Update();
            void Update();
            void CleanUp();
            void Quit();
            bool IsRunning() const;
            Rellx::Servers::DisplayServer* GetDisplayServer();

    };    
};