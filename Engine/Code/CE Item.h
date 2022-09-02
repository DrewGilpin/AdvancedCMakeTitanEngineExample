/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************/
namespace Edit{
/******************************************************************************/
struct Item
{
   enum TYPE : Byte
   {
      UNKNOWN,
      LIB    ,
      APP    ,
      FOLDER ,
      FILE   ,
   };
   TYPE       type;
   Str        base_name, full_name;
   Memx<Item> children;

   Item() {type=UNKNOWN;}
};
/******************************************************************************/
} // namespace
/******************************************************************************/
