/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************/
struct ShaderImage // Shader Image
{
 C Image* get(                 )C {return   _image  ;}
   void   set(C Image    *image)  {T._image= image  ;}
   void   set(C Image    &image)  {T._image=&image  ;}
 //void   set(C ImagePtr &image)  {T._image= image();} this is not safe, as 'ShaderImage' does not store 'ImagePtr' for performance reasons

private:
 C Image *_image=null;
};
struct ShaderRWImage // Shader Read Write Image
{
 C ImageRT* get(                )C {return   _image;}
   void     set(C ImageRT *image)  {T._image= image;}
   void     set(C ImageRT &image)  {T._image=&image;}

private:
 C ImageRT *_image=null;
};
/******************************************************************************/
struct ShaderParam // Shader Parameter
{
            void set(  Bool     b               ); // set boolean  value
            void set(  Int      i               ); // set integer  value
            void set(  Flt      f               ); // set float    value
            void set(  Dbl      d               ); // set double   value
            void set(C Vec2    &v               ); // set vector2D value
            void set(C VecD2   &v               ); // set vector2D value
            void set(C VecI2   &v               ); // set vector2D value
            void set(C Vec     &v               ); // set vector3D value
            void set(C VecD    &v               ); // set vector3D value
            void set(C VecI    &v               ); // set vector3D value
            void set(C Vec4    &v               ); // set vector4D value
            void set(C VecD4   &v               ); // set vector4D value
            void set(C VecI4   &v               ); // set vector4D value
            void set(C Color   &color           ); // set vector4D value
            void set(C Rect    &rect            ); // set vector4D value
            void set(C Matrix3 &matrix          ); // set matrix3  value
            void set(C Matrix  &matrix          ); // set matrix   value
            void set(C MatrixM &matrix          ); // set matrix   value
            void set(C Matrix4 &matrix          ); // set matrix4  value
            void set(C Vec     *v     , Int elms); // set vector3D array
            void set(C Vec4    *v     , Int elms); // set vector4D array
            void set(C Matrix  *matrix, Int elms); // set matrix   array
            void set(  CPtr     data  , Int size); // set memory
   T1(TYPE) void set(C TYPE    &data            ) {set((CPtr)&data, SIZE(data));}
};
struct ShaderParamBool : private ShaderParam // Shader Parameter
{
   void set(Bool b); // set boolean value
};
struct ShaderParamInt : private ShaderParam // Shader Parameter
{
   void set(  Int    i); // set integer  value
   void set(C VecI2 &v); // set vector2D value
   void set(C VecI  &v); // set vector3D value
   void set(C VecI4 &v); // set vector4D value
   void set(C RectI &v); // set vector4D value
};
/******************************************************************************/
struct ShaderParamChange // Shader Parameter Change
{
   ShaderParam *param; // parameter to change
   Vec4         value; // value     to change to

   ShaderParamChange& set(  Bool  b) {value.x  =b; return T;}
   ShaderParamChange& set(  Int   i) {value.x  =i; return T;}
   ShaderParamChange& set(  Flt   f) {value.x  =f; return T;}
   ShaderParamChange& set(C Vec2 &v) {value.xy =v; return T;}
   ShaderParamChange& set(C Vec  &v) {value.xyz=v; return T;}
   ShaderParamChange& set(C Vec4 &v) {value    =v; return T;}

   ShaderParamChange& set(ShaderParam *param) {T.param=param; return T;}

   ShaderParamChange() {param=null; value.zero();}
};
/******************************************************************************/
struct ShaderData : Mems<Byte>
{
};
struct Shader
{
   void draw(                C Rect *rect=null        )C;                             // apply custom 2D effect on the screen, 'image'=image to automatically set as 'Img' shader image, 'rect'=screen rectangle for the effect (set null for full viewport)
   void draw(C Image *image, C Rect *rect=null        )C;                             // apply custom 2D effect on the screen, 'image'=image to automatically set as 'Img' shader image, 'rect'=screen rectangle for the effect (set null for full viewport)
   void draw(C Image &image, C Rect *rect=null        )C {draw(&image  , rect     );} // apply custom 2D effect on the screen, 'image'=image to automatically set as 'Img' shader image, 'rect'=screen rectangle for the effect (set null for full viewport)
   void draw(                C Rect *rect, C Rect &tex)C;                             // apply custom 2D effect on the screen, 'image'=image to automatically set as 'Img' shader image, 'rect'=screen rectangle for the effect (set null for full viewport), 'tex'=source image texture coordinates
   void draw(C Image *image, C Rect *rect, C Rect &tex)C;                             // apply custom 2D effect on the screen, 'image'=image to automatically set as 'Img' shader image, 'rect'=screen rectangle for the effect (set null for full viewport), 'tex'=source image texture coordinates
   void draw(C Image &image, C Rect *rect, C Rect &tex)C {draw(&image  , rect, tex);} // apply custom 2D effect on the screen, 'image'=image to automatically set as 'Img' shader image, 'rect'=screen rectangle for the effect (set null for full viewport), 'tex'=source image texture coordinates*/
};
struct ComputeShader
{
};
/******************************************************************************/
struct ShaderFile // Shader File
{
   // get
          Int            shaders(            )C {return         _shaders.elms();} // get number of         shaders in this file
          Int     computeShaders(            )C {return _compute_shaders.elms();} // get number of compute shaders in this file
          Shader*        shader (Int i       ); // get i-th         shader, null on fail
   ComputeShader* computeShader (Int i       ); // get i-th compute shader, null on fail
          Shader*        find   (C Str8 &name); // find             shader, null on fail
   ComputeShader* computeFind   (C Str8 &name); // find     compute shader, null on fail
          Shader*        get    (C Str8 &name); // get              shader, Exit on fail
   ComputeShader* computeGet    (C Str8 &name); // get      compute shader, Exit on fail

