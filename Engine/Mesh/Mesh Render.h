/******************************************************************************

   'MeshRender' is the hardware version of the 'MeshBase'.
   It contains vertexes and triangles.
   It is stored on the GPU memory.

/******************************************************************************/
#if EE_PRIVATE
struct BoneSplit
{
   Byte split_to_real[256];
   Int  vtxs, tris, bones;

   Int realToSplit (Int bone)C; // -1 on fail
   Int realToSplit0(Int bone)C; //  0 on fail
};
#endif
/******************************************************************************/
struct MeshRender // Mesh Renderable (Hardware: contains Vertexes + Triangles)
{
   // manage
   MeshRender& del();

   Bool create(C MeshBase   &src, MESH_FLAG flag_and=MESH_ALL, VTX_COMPRESS compress=VTX_COMPRESS_DEFAULT);
   Bool create(C MeshRender &src);
#if EE_PRIVATE
   void zero     ();
   Bool create   (Int vtxs, Int tris ,           MESH_FLAG flag             , VTX_COMPRESS compress=VTX_COMPRESS_DEFAULT);
   Bool createRaw(C MeshBase   &src  ,           MESH_FLAG flag_and=MESH_ALL, VTX_COMPRESS compress=VTX_COMPRESS_DEFAULT);
   Bool create   (C MeshRender *src[], Int elms, MESH_FLAG flag_and=MESH_ALL, VTX_COMPRESS compress=VTX_COMPRESS_AUTO   ); // create from 'src' array, 'flag_and'=data to copy

   struct Instance
   {
      Material *mtrl;
    C MeshPart *mesh;
    C Matrix   *mtrx;
   };
   Bool create(C Instance *src, Int elms, Box &box, Ball &ball, MESH_FLAG flag_and=MESH_ALL, VTX_COMPRESS compress=VTX_COMPRESS_AUTO); // create from 'src' array, 'flag_and'=data to copy
#endif

   // get
   Bool is  ()C {return vtxs() || tris();} // if  has any data
   Int  vtxs()C {return _vb.vtxs()      ;} // get number of vertexes
   Int  tris()C {return    _tris        ;} // get number of triangles

   UInt         memUsage(             )C {return _vb.memUsage()+_ib.memUsage();} // get mesh memory usage (in bytes)
   UInt      vtxMemUsage(             )C {return _vb.memUsage()               ;} // get size of   all    vertexes
   Int       vtxSize    (             )C {return _vb.vtxSize ()               ;} // get size of a single vertex
   Int       vtxOfs     (MESH_FLAG elm)C;                                        // get offset of a specified vertex component in the vertex data, -1 if not found
   UInt      indMemUsage(             )C {return _ib.memUsage()               ;} // get size of   all    indices
   Bool      indBit16   (             )C {return _ib.bit16()                  ;} // if  indices are 16-bit (false for 32-bit)
   MESH_FLAG        flag(             )C {return _flag                        ;} // get available data
   VTX_COMPRESS compress(             )C {return _compress                    ;} // get compression

   Bool getBox(Box &box                   )C; // get box encapsulating the mesh, this method iterates through all vertexes, false on fail (if no vertexes are present)
   Bool getBox(Box &box, C Matrix3 &matrix)C; // get box encapsulating the mesh, this method iterates through all vertexes, 'matrix'=matrix affecting vertex positions, false on fail (if no vertexes are present)
   Bool getBox(Box &box, C Matrix  &matrix)C; // get box encapsulating the mesh, this method iterates through all vertexes, 'matrix'=matrix affecting vertex positions, false on fail (if no vertexes are present)
   Flt    area(Vec *center=null           )C; // get surface area of all mesh faces, 'center'=if specified then it will be calculated as the average surface center

   // transform
   void scaleMove(C Vec &scale, C Vec &move=VecZero);

   // UV transform
   void uvMove  (C Vec2 &move , Byte uv_index=0);
   void uvScale (C Vec2 &scale, Byte uv_index=0);
   void uvRotate(  Flt   angle, Byte uv_index=0);

   // operations
 C Byte* vtxLockedData(                              )C {return _vb.lockedData(    );} //    get vertex data if it's already locked, null on fail
 C Byte* vtxLockedElm (MESH_FLAG elm                 )C;                               //    get vertex data if it's already locked offsetted by specified vertex component in the vertex data according to 'vtxOfs' method, null on fail (if the vertex buffer is not locked or if the component was not found)
   Byte* vtxLock      (LOCK_MODE lock=LOCK_READ_WRITE)  {return _vb.lock      (lock);} //   lock vertex data and return it, this method may be used to directly modify values of hardware mesh vertexes after getting their offset in the data by using 'vtxOfs' method, null on fail
 C Byte* vtxLockRead  (                              )C {return _vb.lockRead  (    );} //   lock vertex data and return it, this method may be used to directly access values of hardware mesh vertexes after getting their offset in the data by using 'vtxOfs' method, null on fail
   void  vtxUnlock    (                              )C {       _vb.unlock    (    );} // unlock vertex data

