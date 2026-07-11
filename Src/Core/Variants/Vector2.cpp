#include "Core/Variants/Vector2.hpp"

namespace Rellx{
    namespace Variants{
        // Vector2f
        Vector2f::Vector2f() : x(0.0f),y(0.0f){};
        Vector2f::Vector2f(Rellx::Types::Reel x,Rellx::Types::Reel y) : x(x),y(y){};
        // Vector2i
        Vector2i::Vector2i() : x(0.0f),y(0.0f){};
        Vector2i::Vector2i(Rellx::Types::Int x,Rellx::Types::Int y) : x(x),y(y){};
        // Vector2u
        Vector2u::Vector2u() : x(0.0f),y(0.0f){};
        Vector2u::Vector2u(Rellx::Types::Uint x,Rellx::Types::Uint y) : x(x),y(y){};

    };
};
