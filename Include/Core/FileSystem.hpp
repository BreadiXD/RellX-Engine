#pragma once
#include "RellXLib.hpp"
namespace Rellx{
    namespace FileSystem{
        static Rellx::String BasePath = "";
        void Initialize();
        Rellx::String ReadText(const Rellx::String& path,Rellx::Types::Uint64* datasize);
    };
};