/******************************************************************************

   Use 'VI' vertex index buffer for drawing simple 2D or 3D buffered graphics.

/******************************************************************************/
#if EE_PRIVATE
enum VI_TYPE : Byte // VertexIndex vertex type
{
   VI_NONE           , // none
   VI_2D_FLAT        , // pos
   VI_2D_COL         , // pos+color
   VI_2D_UV          , // pos+uv
   VI_2D_UV_COL      , // pos+uv+color
   VI_2D_UV2         , // pos+uv*2
   VI_2D_FONT        , // pos+uv+shade
   VI_2D_DEPTH_UV    , // pos+depth+uv
   VI_2D_DEPTH_UV_COL, // pos+depth+uv+color
   VI_3D_FLAT        , // pos
   VI_3D_COL         , // pos+color
   VI_3D_UV          , // pos+uv
   VI_3D_UV_COL      , // pos+uv+color
   VI_3D_BILB        , // pos+color+uv+size
   VI_3D_BILB_ANIM   , // pos+color+uv+size+frame
   VI_3D_LASER       , // pos+nrm
   VI_3D_SIMPLE      , // pos+nrm+uv+color
   VI_3D_STANDARD    , // pos+nrm+tan+bin+uv+color
   VI_3D_FULL        , // pos+pos1+nrm+tan+bin+uv+blend+matrix
};
enum VI_FLAG // VertexIndex flags
{
   VI_LINE    =0x1, // if drawing lines
   VI_STRIP   =0x2, // if drawing strip
   VI_QUAD_IND=0x4, // if drawing quad using index buffer
   VI_SP_COL  =0x8, // use 'ShaderParam' color modifiers
};
enum VI_USER_FLAG // VertexIndex user flags
{
   VI_CULL              =1<<0, // perform triangle culling
   VI_ALPHA_TEST        =1<<1, // perform alpha    testing
   VI_FOG               =1<<2, // make use of Fog
   VI_CUSTOM_SAMPLER    =1<<3, // custom texture sampler was specified
   VI_CUSTOM_DEPTH_WRITE=1<<4, // custom depth   write   was specified
};
/******************************************************************************/
struct Vtx2DFlat
{
   Vec2 pos;
};
struct Vtx2DCol
{
   Vec2  pos;
   Color color;
};
struct Vtx2DUV2
{
   Vec2 pos, uv[2];
};
struct Vtx2DFont
{
   Vec2 pos, uv;
   Flt  shade;
};
struct Vtx3DFlat
{
   Vec pos;
};
struct Vtx3DCol
{
   Vec   pos;
   Color color;
};
#define VTX3D_BILB_HALF 1
struct Vtx3DBilb
{
   Vec   pos;
#if VTX3D_BILB_HALF
   VecH4 vel_angle;
#else
   Vec4  vel_angle;
#endif
   VecB4 uv;
   Flt   size;
   Color color;
};
struct Vtx3DBilbAnim : Vtx3DBilb
{
   Flt frame;
};
struct Vtx3DLaser
{
   Vec pos, nrm;
};
struct Vtx3DFull
{
   Vec   pos, pos1, nrm;
   Vec4  tan; // tan.xyz=tangent, tan.w=binormal direction (should be -1 or +1)
   Vec2  uv, uv1, uv2, uv3;
   Color color;
   VecB4 material;
   VecB4 matrix; // #MeshVtxBoneHW
   VecB4 blend;
   Flt   size;

   void setNrmTan(C Vec &nrm, C Vec &tan            ) {T.nrm=nrm; T.tan.set(tan,                                 +1.0f        );} // set normal tangent binormal from 'normal' 'tangent'           , this method is faster, use it when you don't use mirroring in uv mapping or you don't use binormal in the shader at all
   void setNrmTan(C Vec &nrm, C Vec &tan, C Vec &bin) {T.nrm=nrm; T.tan.set(tan, (Dot(Cross(nrm, tan), bin)>0) ? +1.0f : -1.0f);} // set normal tangent binormal from 'normal' 'tangent' 'binormal'
};
#endif
struct Vtx2DUV
{
   Vec2 pos, uv;
};
struct Vtx2DUVCol
{
   Vec2  pos, uv;
   Color color;
};
struct Vtx3DUV
{
   Vec  pos;
   Vec2 uv;
};
struct Vtx3DUVCol
{
   Vec   pos;
   Vec2  uv;
   Color color;
};
struct Vtx3DSimple
{
   Vec   pos, nrm;
   Vec2  uv;
   Color color;
};
struct Vtx3DStandard
{
   Vec   pos, nrm;
   Vec4  tan; // tan.xyz=tangent, tan.w=binormal direction (should be -1 or +1)
   Vec2  uv;
   Color color;

