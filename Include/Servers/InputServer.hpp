#pragma once
#include "RellXLib.hpp"
// Display Server Is The Manager Of Any Thing You See In Screen ... Used For Creating Windows Etc..
class Rellx::GameLoop;
namespace Rellx{
    namespace Servers{
        struct InputServerData;

        class InputServer{
            private:
                Rellx::GameLoop* gameloop = nullptr;
                InputServerData* data = nullptr;

                void Initialize();
                void BeginFrame();
                void EndFrame();
                void CleanUp();
            public:

            friend class Rellx::GameLoop;
        };
    };
};