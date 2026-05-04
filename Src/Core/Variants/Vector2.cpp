#include "Core/Variants/Vector2.hpp"

namespace Rellx{
    namespace Variants{
        // Vector2f
        Vector2f::Vector2f(){
            this->x = 0.0f;
            this->y = 0.0f;
        };
        Vector2f::Vector2f(Rellx::Types::Reel x,Rellx::Types::Reel y){
            this->x = x;
            this->y = y;
        };
        // Vector2i
        Vector2i::Vector2i(){
            this->x = 0;
            this->y = 0;
        };
        Vector2i::Vector2i(Rellx::Types::Int x,Rellx::Types::Int y){
            this->x = x;
            this->y = y;
        };
        // Vector2u
        Vector2u::Vector2u(){
            this->x = 0u;
            this->y = 0u;
        };
        Vector2u::Vector2u(Rellx::Types::Uint x,Rellx::Types::Uint y){
            this->x = x;
            this->y = y;
        };
    };
};
