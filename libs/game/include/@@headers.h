/******************************************************************************/
#pragma once

#define bool Bool // boolean value (8-bit)

#define char8 Char8 //  8-bit character
#define char  Char  // 16-bit character

#define sbyte  I8  //  8-bit   signed integer
#define  byte  U8  //  8-bit unsigned integer
#define  short I16 // 16-bit   signed integer
#define ushort U16 // 16-bit unsigned integer
#define  int   I32 // 32-bit   signed integer
#define uint   U32 // 32-bit unsigned integer
#define  long  I64 // 64-bit   signed integer
#define ulong  U64 // 64-bit unsigned integer

#define flt Flt // 32-bit floating point
#define dbl Dbl // 64-bit floating point

#define  ptr  Ptr // universal pointer
#define cptr CPtr // universal pointer to const data

#define cchar8 CChar8 // const Char8
#define cchar  CChar  // const Char16

#define  intptr  IntPtr //   signed integer capable of storing full memory address
#define uintptr UIntPtr // unsigned integer capable of storing full memory address

#define class struct // Code Editor "class" is a C++ "struct"
/******************************************************************************/
// DEFINES
#define STEAM   0
#define OPEN_VR 0
/******************************************************************************/
// ENUMS
/******************************************************************************/
enum OBJ_TYPE // Object Class Types
{
   OBJ_CHR         ,
   OBJ_DESTRUCTIBLE,
   OBJ_ITEM        ,
   OBJ_LIGHT_POINT ,
   OBJ_PARTICLES   ,
};
/******************************************************************************/
// CONSTANTS
/******************************************************************************/
const int  APP_BUILD        =1;
/******************************************************************************/
// CPP
/******************************************************************************/
#include "Auto.h"
#include "Main.h"
/******************************************************************************/
// INLINE, TEMPLATES
/******************************************************************************/
