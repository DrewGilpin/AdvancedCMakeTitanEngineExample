﻿/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************/
enum IMAGERT_TYPE : Byte // Image Render Target Type, this describes a group of Image Types
{ // P=10bit, H=16bit, F=32bit, S=Signed
   IMAGERT_SRGBA  , // IMAGE_R8G8B8A8_SRGB                                                                   (         32-bit total       with Alpha)
   IMAGERT_SRGB   , // IMAGE_R8G8B8A8_SRGB                                                                   (         32-bit total       no   Alpha)
   IMAGERT_SRGB_P , // IMAGE_F16_3, IMAGE_F16_4, IMAGE_R8G8B8A8_SRGB                                         (at least 10-bit per channel no   Alpha)
   IMAGERT_SRGBA_H, // IMAGE_F16_4, IMAGE_R8G8B8A8_SRGB                                                      (at least 16-bit per channel with Alpha)
   IMAGERT_SRGB_H , // IMAGE_F16_3, IMAGE_F16_4, IMAGE_R8G8B8A8_SRGB                                         (at least 16-bit per channel no   Alpha)
   IMAGERT_SRGBA_F, // IMAGE_F32_4, IMAGE_F16_4, IMAGE_R8G8B8A8_SRGB                                         (at least 32-bit per channel with Alpha)
   IMAGERT_SRGB_F , // IMAGE_F32_3, IMAGE_F32_4, IMAGE_F16_3, IMAGE_F16_4, IMAGE_R8G8B8A8_SRGB               (at least 32-bit per channel no   Alpha)

   IMAGERT_RGBA   , // IMAGE_R8G8B8A8                                                                        (         32-bit total       with Alpha)
   IMAGERT_RGB    , // IMAGE_R10G10B10A2, IMAGE_R8G8B8A8                                                     (         32-bit total       no   Alpha)
   IMAGERT_RGB_P  , // IMAGE_R10G10B10A2, IMAGE_F16_3, IMAGE_F16_4, IMAGE_R8G8B8A8                           (at least 10-bit per channel no   Alpha)
   IMAGERT_RGBA_H , // IMAGE_F16_4, IMAGE_R8G8B8A8                                                           (at least 16-bit per channel with Alpha)
   IMAGERT_RGB_H  , // IMAGE_F16_3, IMAGE_F16_4, IMAGE_R10G10B10A2, IMAGE_R8G8B8A8                           (at least 16-bit per channel no   Alpha)
   IMAGERT_RGBA_F , // IMAGE_F32_4, IMAGE_F16_4, IMAGE_R8G8B8A8                                              (at least 32-bit per channel with Alpha)
   IMAGERT_RGB_F  , // IMAGE_F32_3, IMAGE_F32_4, IMAGE_F16_3, IMAGE_F16_4, IMAGE_R10G10B10A2, IMAGE_R8G8B8A8 (at least 32-bit per channel no   Alpha)

   IMAGERT_RGBA_S , // IMAGE_R8G8B8A8_SIGN, IMAGE_F16_4                                                      (signed   32-bit total       with Alpha)
   IMAGERT_F32    , // IMAGE_F32, IMAGE_F16
   IMAGERT_F16    , // IMAGE_F16, IMAGE_F32
   IMAGERT_ONE    , // IMAGE_R8     , IMAGE_F16, IMAGE_R8G8     , IMAGE_F32  , IMAGE_R8G8B8A8
   IMAGERT_ONE_S  , // IMAGE_R8_SIGN, IMAGE_F16, IMAGE_R8G8_SIGN, IMAGE_F32  , IMAGE_R8G8B8A8_SIGN
   IMAGERT_TWO    , //                           IMAGE_R8G8     , IMAGE_F16_2, IMAGE_R8G8B8A8     
   IMAGERT_TWO_S  , //                           IMAGE_R8G8_SIGN, IMAGE_F16_2, IMAGE_R8G8B8A8_SIGN
   IMAGERT_TWO_H  , // IMAGE_F16_2, IMAGE_F32_2
   IMAGERT_DS     , // IMAGE_D24S8, IMAGE_D24X8, IMAGE_D32, IMAGE_D32S8X24, IMAGE_D16
   IMAGERT_DS_S   , // IMAGE_D24S8, IMAGE_D32S8X24
   IMAGERT_NUM    , // number of Image render targets

   IMAGERT_RGBA_P =IMAGERT_RGBA_H , // (at least        10-bit per channel with Alpha)

