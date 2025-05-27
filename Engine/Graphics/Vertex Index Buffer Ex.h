/******************************************************************************/
enum VTX_COMPRESS : Byte
{
   VTX_COMPRESS_NONE   =   0,
   VTX_COMPRESS_POS    =1<<0, // compress "Vec  pos, pos1        " to "VecH4   pos, pos1"
   VTX_COMPRESS_POS_SSN=1<<5, // compress "Vec  pos, pos1        " to "VecSSN4 pos, pos1"
   VTX_COMPRESS_NRM    =1<<1, // compress "Vec  normal           " to "VecB4   normal   "
   VTX_COMPRESS_TAN_BIN=1<<2, // compress "Vec  tangent, binormal" to "VecB4   tan_bin  "
   VTX_COMPRESS_UV     =1<<3, // compress "Vec2 uv               " to "VecH2   uv       "
   VTX_COMPRESS_UV_USN =1<<4, // compress "Vec2 uv               " to "VecUSN2 uv       "

   VTX_COMPRESS_NRM_TAN_BIN=VTX_COMPRESS_NRM|VTX_COMPRESS_TAN_BIN,
   VTX_COMPRESS_DEFAULT    =VTX_COMPRESS_NRM_TAN_BIN, // default compression, retains high precision for position and UV

   VTX_COMPRESS_AUTO_POS=VTX_COMPRESS_POS|VTX_COMPRESS_POS_SSN                              , // tries to maximize position compression as much as possible based on source data
   VTX_COMPRESS_AUTO_UV =VTX_COMPRESS_UV|VTX_COMPRESS_UV_USN                                , // tries to maximize UV       compression as much as possible based on source data
   VTX_COMPRESS_AUTO    =VTX_COMPRESS_AUTO_POS|VTX_COMPRESS_NRM_TAN_BIN|VTX_COMPRESS_AUTO_UV, // tries to maximize          compression as much as possible based on source data
};
SET_ENUM_FLAGS(VTX_COMPRESS);
#if EE_PRIVATE
Vec    UByte4ToNrm       (C VecB4  &v                                    ); // ( 0..255) -> (-1..1  )
void   UByte4ToTanBin    (C VecB4  &v,   Vec *tan,   Vec *bin, C Vec *nrm); // ( 0..255) -> (-1..1  )
VecB4     NrmToUByte4    (C Vec    &v                                    ); // (-1..1  ) -> ( 0..255)
VecB4     TanToUByte4    (C Vec    &v                                    ); // (-1..1  ) -> ( 0..255)
VecB4  TanBinToUByte4    (             C Vec *tan, C Vec *bin, C Vec *nrm); // (-1..1  ) -> ( 0..255)

Vec    SByte4ToNrm       (C VecSB4 &v                                    ); // (-127..127) -> (-  1..1  )     normalized
Vec    SByte4ToNrmFast   (C VecSB4 &v                                    ); // (-127..127) -> (-  1..1  ) NOT normalized
void   SByte4ToTanBin    (C VecSB4 &v,   Vec *tan,   Vec *bin, C Vec *nrm); // (-127..127) -> (-  1..1  )     normalized
void   SByte4ToTanBinFast(C VecSB4 &v,   Vec *tan,   Vec *bin, C Vec *nrm); // (-127..127) -> (-  1..1  ) NOT normalized
VecSB4    NrmToSByte4    (C Vec    &v                                    ); // (-  1..1  ) -> (-127..127)
VecSB4    TanToSByte4    (C Vec    &v                                    ); // (-  1..1  ) -> (-127..127)
VecSB4 TanBinToSByte4    (             C Vec *tan, C Vec *bin, C Vec *nrm); // (-  1..1  ) -> (-127..127)
VecSB4 TanBinToSByte4    (             C Vec *tan, C Vec *bin, C Vec *nrm, C Matrix3 &mtrx); // (-  1..1  ) -> (-127..127)
/******************************************************************************/
struct VtxFormatKey
{
   MESH_FLAG    flag    ;
   VTX_COMPRESS compress;

   VtxFormatKey() {}
   VtxFormatKey(MESH_FLAG flag, VTX_COMPRESS compress) {T.flag=flag; T.compress=compress;}
};
#if GL
enum GL_VTX_SEMANTIC : Byte // !! must be in sync with all "ATTR*" mentions in the engine !!
{
   GL_VTX_POS     , // 0
   GL_VTX_POS1    , // 1
   GL_VTX_NRM     , // 2
   GL_VTX_TAN     , // 3
   GL_VTX_UV      , // 4
   GL_VTX_UV1     , // 5
   GL_VTX_UV2     , // 6
   GL_VTX_UV3     , // 7
   GL_VTX_SIZE    , // 8
   GL_VTX_BONE    , // 9
   GL_VTX_WEIGHT  , // 10
   GL_VTX_MATERIAL, // 11
   GL_VTX_COLOR   , // 12
   GL_VTX_FACE_ID , // 13
   GL_VTX_NUM     , // 14
};
GL_VTX_SEMANTIC VtxSemanticToIndex(Int semantic);
struct VtxFormatGL
{
   struct Elm
   {
      GL_VTX_SEMANTIC semantic;
      Byte            component_num;
      Bool            component_normalize;
      GLenum          component_type;
      UInt            offset;

      void set(GL_VTX_SEMANTIC semantic, Byte component_num, GLenum component_type, Bool component_normalize, UInt offset) {T.semantic=semantic; T.component_num=component_num; T.component_type=component_type; T.component_normalize=component_normalize; T.offset=offset;}
   };
   Mems<Elm> elms;
   UInt      vtx_size, vao;

