#include "Core/FileSystem.hpp"
#include "Core/Utility.hpp"
#include "SDL3/SDL.h"
namespace Rellx{
    namespace FileSystem{
        Rellx::String GetFullPath(const char* relativePath){
            return BasePath + relativePath;
        };
        void Initialize(){
            const char* path = SDL_GetBasePath();
            if (!path){
                RELLX_LOG_ERROR("Failed To Get Base Path !!!")
                return;
            };
            BasePath = Rellx::String(path);
            RELLX_LOG("Base Path %s ",BasePath.c_str())
        };

        Rellx::String ReadText(const Rellx::String& path,Rellx::Types::Uint64* datasize){
            Rellx::String fullPath = GetFullPath(path.c_str());
            Rellx::Types::Uint64 size = 0;
            void* data = SDL_LoadFile(fullPath.c_str(),&size);
            if (!data){
                RELLX_LOG_ERROR("Failed To Load : %s",fullPath.c_str())
                RELLX_LOG_ERROR(SDL_GetError())
                return Rellx::String("");
            };
            if (datasize) datasize = &size;
            Rellx::String content(static_cast<char*>(data),size);
            SDL_free(data);
            return content;
        };
    };
};