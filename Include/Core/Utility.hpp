#pragma once

// All Utility Function And Types To Use In General 

namespace Rellx{
    namespace Loging{
        void Log(const char* fmt,...);
        void Error(const char* fmt,...);
    };
};



#ifdef RELLX_DEBUG_LOGGING
#define RELLX_LOG(...) Rellx::Logging::Log(__VA_ARGS__);
#define RELLX_LOG_ERROR(...) Rellx::Logging::Error(__VA_ARGS__);
#else
#define RELLX_LOG(...)
#define RELLX_LOG_ERROR(...)
#endif


namespace Rellx{
    namespace Types{
        #ifdef RELLX_HIGH_INT_PERCENTION
        using Int = long long;
        #else
        using Int = int;

        #endif
        #ifdef RELLX_HIGH_UINT_PERCENTION
        using Uint = unsigned long long;
        #else
        using Uint = unsigned int;
        #endif
        #ifdef RELLX_HIGH_REEL_PERCENTION
        using Reel = double;
        #else
        using Reel = float;
        #endif
        using Uint8 = unsigned char;
        using Uint16 = unsigned short;
        using Uint32 = unsigned int;
        using Uint64 = unsigned long long;
        using Int8 = signed char;
        using Int16 = short;
        using Int32 = int;
        using Int64 = long long;
    };
    
    // Memory Operation
    namespace Memory{
        void Initialize();
        void CleanUp();
        void* Alloc(Rellx::Types::Uint64 size);
        template <typename T>
        T* New(){
            return static_cast<T*>(Rellx::Memory::Alloc(sizeof(T)));
        };
        void Delete(void* ptr);
    };
    // Errors Handling
    enum class Error{OK,PROGRAM_CLOSED};
    // Loging
    namespace Logging{
        void Log(const char* fmt,...);
        void Error(const char* fmt,...);

        
    };
};