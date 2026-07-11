#pragma once

#include "Core/Utility.hpp"
namespace Rellx{
    namespace Variants{
        struct Color{
            Rellx::Types::Reel r,g,b,a;
            Color();
            Color(Rellx::Types::Reel r);
            Color(Rellx::Types::Reel r,Rellx::Types::Reel g,Rellx::Types::Reel b);
            Color(Rellx::Types::Reel r,Rellx::Types::Reel g,Rellx::Types::Reel b,Rellx::Types::Reel a);
            
        };
    };
};
