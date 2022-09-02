/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************

   Use 'LightDir'    to add a directional light onto the scene
   Use 'LightPoint'  to add a point       light onto the scene
   Use 'LightLinear' to add a point       light onto the scene (with small range)
   Use 'LightCone'   to add a cone        light onto the scene

   Access 'CurrentLight' to gain informations about the current light which is being applied.

/******************************************************************************/
enum LIGHT_TYPE : Byte // Light Type
{
   LIGHT_NONE  , // none
   LIGHT_DIR   , // directional
   LIGHT_POINT , // point
   LIGHT_LINEAR, // point with small range
   LIGHT_CONE  , // cone
};
/******************************************************************************/
struct LightDir // Directional Light
{
   Vec dir         , // direction          , normalized vector
       color_l     ; // color linear gamma , (0,0,0) .. (1,1,1)
   Flt radius_frac , // radius fraction    , (0..1  )
       vol         , // volumetric amount  , (0..1  )
       vol_exponent, // volumetric exponent, (0..Inf)
       vol_steam   ; // volumetric steam   , (0..1  )

   void add(Bool shadow=true, CPtr light_src=null); // add light to scene, this needs to be called only in RM_PREPARE mode, 'shadow'=if shadowing enabled, 'light_src'=custom pointer to light source (which can be later accessed from "CurrentLight.src")
   void set(                                     ); // use only outside Renderer rendering, before drawing any shade'able meshes

   LightDir() {}
   LightDir(C Vec &dir, C Vec &color_l=Vec(1, 1, 1), Flt radius_frac=0.0036f, Flt vol=0, Flt vol_exponent=1, Flt vol_steam=0.5f) {T.dir=dir; T.color_l=color_l; T.radius_frac=radius_frac; T.vol=vol; T.vol_exponent=vol_exponent; T.vol_steam=vol_steam;}
};
/******************************************************************************/
struct LightPoint // Point Light
{
   Flt  power  , // power             , (0..Inf), determines light range
        lum_max, // maximum luminance , (0..Inf)
        vol    , // volumetric amount , (0..Inf)
        vol_max; // volumetric maximum, (0..1  )
   VecD pos    ; // position          ,
   Vec  color_l; // color linear gamma, (0,0,0) .. (1,1,1)

   Flt  range(                                            )C; // get affected range according to light's 'power'
   void add  (Flt shadow_opacity=1.0f, CPtr light_src=null) ; // add light to scene, this needs to be called only in RM_PREPARE mode, 'shadow_opacity'=opacity of shadows (0..1) where value 0 disables shadowing, value 1 sets full shadows, and values between allow for manual blending the shadows, 'light_src'=custom pointer to light source (which can be later accessed from "CurrentLight.src")

   LightPoint() {}
   LightPoint(Flt power, C VecD &pos, C Vec &color_l=Vec(1, 1, 1), Flt lum_max=1, Flt vol=0, Flt vol_max=0.5f) {T.power=power; T.pos=pos; T.color_l=color_l; T.lum_max=lum_max; T.vol=vol; T.vol_max=vol_max;}
};
/******************************************************************************/
struct LightLinear // Point Light with small range
{
   Flt  range  , // range             , (0..Inf)
        vol    , // volumetric amount , (0..Inf)
        vol_max; // volumetric maximum, (0..1  )
   VecD pos    ; // position          ,
   Vec  color_l; // color linear gamma, (0,0,0) .. (1,1,1)

   void add(Flt shadow_opacity=1.0f, CPtr light_src=null); // add light to scene, this needs to be called only in RM_PREPARE mode, 'shadow_opacity'=opacity of shadows (0..1) where value 0 disables shadowing, value 1 sets full shadows, and values between allow for manual blending the shadows, 'light_src'=custom pointer to light source (which can be later accessed from "CurrentLight.src")

   LightLinear() {}
   LightLinear(Flt range, C VecD &pos, C Vec &color_l=Vec(1, 1, 1), Flt vol=0, Flt vol_max=0.5f) {T.range=range; T.pos=pos; T.color_l=color_l; T.vol=vol; T.vol_max=vol_max;}
};
/******************************************************************************/
struct LightCone // Cone Light
{
   Flt      falloff, // light falloff     , (0..1  ), default=0.5
            vol    , // volumetric amount , (0..Inf)
            vol_max; // volumetric maximum, (0..1  )
   Vec      color_l; // color linear gamma, (0,0,0) .. (1,1,1)
   PyramidM pyramid; // pyramid           , determines orientation of the light

   void add(Flt shadow_opacity=1.0f, CPtr light_src=null, Image *image=null, Flt image_scale=1); // add light to scene, this needs to be called only in RM_PREPARE mode, 'shadow_opacity'=opacity of shadows (0..1) where value 0 disables shadowing, value 1 sets full shadows, and values between allow for manual blending the shadows, 'light_src'=custom pointer to light source (which can be later accessed from "CurrentLight.src"), 'image'=dynamic lightmap, 'image_scale'=scale dynamic lightmap

   LightCone() {}
   LightCone(Flt length, C VecD &pos, C Vec &dir, C Vec &color_l=Vec(1, 1, 1), Flt vol=0, Flt vol_max=0.5f);
};
/******************************************************************************/
struct Light
{
   LIGHT_TYPE type          ; // light type
   Bool       shadow        ; // if shadowing enabled
   Flt        shadow_opacity; // opacity of shadows
   Flt        image_scale   ; // dynamic lightmap scale
   Rect       rect          ; // screen rectangle affected by light
   CPtr       src           ; // custom pointer to light source
   Image     *image         ; // dynamic lightmap
   union
   {
      LightDir    dir   ; // directional light, valid when "type==LIGHT_DIR"
      LightPoint  point ; // point       light, valid when "type==LIGHT_POINT"
      LightLinear linear; // point       light, valid when "type==LIGHT_LINEAR"
      LightCone   cone  ; // cone        light, valid when "type==LIGHT_CONE"
   };

   // get / set
   Flt  range()C; // get light range    (this is equal to 0       for directional lights)
   Flt  vol  ()C; // get light volumetric amount
   VecD pos  ()C; // get light position (this is equal to (0,0,0) for directional lights)

   Light() {} // needed because of union
}extern
   CurrentLight; // this contains information about the light which is currently rendered
/******************************************************************************/
Flt GetLightFade(CPtr src); // get fade value of a light for specified 'Light.src' parameter, this can be called after RM_PREPARE
/******************************************************************************/