   // manage
   void del();

   // io
   Bool load(C Str &name); // load, false on fail

   ShaderFile();
  ~ShaderFile() {del();}

private:
   Mems<ShaderData   > _vs, _hs, _ds, _ps, _cs, _buffer_links, _image_links, _rw_image_links;
   Mems<       Shader>         _shaders;
   Mems<ComputeShader> _compute_shaders;
   NO_COPY_CONSTRUCTOR(ShaderFile);
};
/******************************************************************************/
extern Cache<ShaderFile> ShaderFiles; // Shader File Cache
/******************************************************************************/
struct ShaderMacro // macro used for shader compilation
{
   Str8 name      ,
        definition;

   void set(C Str8 &name, C Str8 &definition) {T.name=name; T.definition=definition;}
};
/******************************************************************************/
// shader image
ShaderImage* FindShaderImage(CChar8 *name); // find shader image, null on fail (shader image can be returned only after loading a shader which contains the image)
ShaderImage*  GetShaderImage(CChar8 *name); // find shader image, Exit on fail (shader image can be returned only after loading a shader which contains the image)

// shader read write image
ShaderRWImage* FindShaderRWImage(CChar8 *name); // find shader read write image, null on fail (shader image can be returned only after loading a shader which contains the image)
ShaderRWImage*  GetShaderRWImage(CChar8 *name); // find shader read write image, Exit on fail (shader image can be returned only after loading a shader which contains the image)

// shader parameter
ShaderParam* FindShaderParam(CChar8 *name); // find shader parameter, null on fail (shader parameter can be returned only after loading a shader which contains the parameter)
ShaderParam*  GetShaderParam(CChar8 *name); // find shader parameter, Exit on fail (shader parameter can be returned only after loading a shader which contains the parameter)

inline ShaderParamInt * FindShaderParamInt (CChar8 *name) {return (ShaderParamInt *)FindShaderParam(name);}
inline ShaderParamBool*  GetShaderParamBool(CChar8 *name) {return (ShaderParamBool*) GetShaderParam(name);}
inline ShaderParamInt *  GetShaderParamInt (CChar8 *name) {return (ShaderParamInt *) GetShaderParam(name);}

         inline void SPSet(CChar8 *name,   Bool     b               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(b           );} // set boolean  value
         inline void SPSet(CChar8 *name,   Int      i               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(i           );} // set integer  value
         inline void SPSet(CChar8 *name,   Flt      f               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(f           );} // set float    value
         inline void SPSet(CChar8 *name,   Dbl      d               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(d           );} // set double   value
         inline void SPSet(CChar8 *name, C Vec2    &v               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(v           );} // set vector2D value
         inline void SPSet(CChar8 *name, C VecD2   &v               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(v           );} // set vector2D value
         inline void SPSet(CChar8 *name, C VecI2   &v               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(v           );} // set vector2D value
         inline void SPSet(CChar8 *name, C Vec     &v               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(v           );} // set vector3D value
         inline void SPSet(CChar8 *name, C VecD    &v               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(v           );} // set vector3D value
         inline void SPSet(CChar8 *name, C VecI    &v               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(v           );} // set vector3D value
         inline void SPSet(CChar8 *name, C Vec4    &v               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(v           );} // set vector4D value
         inline void SPSet(CChar8 *name, C VecD4   &v               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(v           );} // set vector4D value
         inline void SPSet(CChar8 *name, C VecI4   &v               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(v           );} // set vector4D value
         inline void SPSet(CChar8 *name, C Color   &color           ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(color       );} // set vector4D value
         inline void SPSet(CChar8 *name, C Rect    &rect            ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(rect        );} // set vector4D value
         inline void SPSet(CChar8 *name, C Matrix3 &matrix          ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(matrix      );} // set matrix   value
         inline void SPSet(CChar8 *name, C Matrix  &matrix          ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(matrix      );} // set matrix   value
         inline void SPSet(CChar8 *name, C Matrix4 &matrix          ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(matrix      );} // set matrix4  value
         inline void SPSet(CChar8 *name, C Vec     *v     , Int elms) {if(ShaderParam *sp=FindShaderParam(name))sp->set(v     , elms);} // set vector3D array
         inline void SPSet(CChar8 *name, C Vec4    *v     , Int elms) {if(ShaderParam *sp=FindShaderParam(name))sp->set(v     , elms);} // set vector4D array
         inline void SPSet(CChar8 *name, C Matrix  *matrix, Int elms) {if(ShaderParam *sp=FindShaderParam(name))sp->set(matrix, elms);} // set matrix   array
         inline void SPSet(CChar8 *name,   CPtr     data  , Int size) {if(ShaderParam *sp=FindShaderParam(name))sp->set(data  , size);} // set memory
T1(TYPE) inline void SPSet(CChar8 *name, C TYPE    &data            ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(data        );} // set memory

         inline void SPISet(CChar8 *name,   Int    i) {if(ShaderParamInt *sp=FindShaderParamInt(name))sp->set(i);} // set integer  value
         inline void SPISet(CChar8 *name, C VecI2 &v) {if(ShaderParamInt *sp=FindShaderParamInt(name))sp->set(v);} // set vector2D value
         inline void SPISet(CChar8 *name, C VecI  &v) {if(ShaderParamInt *sp=FindShaderParamInt(name))sp->set(v);} // set vector3D value
         inline void SPISet(CChar8 *name, C VecI4 &v) {if(ShaderParamInt *sp=FindShaderParamInt(name))sp->set(v);} // set vector4D value
/******************************************************************************/
