#pragma once
#include <new>
#include <utility>
#include <string>
#include <vector>
// All Utility Function And Types To Use In General 
#ifdef RELLX_DEBUG_LOGGING
#define RELLX_LOG(...) Rellx::Logging::Log(__VA_ARGS__);
#define RELLX_LOG_ERROR(...) Rellx::Logging::Error(__VA_ARGS__);
#else
#define RELLX_LOG(...)
#define RELLX_LOG_ERROR(...)
#endif


namespace Rellx{
    namespace Types{
        #ifdef RELLX_HIGH_INT_PRECISION
        using Int = long long;
        #else
        using Int = int;

        #endif
        #ifdef RELLX_HIGH_UINT_PRECISION
        using Uint = unsigned long long;
        #else
        using Uint = unsigned int;
        #endif
        #ifdef RELLX_HIGH_REEL_PRECISION
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
        template <typename T,typename... Args>
        T* New(Args&&... args){
            void* ptr = Rellx::Memory::Alloc(sizeof(T));
            if (!ptr) return nullptr;
            
            return ::new (ptr) T(std::forward<Args>(args)...);
        };
        void Free(void* ptr);

        template <typename T>
        void Delete(T* ptr){
            if (!ptr) return;
            ptr->~T();
            Free(ptr);
        };
        template <typename T>
        struct RellxAllocator{
            using value_type = T;
            RellxAllocator() = default;
            template <typename U>
            RellxAllocator(const RellxAllocator<U>&) noexcept {};
            T* allocate(size_t n){
                void* ptr = Rellx::Memory::Alloc(sizeof(T) * n);
                if (!ptr) throw std::bad_alloc();
                return static_cast<T*>(ptr);
            };
            void deallocate(T* ptr,size_t) noexcept{
                Rellx::Memory::Free(ptr);
            };
            template <typename U>
            bool operator==(const RellxAllocator<U>&) const noexcept {return true;};
            template <typename U>
            bool operator!=(const RellxAllocator<U>&) const noexcept {return false;};
        };
    };
    using String = std::basic_string<char,std::char_traits<char>,Rellx::Memory::RellxAllocator<char>>;
    template <typename T>
    using Array = std::vector<T,Rellx::Memory::RellxAllocator<T>>;



    // Errors Handling
    enum class Error{OK,FAILED};
    
    enum class GraphicsAPIS{NONE,OPENGL33}; // Graphics API
    enum class VsyncsModes{OFF,ON,ADAPTIVE};
    // Loging
    namespace Logging{
        void Log(const char* fmt,...);
        void Error(const char* fmt,...);
    };
};