   IMAGERT_SRGBA_P=IMAGERT_SRGBA_H, // (at least        10-bit per channel with Alpha)

   IMAGERT_RGBA_SP=IMAGERT_RGBA_H , // (at least signed 10-bit per channel with Alpha)
   IMAGERT_RGB_S  =IMAGERT_RGBA_S , // (         signed 32-bit total       no   Alpha)

   IMAGERT_RGB_A2_H=IMAGERT_RGBA_H,
   IMAGERT_RGB_A2_S=IMAGERT_RGBA_S,
   IMAGERT_RGB_A2  =IMAGERT_RGB   ,
};
/******************************************************************************/
struct ImageRT : Image // Image Render Target
{
   Bool         create(C VecI2 &size, IMAGE_TYPE type, IMAGE_MODE mode=IMAGE_RT, Byte samples=1); // create, false on fail
   ImageRT& mustCreate(C VecI2 &size, IMAGE_TYPE type, IMAGE_MODE mode=IMAGE_RT, Byte samples=1); // create, Exit  on fail

   ImageRT();
  ~ImageRT();
private:
   union
   {
      struct
      {
         Ptr _ptr[6];
      };
      struct
      {
         UInt _uint;
      };
   };
   NO_COPY_CONSTRUCTOR(ImageRT);
};
/******************************************************************************/
struct ImageRTC : ImageRT // Image Render Target Counted
{
private:
   UInt _ptr_num=0; // this shouldn't be modified in any 'del', 'create' method
};
/******************************************************************************/
struct ImageRTPtr // Render Target Pointer
{
   Bool       find(Int w, Int h, IMAGERT_TYPE rt_type, Byte samples=1); // find Render Target, false on fail, 'samples'=number of samples per-pixel (allows multi-sampling)
   ImageRTPtr& get(Int w, Int h, IMAGERT_TYPE rt_type, Byte samples=1); // find Render Target, Exit  on fail, 'samples'=number of samples per-pixel (allows multi-sampling)

   ImageRTC* operator ()       (               )C {return  T._data         ;} // access the data, you can use the returned reference as long as this 'ImageRTPtr' object exists and not modified
   ImageRTC* operator ->       (               )C {return  T._data         ;} // access the data, you can use the returned reference as long as this 'ImageRTPtr' object exists and not modified
   ImageRTC& operator *        (               )C {return *T._data         ;} // access the data, you can use the returned reference as long as this 'ImageRTPtr' object exists and not modified
   Bool      operator ==       (  null_t       )C {return  T._data==null   ;} // if pointers are equal
   Bool      operator !=       (  null_t       )C {return  T._data!=null   ;} // if pointers are different
   Bool      operator ==       (  ImageRTC   *p)C {return  T._data==p      ;} // if pointers are equal
   Bool      operator !=       (  ImageRTC   *p)C {return  T._data!=p      ;} // if pointers are different
   Bool      operator ==       (C ImageRTC   *p)C {return  T._data==p      ;} // if pointers are equal
   Bool      operator !=       (C ImageRTC   *p)C {return  T._data!=p      ;} // if pointers are different
   Bool      operator ==       (C ImageRTPtr &p)C {return  T._data==p._data;} // if pointers are equal
   Bool      operator !=       (C ImageRTPtr &p)C {return  T._data!=p._data;} // if pointers are different
             operator Bool     (               )C {return  T._data!=null   ;} // if pointer  is  valid
             operator ImageRTC*(               )C {return  T._data         ;}

   ImageRTPtr& clear    (               );                  // clear the pointer to null, this automatically decreases the reference count of current data
   ImageRTPtr& operator=(  null_t       ) {return clear();} // clear the pointer to null, this automatically decreases the reference count of current data
   ImageRTPtr& operator=(C ImageRTPtr &p);                  // set       pointer to 'p' , this automatically decreases the reference count of current data and increases the reference count of the new data
   ImageRTPtr& operator=(  ImageRTC   *p);                  // set       pointer to 'p' , this automatically decreases the reference count of current data and increases the reference count of the new data

   ImageRTPtr(  null_t=null  ) {_data=null; _last_index=-1;}
   ImageRTPtr(C ImageRTPtr &p);
   ImageRTPtr(  ImageRTC   *p);
  ~ImageRTPtr(               ) {clear();}

private:
   ImageRTC *_data;
   Int       _last_index;
};
/******************************************************************************/
