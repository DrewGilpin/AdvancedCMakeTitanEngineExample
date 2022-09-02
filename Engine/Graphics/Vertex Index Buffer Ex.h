/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************/
struct VtxFormat // Vertex Format
{
   VtxFormat& del();

  ~VtxFormat() {del();}
   VtxFormat() {vf=null;}

private:
   Ptr vf;
   NO_COPY_CONSTRUCTOR(VtxFormat);
};
/******************************************************************************/
struct VtxBuf // Vertex Buffer
{
   // manage
   VtxBuf& del();

   // get
   Bool is      ()C {return _buf!=NULL        ;} // if  created
   Int  vtxs    ()C {return _vtx_num          ;} // get number of vertexes
   Int  vtxSize ()C {return          _vtx_size;} // get size of a single vertex
   UInt memUsage()C {return _vtx_num*_vtx_size;} // get memory usage of the vertex buffer (in bytes)

   // operations
 C Byte*  lockedData()C {return _data;}
   Byte*  lock      (LOCK_MODE lock=LOCK_READ_WRITE);
 C Byte*  lockRead  ()C;
   void unlock      () ;
   void unlock      ()C;

  ~VtxBuf() {del ( );}
   VtxBuf() {Zero(T);}

private:
   Bool      _dynamic;
   LOCK_MODE _lock_mode;
   Int       _vtx_size, _vtx_num, _lock_count;
   Byte     *_data;
   Ptr       _buf;
   NO_COPY_CONSTRUCTOR(VtxBuf);
};
/******************************************************************************/
struct IndBuf // Index Buffer
{
   // manage
   IndBuf& del();

   // get
   Bool is      ()C {return _ind_num>0;}
   Bool bit16   ()C {return           _bit16         ;} // if indices are 16-bit (false for 32-bit)
   UInt memUsage()C {return _ind_num*(_bit16 ? 2 : 4);} // get memory usage of the index buffer (in bytes)

   // operations
   CPtr   lockedData()C {return _data;}
    Ptr   lock      (LOCK_MODE lock=LOCK_READ_WRITE);
   CPtr   lockRead  ()C;
   void unlock      () ;
   void unlock      ()C;

  ~IndBuf() {del ( );}
   IndBuf() {Zero(T);}

private:
   Bool      _dynamic, _bit16;
   LOCK_MODE _lock_mode;
   Int       _ind_num, _lock_count;
   Byte     *_data;
   Ptr       _buf;
   NO_COPY_CONSTRUCTOR(IndBuf);
};
/******************************************************************************/