   CPtr indLockedData(                              )C {return _ib.  lockedData(    );} //    get index data if it's already locked, null on fail
    Ptr indLock      (LOCK_MODE lock=LOCK_READ_WRITE)  {return _ib.  lock      (lock);} //   lock index data and return it, this method may be used to directly access values of hardware mesh indexes, null on fail
   CPtr indLockRead  (                              )C {return _ib.  lockRead  (    );} //   lock index data and return it, this method may be used to directly modify values of hardware mesh indexes, null on fail
   void indUnlock    (                              )C {       _ib.unlock      (    );} // unlock index data

#if EE_PRIVATE
   Int triIndSize()C {return indBit16() ? SIZE(U16)*3 : SIZE(U32)*3;} // get triangle indexes size

   void        boneRemap(C CMemPtrN<BoneType, 256> &old_to_new); // remap vertex bone/matrix indexes according to bone 'old_to_new' remap
   void     setUsedBones(   MemPtrN<Bool    , 256>  bones)C;
   void includeUsedBones(   MemPtrN<Bool    , 256>  bones)C;

   // draw
#if DX11
   void draw         (                         )C {D3DC->DrawIndexed         (_ib._ind_num,           0, 0);}
   void drawRange    (Int tris                 )C {D3DC->DrawIndexed         (tris*3      ,           0, 0);}
   void drawRange    (Int tris, Int start_index)C {D3DC->DrawIndexed         (tris*3      , start_index, 0);}
   void drawInstanced(Int instances            )C {D3DC->DrawIndexedInstanced(_ib._ind_num,   instances, 0, 0, 0);}
#elif GL
   void draw         (                         )C {glDrawElements         (GL_TRIANGLES, _ib._ind_num, indBit16() ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT,                                  null);}
   void drawRange    (Int tris                 )C {glDrawElements         (GL_TRIANGLES,       tris*3, indBit16() ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT,                                  null);}
   void drawRange    (Int tris, Int start_index)C {glDrawElements         (GL_TRIANGLES,       tris*3, indBit16() ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, Ptr(start_index*(indBit16() ? 2 : 4)));}
   void drawInstanced(Int instances            )C {glDrawElementsInstanced(GL_TRIANGLES, _ib._ind_num, indBit16() ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT,                                  null, instances);}
#endif

   void drawBoneHighlight(Int bone, Shader *shader)C;

   // operations
   Bool        setVF();
 C MeshRender& set()C;

   MeshRender& optimize        (Bool faces=true, Bool vertexes=true); // this method will re-order elements for best rendering performance, 'faces'=if re-order faces, 'vertexes'=if re-order vertexes
   MeshRender& freeOpenGLESData(); // this method is used only under OpenGL ES (on other platforms it is ignored), the method frees the software copy of the GPU data which increases available memory, however after calling this method the data can no longer be accessed on the CPU (can no longer be locked or saved to file)
   void        adjustToPlatform(Bool compressed, Bool sign, Bool bone_split, C CMemPtr<BoneSplit> &bone_splits);

   // io
#if EE_PRIVATE
   Bool saveData(File &f)C; // save binary, false on fail
   Bool loadData(File &f) ; // load binary, false on fail
#endif
   void operator=(C Str  &name) ; // load binary, Exit  on fail
   Bool save     (C Str  &name)C; // save binary, false on fail
   Bool load     (C Str  &name) ; // load binary, false on fail
   Bool save     (  File &f   )C; // save binary, false on fail
   Bool load     (  File &f   ) ; // load binary, false on fail

   explicit MeshRender(C MeshBase &mshb, MESH_FLAG flag_and=MESH_ALL) : MeshRender() {create(mshb, flag_and);}
#endif

              ~MeshRender() {del();}
               MeshRender();
               MeshRender(C MeshRender &src);
   MeshRender& operator =(C MeshRender &src); // create from 'src'
   MeshRender& operator+=(C MeshRender &src); // add         'src'

#if !EE_PRIVATE
private:
#endif
   VtxBuf       _vb;
   IndBuf       _ib;
   Bool         _vao_reset;
   VTX_COMPRESS _compress;
   Int          _tris;
   MESH_FLAG    _flag;
#if EE_PRIVATE
   GPU_API(ID3D11InputLayout *_vf, union{UInt _vao; VtxFormatGL *_vf;});
#else
   Ptr          _vf;
#endif
};
/******************************************************************************/