   void del   ();
   Bool create(C MemPtrN<Elm, 32> &elms);

   void disable   ()C;
   void  enableSet()C;
   void       bind(C VtxBuf &vb);

  ~VtxFormatGL() {del();}
   VtxFormatGL() {vtx_size=vao=0;}
};
#endif
#endif
struct VtxFormat // Vertex Format
{
   VtxFormat& del();

#if EE_PRIVATE
   #if DX11
      Bool createTry(D3D11_INPUT_ELEMENT_DESC ve[], Int elms);
      void create   (D3D11_INPUT_ELEMENT_DESC ve[], Int elms);
   #elif GL
      Bool createTry(C MemPtrN<VtxFormatGL::Elm, 32> &elms);
      void create   (C MemPtrN<VtxFormatGL::Elm, 32> &elms);
   #endif
   void create(MESH_FLAG flag, VTX_COMPRESS compress);
#if GL
          void bind(C VtxBuf &vb);
#else
   INLINE void bind(C VtxBuf &vb) {}
#endif
#endif

  ~VtxFormat() {del();}
   VtxFormat() {vf=null;}

#if !EE_PRIVATE
private:
#endif
#if EE_PRIVATE
   GPU_API(ID3D11InputLayout, VtxFormatGL) *vf;
#else
   Ptr vf;
#endif
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

#if EE_PRIVATE
   Byte*  lockDynamic(); // !! this is to be called only for VI buffers !!
   void unlockDynamic(); // !! this is to be called only for VI buffers !!

   Bool setFrom(CPtr data, Int size); // false on fail

   // manage
   Bool createRaw(Int memory_size                                    , Bool dynamic=false, CPtr data=null); //                    false on fail
   Bool createNum(Int vtx_size, Int vtx_num                          , Bool dynamic=false, CPtr data=null); //                    false on fail
   Bool create   (Int vtx_num , MESH_FLAG flag, VTX_COMPRESS compress, Bool dynamic=false                ); //                    false on fail
   Bool create   (C VtxBuf &src                                      , Int  dynamic=-1                   ); // create from 'src', false on fail

   void freeOpenGLESData(); // this method is used only under OpenGL ES (on other platforms it is ignored), the method frees the software copy of the GPU data which increases available memory, however after calling this method the data can no longer be accessed on the CPU (can no longer be locked or saved to file)

   // draw
   #if DX11
      void set(Int stream=0)C {UInt stride=_vtx_size, offset=0; D3DC->IASetVertexBuffers(stream, 1, &_buf, &stride, &offset);}
   #elif GL
      void set(Int stream=0)C {glBindBuffer(GL_ARRAY_BUFFER, _buf);}
   #endif

   // io
   Bool save(File &f)C;
   Bool load(File &f) ;
#endif

  ~VtxBuf() {del ( );}
   VtxBuf() {Zero(T);}

#if !EE_PRIVATE
private:
#endif
   Bool      _dynamic;
   LOCK_MODE _lock_mode;
   Int       _vtx_size, _vtx_num, _lock_count;
   Byte     *_data;
#if EE_PRIVATE
   GPU_API(ID3D11Buffer *_buf, union{UInt _buf; Ptr _buf_ptr;});
#else
   Ptr       _buf;
#endif
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

#if EE_PRIVATE
   Bool setFrom(CPtr data); // false on fail

   Bool create(Int indexes, Bool bit16, Bool dynamic=false, CPtr data=null); //                    false on fail
   Bool create(C IndBuf &src          , Int  dynamic=-1                   ); // create from 'src', false on fail

   IndBuf& setTri (Int i, Int v0, Int v1, Int v2);
   IndBuf& setQuad(Int i, Int v0, Int v1, Int v2, Int v3);

   void freeOpenGLESData(); // this method is used only under OpenGL ES (on other platforms it is ignored), the method frees the software copy of the GPU data which increases available memory, however after calling this method the data can no longer be accessed on the CPU (can no longer be locked or saved to file)

   // draw
   #if DX11
      void set()C {D3DC->IASetIndexBuffer(_buf, _bit16 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT, 0);}
   #elif GL
      void set()C {glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buf);}
   #endif

   // io
   Bool save(File &f)C;
   Bool load(File &f) ;
#endif

  ~IndBuf() {del ( );}
   IndBuf() {Zero(T);}

#if !EE_PRIVATE
private:
#endif
   Bool      _dynamic, _bit16;
   LOCK_MODE _lock_mode;
   Int       _ind_num, _lock_count;
   Byte     *_data;
#if EE_PRIVATE
   GPU_API(ID3D11Buffer *_buf, union{UInt _buf; Ptr _buf_ptr;});
#else
   Ptr       _buf;
#endif
   NO_COPY_CONSTRUCTOR(IndBuf);
};
/******************************************************************************/
#if EE_PRIVATE
void InitVtxInd();
void ShutVtxInd();

Int VtxSize(MESH_FLAG flag, VTX_COMPRESS compress);

#if GL
   INLINE void SetDefaultVAO() {glBindVertexArray(VAO);}
#else
   INLINE void SetDefaultVAO() {}
#endif

void BindIndexBuffer(UInt buf);

extern ThreadSafeMap<VtxFormatKey, VtxFormat> VtxFormats;
extern IndBuf                                 IndBuf16384Quads, IndBufBorder, IndBufPanel, IndBufPanelEx, IndBufRectBorder, IndBufRectShaded;
#endif
/******************************************************************************/
