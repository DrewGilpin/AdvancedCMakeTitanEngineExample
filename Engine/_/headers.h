/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************/
#define SUPPORT_WINDOWS_XP (!X64 && GL) // 0=minor performance improvements in some parts of the engine, but no WindowsXP support, 1=some extra checks in the codes but with WindowsXP support
#define SUPPORT_WINDOWS_7  (        GL) // 0=uses XAudio 2.9 (which requires Windows 10), 1=uses DirectSound

#define JP_X_INPUT       (WINDOWS_OLD && (SUPPORT_WINDOWS_XP || SUPPORT_WINDOWS_7))
#define JP_GAMEPAD_INPUT (WINDOWS     && !JP_X_INPUT) // always use on WINDOWS_NEW to allow 'App.joypad_user_changed'
#define JP_DIRECT_INPUT  (WINDOWS_OLD && 0) // disable DirectInput-only Joypads because it introduces 0.25s delay to engine startup. Modern Joypads use XInput, so this is only for old Joypads.
#define JP_RAW_INPUT     (WINDOWS_OLD && 0)

#if WINDOWS
   #ifndef __PLACEMENT_NEW_INLINE
      #define __PLACEMENT_NEW_INLINE
      inline void* __cdecl operator new   (size_t, void *where) {return where;}
      inline void  __cdecl operator delete(void *, void *     )throw() {}
   #endif
   #undef GetComputerName
   #undef TRANSPARENT
   #undef ERROR
   #undef INPUT_MOUSE
   #undef INPUT_KEYBOARD
   #undef min
   #undef max
   #define _ALLOW_RTCc_IN_STL
   #include <vcruntime_string.h> // needed for 'memcpy' (inside "string.h")
#else
   #include <new>
   #include <stdint.h>
   #include <stddef.h>
   #include <string.h> // needed for 'memcpy'
#endif
#include <math.h>
#include <typeinfo>
#include <type_traits> // needed for 'std::enable_if', 'std::is_enum'
#if ANDROID
   #include <android/api-level.h> // needed for __ANDROID_API__
#endif
#if !WINDOWS_NEW
namespace std{typedef decltype(nullptr) nullptr_t;}
#endif
/******************************************************************************/
