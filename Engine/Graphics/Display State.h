/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************/
enum ALPHA_MODE : Byte // Alpha Blending Modes
{
   ALPHA_NONE         , // Color:set                      , Alpha:set
   ALPHA_BLEND        , // Color:blend                    , Alpha:increase
   ALPHA_MERGE        , // Color:blend alpha premultiplied, Alpha:increase
   ALPHA_ADD          , // Color:add                      , Alpha:add
   ALPHA_MUL          , // Color:multiply                 , Alpha:multiply
   ALPHA_ADD_KEEP     , // Color:add                      , Alpha:keep
   ALPHA_ADDBLEND_KEEP, // Color:add blended              , Alpha:keep

   ALPHA_RENDER_BLEND       , // Color:blend, Alpha:decrease         ,   RT1: Color: increase,   RT2: Color:blend   #RTOutput.Blend
   ALPHA_RENDER_BLEND_FACTOR, // Color:blend, Alpha:blend with factor,   RT1: Color: increase,   RT2: Color:blend   #RTOutput.Blend
};
/******************************************************************************/
struct DisplayState // Display States Control, this class methods can be called by the use of 'Display' object
{
          ALPHA_MODE alpha      (                    )C {return _alpha;} // get alpha blending mode
   static ALPHA_MODE alpha      (ALPHA_MODE alpha    );                  // set alpha blending mode and return previous mode
   static void       clip       (C Rect    *rect=null);                  // set rectangle clipping, null for none
   static void       clip       (C Rect    &rect     ) {clip(&rect);}    // set rectangle clipping
   static void       depthLock  (Bool       on       );                  // set    depth buffer usage and lock it
   static void       depthUnlock(                    );                  // unlock depth buffer usage
   static Bool       depthWrite (Bool       on       );                  // set    depth buffer writing and return previous state
   static Bool       lineSmooth (Bool       on       );                  // set line smoothing (anti-aliasing) and return previous state, enabling this option can significantly reduce performance of drawing lines, default=false

private:
   ALPHA_MODE _alpha;
   Bool       _depth_lock, _depth, _depth_write, _depth_clip, _cull, _line_smooth, _wire, _clip, _clip_allow, _clip_real, _clip_plane_allow, _front_face, _linear_gamma;
   Byte       _depth_bias, _stencil, _stencil_ref, _col_write[4];
   UInt       _depth_func, _sample_mask, _fbo;
   RectI      _viewport, _clip_recti;
   Rect       _clip_rect;
   Color      _alpha_factor;
   Vec4       _alpha_factor_v4, _clip_plane;
   UInt       _prim_type;
   Ptr        _vf;
   DisplayState();
};
/******************************************************************************/