   void setNrmTan(C Vec &nrm, C Vec &tan            ) {T.nrm=nrm; T.tan.set(tan,                                 +1.0f        );} // set normal tangent binormal from 'normal' 'tangent'           , this method is faster, use it when you don't use mirroring in uv mapping or you don't use binormal in the shader at all
   void setNrmTan(C Vec &nrm, C Vec &tan, C Vec &bin) {T.nrm=nrm; T.tan.set(tan, (Dot(Cross(nrm, tan), bin)>0) ? +1.0f : -1.0f);} // set normal tangent binormal from 'normal' 'tangent' 'binormal'
};
/******************************************************************************/
struct VtxIndBuf // Vertex Index Buffer - used for buffered drawing
{
   // operations
   static void shader    (C Shader *shader); // set custom shader
   static void image     (C Image  *image ); // set texture
#if EE_PRIVATE
   static void imageConditional(C Image *image, ShaderImage &shader_image); // set texture for custom shader image, but only if different
   static void color     (C Vec4   &color ); // set color
   static void color1    (C Vec4   &color ); // set color
#endif
   static void color     (C Color  &color ); // set color
   static void color1    (C Color  &color ); // set color1
   static void cull      (Bool      cull  ); // set face  culling
   static void depthWrite(Bool      on    ); // set depth writing (this will affect only drawing that normally uses depth buffer)
   static void alphaTest (Bool      on    ); // set alpha testing (currently this is supported only for drawing faces using 'Vtx3DUV' and 'Vtx3DUVCol' as parameters)
   static void fog       (Bool      on    ); // set fog   usage   (currently this is supported only for drawing faces using 'Vtx3DUV' and 'Vtx3DUVCol' as parameters), if this is enabled then any current 'Fog' will affect the face colors
   static void clamp     (                ); // set texture addressing to (X:clamp, Y:clamp)
   static void wrap      (                ); // set texture addressing to (X:wrap , Y:wrap )
   static void wrapX     (                ); // set texture addressing to (X:wrap , Y:clamp)
   static void wrapY     (                ); // set texture addressing to (X:clamp, Y:wrap )
   static void clampAniso(                ); // set texture addressing to (X:clamp, Y:clamp) anisotropic
   static void flush     (                ); // flush queued data, calling this method is optional as 'end' method will automatically call it, you can call this method during drawing before changing some shader parameters
   static void end       (                ); // flush and finish drawing, this must be called after each series of drawing

   // draw dots
   static void dot(                C Vec2 &pos, Flt r=0.007f); // this uses 'VI.color'
   static void dot(                C Vec  &pos, Flt r=0.007f); // this uses 'VI.color'
   static void dot(C Color &color, C Vec2 &pos, Flt r=0.007f);
   static void dot(C Color &color, C Vec  &pos, Flt r=0.007f);

   // draw rectangles
   static void rect(                C Rect &rect); // this uses 'VI.color'
   static void rect(C Color &color, C Rect &rect);

   // draw non-filled rectangles (lines only)
   static void rectL(                C Rect &rect); // this uses 'VI.color'
   static void rectL(C Color &color, C Rect &rect);

   // draw shaded rectangles
   static void rectShadedX(C Color &color0, C Color &color1, C Rect &rect); // shaded horizontally
   static void rectShadedY(C Color &color0, C Color &color1, C Rect &rect); // shaded   vertically

   // draw lines
   static void line(                                C Vec2 &a, C Vec2 &b           ); // this uses 'VI.color'
   static void line(                                C Vec2 &a, C Vec2 &b, Flt width); // this uses 'VI.color'
   static void line(                                C Vec  &a, C Vec  &b           ); // this uses 'VI.color'
   static void line(C Color &color,                 C Vec2 &a, C Vec2 &b           );
   static void line(C Color &color,                 C Vec2 &a, C Vec2 &b, Flt width);
   static void line(C Color &color,                 C Vec  &a, C Vec  &b           );
   static void line(C Color &col_a, C Color &col_b, C Vec2 &a, C Vec2 &b           );
   static void line(C Color &col_a, C Color &col_b, C Vec2 &a, C Vec2 &b, Flt width);
   static void line(C Color &col_a, C Color &col_b, C Vec  &a, C Vec  &b           );

   // draw triangles
   static void tri(                                                C Tri2 &tri                    ); // this uses 'VI.color'
   static void tri(                                                C Tri  &tri                    ); // this uses 'VI.color'
   static void tri(                                                C Vec2 &a, C Vec2 &b, C Vec2 &c); // this uses 'VI.color'
   static void tri(                                                C Vec  &a, C Vec  &b, C Vec  &c); // this uses 'VI.color'
   static void tri(C Color &color,                                 C Vec2 &a, C Vec2 &b, C Vec2 &c);
   static void tri(C Color &color,                                 C Vec  &a, C Vec  &b, C Vec  &c);
   static void tri(C Color &color,                                 C Tri  &tri                    );
   static void tri(C Color &col_a, C Color &col_b, C Color &col_c, C Vec2 &a, C Vec2 &b, C Vec2 &c);
   static void tri(C Color &col_a, C Color &col_b, C Color &col_c, C Vec  &a, C Vec  &b, C Vec  &c);

