/******************************************************************************

   Use 'Frustum' to detect shapes visibility according to the camera's viewing frustum.

   Sample Usage:

      Ball ball;
      if(Frustum(ball)).. // if ball is visible in current frustum

/******************************************************************************/
struct FrustumData // contains Frustum Data that can be transformed
{
#if !EE_PRIVATE
private:
#endif
#define FRUSTUM_EXTRA_PLANE 0
#define FRUSTUM_EXTRA_BALL  SUPPORT_RT_FORWARD
#define FRUSTUM_EXTRA       (FRUSTUM_EXTRA_PLANE || FRUSTUM_EXTRA_BALL)
   VecD    point      [8];
   PlaneM  plane      [DIR_NUM];
   Vec     plane_n_abs[DIR_NUM];
   MatrixM matrix;
#if FRUSTUM_EXTRA_PLANE
   Vec     extra_plane_n_abs;
   PlaneM  extra_plane;
#endif
#if FRUSTUM_EXTRA_BALL
   BallM   extra_ball; Flt extra_ball_r2;
#endif
};
struct FrustumClass : FrustumData // Frustum
{
   // if shape intersects with frustum
   Bool operator()(C Vec  &point)C;
   Bool operator()(C VecD &point)C;

   Bool operator()(C Ball  &ball)C;
   Bool operator()(C BallM &ball)C;

   Bool operator()(C Capsule  &capsule)C;
   Bool operator()(C CapsuleM &capsule)C;

   Bool operator()(C Extent &ext                                       )C;
   Bool operator()(C Extent &ext, C Matrix3 &matrix                    )C; // 'ext' transformed by 'matrix'
   Bool operator()(C Extent &ext, C Matrix  &matrix                    )C; // 'ext' transformed by 'matrix'
   Bool operator()(C Extent &ext, C MatrixM &matrix                    )C; // 'ext' transformed by 'matrix'
   Bool operator()(C Extent &ext,                    Bool &fully_inside)C; // 'fully_inside'=after this function returns this will be set to if the 'ext' is fully inside the frustum
   Bool operator()(C Extent &ext, C Matrix3 &matrix, Bool &fully_inside)C; // 'fully_inside'=after this function returns this will be set to if the 'ext' is fully inside the frustum
   Bool operator()(C Extent &ext, C Matrix  &matrix, Bool &fully_inside)C; // 'fully_inside'=after this function returns this will be set to if the 'ext' is fully inside the frustum
   Bool operator()(C Extent &ext, C MatrixM &matrix, Bool &fully_inside)C; // 'fully_inside'=after this function returns this will be set to if the 'ext' is fully inside the frustum

   Bool operator()(C Box &box                   )C;
   Bool operator()(C Box &box, C Matrix3 &matrix)C; // 'box' transformed by 'matrix'
   Bool operator()(C Box &box, C Matrix  &matrix)C; // 'box' transformed by 'matrix'
   Bool operator()(C Box &box, C MatrixM &matrix)C; // 'box' transformed by 'matrix'

   Bool operator()(C OBox &obox)C;

   Bool operator()(C Shape &shape            )C;
   Bool operator()(C Shape *shape, Int shapes)C;

   Bool operator()(C Mesh &mesh                   )C {return T(mesh.ext        );} // 'mesh.ext'
   Bool operator()(C Mesh &mesh, C Matrix3 &matrix)C {return T(mesh.ext, matrix);} // 'mesh.ext' transformed by 'matrix'
   Bool operator()(C Mesh &mesh, C Matrix  &matrix)C {return T(mesh.ext, matrix);} // 'mesh.ext' transformed by 'matrix'
   Bool operator()(C Mesh &mesh, C MatrixM &matrix)C {return T(mesh.ext, matrix);} // 'mesh.ext' transformed by 'matrix'

   Bool noForward(C BallM &ball)C; // test without forward plane (assumes infinite view range)

#if EE_PRIVATE
   Bool local(C Ball    &ball   )C; // shape is in Frustum local space
   Bool local(C Capsule &capsule)C; // shape is in Frustum local space

   Bool operator()(C FrustumClass &frustum)C;

   Dbl volume()C;

   void set (Flt range, C Vec2 &fov, C MatrixM &camera); // set from active viewport
   void set (                                         ); // set from active viewport and camera
   void from(C BoxD     &box                          ); // set from box
   void from(C PyramidM &pyramid                      ); // set from pyramid

   void draw(C Color &color=WHITE)C; // this relies on active object matrix which can be set using 'SetMatrix' function
#endif

   void getIntersectingAreas      (MemPtr<VecI2     > area_pos,   Flt       area_size, Bool distance_check, Bool sort_by_distance, Bool extend, C RectI *clamp=null)C; // get 'area_pos' coordinates of areas intersecting with this Frustum, 'area_size'=size of a single area   , 'distance_check'=list only areas within frustum range, 'sort_by_distance'=if sort areas by distance from camera, 'extend'=if extend frustum by half of 'area_size', 'clamp'=optionally process areas only within this inclusive rectangle                       , this assumes that areas are located on flat XZ plane, so only XZ coordinates of all 3D vectors are processed and Y is ignored
   void getIntersectingSphereAreas(MemPtr<SphereArea> area_pos, C SphereConvertEx &sc, Bool distance_check, Bool sort_by_distance, Bool extend, Flt min_height     )C; // get 'area_pos' coordinates of areas intersecting with this Frustum, 'sc'=precalculated sphere conversion, 'distance_check'=list only areas within frustum range, 'sort_by_distance'=if sort areas by distance from camera, 'extend'=if extend frustum by half of 'area_size', 'min_height'=assume that area data is located only above this distance from center of sphere, this assumes that areas are located on a sphere

#if !EE_PRIVATE
private:
#endif
#if EE_PRIVATE
   enum EXTRA
   {
      PLANE=1<<0,
      BALL =1<<1,
   };
#endif
                   Int points;
   VecI2 edge[12]; Int edges ;
   Bool  persp;
#if FRUSTUM_EXTRA
   Byte  extra;
#endif
   Flt   range, eye_dist_2, view_quad_max_dist;
   Vec2  fov_tan, fov_cos_inv;
   Vec   size;

#if EE_PRIVATE
#if FRUSTUM_EXTRA_PLANE
   void setExtraPlane(C PlaneM &plane, Bool chs=false);     Bool extraPlane()C {return FlagOn(extra, PLANE);}
#else
   void setExtraPlane(C PlaneM &plane, Bool chs=false) {}   Bool extraPlane()C {return false;}
#endif
#if FRUSTUM_EXTRA_BALL
   void setExtraBall(C BallM &ball);     Bool extraBall()C {return FlagOn(extra, BALL);}   void clearExtraBall() {FlagDisable(extra, BALL);}
#else
   void setExtraBall(C BallM &ball) {}   Bool extraBall()C {return false              ;}   void clearExtraBall() {}
#endif
#endif
}extern
   Frustum; // Active Frustum
#if EE_PRIVATE
extern FrustumClass FrustumMain;
#endif
/******************************************************************************/
