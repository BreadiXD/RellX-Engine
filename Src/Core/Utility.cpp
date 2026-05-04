#include "Core/Utility.hpp"
#include "SDL3/SDL.h"
namespace Rellx{
    namespace Memory{
        void* Alloc(Rellx::Types::Uint64 size){
            return SDL_malloc(size);
        };
        void Delete(void* ptr){
            SDL_free(ptr);
        };
    };

    namespace Loging{
        void Log(const char* fmt,...){
            SDL_Log(fmt);
        };
        void Error(const char* fmt,...){
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,fmt);
        };
        
    };
};
