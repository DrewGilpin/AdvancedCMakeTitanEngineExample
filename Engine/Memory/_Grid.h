/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************/
struct _Cell // Cell - Do not use this class, use 'Cell' instead
{
private:
   Ptr   _data;
   Int   _x[4],
         _y[4];
  _Cell *_parent;
   union
   {
      struct{_Cell *_g[9];};
      struct{_Cell *_lb, *_b, *_rb, *_l, *_c, *_r, *_lf, *_f, *_rf;};
   };

  _Cell() {Zero(T);}

   NO_COPY_CONSTRUCTOR(_Cell);
};
/******************************************************************************/
struct _Grid // Grid - Do not use this class, use 'Grid' instead
{
   Ptr user;

   void   del(             ) ;
   void   del( _Cell  *cell) ;
  _Cell&  get(C VecI2 &xy  ) ;
  _Cell* find(C VecI2 &xy  )C;
   Bool  size(  RectI &rect)C;
   void  fastAccess(C RectI *rect);

   void func      (               void func(_Cell &cell, Ptr user), Ptr user);
   void func      (C RectI &rect, void func(_Cell &cell, Ptr user), Ptr user);
   void funcCreate(C RectI &rect, void func(_Cell &cell, Ptr user), Ptr user);

   void mtFunc(Threads &threads,                void func(_Cell &cell, Ptr user, Int thread_index), Ptr user);
   void mtFunc(Threads &threads, C RectI &rect, void func(_Cell &cell, Ptr user, Int thread_index), Ptr user);

   T2(TYPE, EXTENDED)   void replaceClass()
   {
      struct Helper
      {
         static void New(EXTENDED* &elm, C VecI2 &xy, Ptr grid_user) {Alloc(elm); new(elm)EXTENDED(xy, grid_user);} // first allocate memory to setup pointer, then call the constructor in case the constructor checks the grid for self
         static void Del(EXTENDED* &elm                            ) {if(elm){elm->~EXTENDED(); Free(elm);}}
      };
      ASSERT_BASE_EXTENDED<TYPE, EXTENDED>();
      del();
     _new=(void (*)(Ptr &elm, C VecI2 &xy, Ptr grid_user))Helper::New;
     _del=(void (*)(Ptr &elm                            ))Helper::Del;
   }

 ~_Grid() {del();}

private:
  _Cell        *_root;
   Int          _fast_access_mul;
   RectI        _fast_access_rect;
   Mems<_Cell*> _fast_access_cell;
   void       (*_new)(Ptr &elm, C VecI2 &xy, Ptr grid_user);
   void       (*_del)(Ptr &elm                            );

   explicit _Grid() {user=null; _root=null; _fast_access_mul=0; _fast_access_rect.set(0, 0, -1, -1); _new=null; _del=null;}

   NO_COPY_CONSTRUCTOR(_Grid);

   T1(TYPE) friend struct Grid;
};
/******************************************************************************/
