#include "Core/Variants/Color.hpp"

namespace Rellx{
    namespace Variants{
        Color::Color() : r(1.0f),g(1.0f),b(1.0f),a(1.0f){};
        Color::Color(Rellx::Types::Reel r) : r(r),g(r),b(r),a(1.0f){};
        Color::Color(Rellx::Types::Reel r,Rellx::Types::Reel g,Rellx::Types::Reel b) : r(r),g(g),b(b),a(1.0f){};
        Color::Color(Rellx::Types::Reel r,Rellx::Types::Reel g,Rellx::Types::Reel b,Rellx::Types::Reel a) : r(r),g(g),b(b),a(a){};
    };
};
