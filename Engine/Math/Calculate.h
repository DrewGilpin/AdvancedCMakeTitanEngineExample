/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************

   Use 'Calculate' functions to calculate string expressions and convert them to values.

   Sample Usage:

      Flt result=CalculateF("2*3");

/******************************************************************************/
enum CVAL_TYPE : Byte // Calculator Value Type
{
   CVAL_NONE, // none
   CVAL_INT , // integer
   CVAL_REAL, // real
   CVAL_VEC2, // vector 2D
   CVAL_VEC , // vector 3D
   CVAL_VEC4, // vector 4D
};
/******************************************************************************/
struct CalcValue // Calculator Value
{
   CVAL_TYPE type; // value type
   union
   {
      Long  i ; // CVAL_INT
      Dbl   r ; // CVAL_REAL
      VecD2 v2; // CVAL_VEC2
      VecD  v ; // CVAL_VEC
      VecD4 v4; // CVAL_VEC4
   };

   // get
   CChar8* typeName(                     )C; // get CVAL_TYPE type name in text format
   Str     asText  (Int precision=INT_MAX)C; // get value as text
   Int     asInt   (                     )C; // get value as Int  , 0 on fail
   UInt    asUInt  (                     )C; // get value as UInt , 0 on fail
   Long    asLong  (                     )C; // get value as Long , 0 on fail
   ULong   asULong (                     )C; // get value as ULong, 0 on fail
   Flt     asFlt   (                     )C; // get value as Flt  , 0 on fail
   Dbl     asDbl   (                     )C; // get value as Dbl  , 0 on fail
   Vec2    asVec2  (                     )C; // get value as Vec2 , (0,0) on fail
   VecD2   asVecD2 (                     )C; // get value as VecD2, (0,0) on fail
   VecI2   asVecI2 (                     )C; // get value as VecI2, (0,0) on fail
   Vec     asVec   (                     )C; // get value as Vec  , (0,0,0) on fail
   VecD    asVecD  (                     )C; // get value as VecD , (0,0,0) on fail
   VecI    asVecI  (                     )C; // get value as VecI , (0,0,0) on fail
   Vec4    asVec4  (                     )C; // get value as Vec4 , (0,0,0,0) on fail
   VecD4   asVecD4 (                     )C; // get value as VecD4, (0,0,0,0) on fail
   VecI4   asVecI4 (                     )C; // get value as VecI4, (0,0,0,0) on fail

   CalcValue() {} // needed because of union
};
/******************************************************************************/
struct CalcVar // Calculator Variable
{
   Str       name ;
   CalcValue value;

   CalcVar& set(C Str &name, CVAL_TYPE type=CVAL_REAL) {T.name=name; T.value.type=type; return T;}

            CalcVar(                                     ) {value.type=CVAL_REAL;}
   explicit CalcVar(C Str &name, CVAL_TYPE type=CVAL_REAL) {set(name, type);}
};
/******************************************************************************/
// Calculate 'expression', with 'var' array of 'vars' variables
Bool  Calculate  (CalcValue &value, C Str &expression, Str *error=null, C CMemPtr<CalcVar> &vars=null); // put    result value to 'value' and return if ok
Int   CalculateI (                  C Str &expression, Str *error=null, C CMemPtr<CalcVar> &vars=null); // return result value as Int
Long  CalculateL (                  C Str &expression, Str *error=null, C CMemPtr<CalcVar> &vars=null); // return result value as Long
Flt   CalculateF (                  C Str &expression, Str *error=null, C CMemPtr<CalcVar> &vars=null); // return result value as Flt
Dbl   CalculateD (                  C Str &expression, Str *error=null, C CMemPtr<CalcVar> &vars=null); // return result value as Dbl
VecD2 CalculateV2(                  C Str &expression, Str *error=null, C CMemPtr<CalcVar> &vars=null); // return result value as Vec2
VecD  CalculateV (                  C Str &expression, Str *error=null, C CMemPtr<CalcVar> &vars=null); // return result value as Vec
VecD4 CalculateV4(                  C Str &expression, Str *error=null, C CMemPtr<CalcVar> &vars=null); // return result value as Vec4
/******************************************************************************/