   // draw quads
   static void quad(                               C Quad2 &quad                             ); // this uses 'VI.color'
   static void quad(                               C Quad  &quad                             ); // this uses 'VI.color'
   static void quad(C Color &color,                C Quad2 &quad                             );
   static void quad(C Color &color,                C Quad  &quad                             );
   static void quad(                               C Vec2 &a, C Vec2 &b, C Vec2 &c, C Vec2 &d); // this uses 'VI.color'
   static void quad(                               C Vec  &a, C Vec  &b, C Vec  &c, C Vec  &d); // this uses 'VI.color'
   static void quad(C Color &color,                C Vec2 &a, C Vec2 &b, C Vec2 &c, C Vec2 &d);
   static void quad(C Color &color,                C Vec  &a, C Vec  &b, C Vec  &c, C Vec  &d);
   static void quad(C Color &col0 , C Color &col1, C Vec2 &a, C Vec2 &b, C Vec2 &c, C Vec2 &d);
   static void quad(C Color &col0 , C Color &col1, C Vec  &a, C Vec  &b, C Vec  &c, C Vec  &d);

   // draw image
   static void image    (C Rect &screen_rect                 ); // this uses 'VI.color' and 'VI.color1' as "FinalColor = Image*color + color1"
   static void imagePart(C Rect &screen_rect, C Rect &uv_rect); // this uses 'VI.color' and 'VI.color1' as "FinalColor = Image*color + color1"
#if EE_PRIVATE
   static void font     (C Rect &screen_rect, C Rect &uv_rect);
#endif

   // draw image at selected depth
   static void imageDepth    (                C Rect &screen_rect                 , Flt depth);
   static void imageDepth    (C Color &color, C Rect &screen_rect                 , Flt depth);
   static void imagePartDepth(                C Rect &screen_rect, C Rect &uv_rect, Flt depth);
   static void imagePartDepth(C Color &color, C Rect &screen_rect, C Rect &uv_rect, Flt depth);

   // draw faces
   static void face(C Vtx2DUV &a, C Vtx2DUV &b, C Vtx2DUV &c);
   static void face(C Vtx2DUV &a, C Vtx2DUV &b, C Vtx2DUV &c, C Vtx2DUV &d);

   static void face(C Vtx2DUVCol &a, C Vtx2DUVCol &b, C Vtx2DUVCol &c);
   static void face(C Vtx2DUVCol &a, C Vtx2DUVCol &b, C Vtx2DUVCol &c, C Vtx2DUVCol &d);

   static void face(C Vtx3DUV &a, C Vtx3DUV &b, C Vtx3DUV &c);
   static void face(C Vtx3DUV &a, C Vtx3DUV &b, C Vtx3DUV &c, C Vtx3DUV &d);

   static void face(C Vtx3DUVCol &a, C Vtx3DUVCol &b, C Vtx3DUVCol &c);
   static void face(C Vtx3DUVCol &a, C Vtx3DUVCol &b, C Vtx3DUVCol &c, C Vtx3DUVCol &d);

   static void face(C Vtx3DSimple &a, C Vtx3DSimple &b, C Vtx3DSimple &c);
   static void face(C Vtx3DSimple &a, C Vtx3DSimple &b, C Vtx3DSimple &c, C Vtx3DSimple &d);

   static void face(C Vtx3DStandard &a, C Vtx3DStandard &b, C Vtx3DStandard &c);
   static void face(C Vtx3DStandard &a, C Vtx3DStandard &b, C Vtx3DStandard &c, C Vtx3DStandard &d);

#if EE_PRIVATE
   static void face(C Vtx3DFull &a, C Vtx3DFull &b, C Vtx3DFull &c);
   static void face(C Vtx3DFull &a, C Vtx3DFull &b, C Vtx3DFull &c, C Vtx3DFull &d);

          void del     ();
          void create  ();
   static void clear   ();
   static void setType (VI_TYPE vtx_type, UInt flag=0);
   static void setFirst(VI_TYPE vtx_type, UInt flag=0);

   // lock / unlock
   static Bool lockVtx();   static void unlockVtx();
 //static Bool lockInd();   static void unlockInd();

   // draw
   static void flushIndexed(IndBuf &ib, Int ind_num);

   // add
   static Ptr addVtx(Int vtxs);
#endif

#if !EE_PRIVATE
private:
#endif
   Bool       _quad_ind, _depth_write;
   Byte       _vtx_type, _flag, _user_flag;
   Int        _mem_max,
              _vtx_queued, _vtx_drawing, _vtx_drawing_raw,
              _ind_div, _ind_sub;
 C Image     *_image;
 C Shader    *_shader;
   Byte      *_vtx_buf;
   VtxFormat  _vf2D_flat, _vf2D_col, _vf2D_uv, _vf2D_uv_col, _vf2D_uv2, _vf2D_font, _vf3D_flat, _vf3D_col, _vf3D_uv, _vf3D_uv_col, _vf3D_bilb, _vf3D_bilb_anim, _vf3D_laser, _vf3D_cloth, _vf3D_simple, _vf3D_standard, _vf3D_full;
   VtxBuf     _vb;
   UInt       _prim_type;

   VtxIndBuf();
}extern
   VI; // Buffered Drawing
/******************************************************************************/
