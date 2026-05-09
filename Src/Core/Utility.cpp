#include "Core/Utility.hpp"
#include "SDL3/SDL.h"
#include "rpmalloc.h"
#include <cstdarg>
namespace Rellx{
    namespace Memory{
        void Initialize(){
            rpmalloc_initialize();
        };
        void CleanUp(){
            rpmalloc_finalize();
        };
        void* Alloc(Rellx::Types::Uint64 size){
            return rpmalloc(size);
        };
        void Delete(void* ptr){
            rpfree(ptr);
        };
    };

    namespace Logging{
        void Log(const char* fmt,...){
            va_list args;
            va_start(args,fmt);
            SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,fmt,args);
            va_end(args);
        };
        void Error(const char* fmt,...){
            va_list args;
            va_start(args,fmt);
            SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,fmt,args);
            va_end(args);
        };
        
    };
};
