#pragma once

#include "Core/Utility.hpp"
namespace Rellx{
    namespace Variants{
        struct Vector2f{
            Rellx::Types::Reel x;
            Rellx::Types::Reel y;
            Vector2f();
            Vector2f(Rellx::Types::Reel x,Rellx::Types::Reel y);
        };
        struct Vector2i{
            Rellx::Types::Int x;
            Rellx::Types::Int y;
            Vector2i();
            Vector2i(Rellx::Types::Int x,Rellx::Types::Int y);

        };
        struct Vector2u{
            Rellx::Types::Uint x;
            Rellx::Types::Uint y;
            Vector2u();
            Vector2u(Rellx::Types::Uint x,Rellx::Types::Uint y);

        };
    };
};
