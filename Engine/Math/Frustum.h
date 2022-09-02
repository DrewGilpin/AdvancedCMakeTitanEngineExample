﻿/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************

   Use 'Frustum' to detect shapes visibility according to the camera's viewing frustum.

   Sample Usage:

      Ball ball;
      if(Frustum(ball)).. // if ball is visible in current frustum

/******************************************************************************/
struct FrustumClass // Frustum
{
   // if shape intersects with frustum
   Bool operator()(C Vec  &point)C;
   Bool operator()(C VecD &point)C;

   Bool operator()(C Ball  &ball)C;
   Bool operator()(C BallM &ball)C;

   Bool operator()(C Capsule  &capsule)C;
   Bool operator()(C CapsuleM &capsule)C;

   Bool operator()(C Extent &ext                         )C;
   Bool operator()(C Extent &ext, C Matrix  &matrix      )C; // 'ext' transformed by 'matrix'
   Bool operator()(C Extent &ext, C MatrixM &matrix      )C; // 'ext' transformed by 'matrix'
   Bool operator()(C Extent &ext,   Bool    &fully_inside)C; // 'fully_inside'=after this function returns this will be set to if the 'ext' is fully inside the frustum

   Bool operator()(C Box &box                         )C;
   Bool operator()(C Box &box, C Matrix  &matrix      )C; // 'box' transformed by 'matrix'
   Bool operator()(C Box &box, C MatrixM &matrix      )C; // 'box' transformed by 'matrix'
   Bool operator()(C Box &box,   Bool    &fully_inside)C; // 'fully_inside'=after this function returns this will be set to if the 'box' is fully inside the frustum

   Bool operator()(C OBox &obox)C;

   Bool operator()(C Shape &shape            )C;
   Bool operator()(C Shape *shape, Int shapes)C;

   Bool operator()(C Mesh &mesh                   )C {return T(mesh.ext        );} // 'mesh.ext'
   Bool operator()(C Mesh &mesh, C Matrix  &matrix)C {return T(mesh.ext, matrix);} // 'mesh.ext' transformed by 'matrix'
   Bool operator()(C Mesh &mesh, C MatrixM &matrix)C {return T(mesh.ext, matrix);} // 'mesh.ext' transformed by 'matrix'

   void getIntersectingAreas(MemPtr<VecI2> area_pos, Flt area_size, Bool distance_check, Bool sort_by_distance, Bool extend, C RectI *clamp=null)C; // get 'area_pos' coordinates of areas intersecting with this Frustum, 'area_size'=size of a single area, 'distance_check'=list only areas within frustum range, 'sort_by_distance'=if sort areas by distance from camera, 'extend'=if extend frustum by half of 'area_size', 'clamp'=optionally process areas only within this inclusive rectangle, this assumes that areas are located on flat XZ plane, so only XZ coordinates of all 3D vectors are processed and Y is ignored

private:
   VecD    point[ 8]; Int points;
   VecI2   edge [12]; Int edges ;
   Bool    persp;
   Byte    extra;
   Flt     range, eye_dist_2, view_quad_max_dist;
   Vec2    fov_tan, fov_cos_inv;
   Vec     size, plane_n_abs[DIR_NUM], extra_plane_n_abs;
   PlaneM  plane[DIR_NUM], extra_plane;
   BallM   extra_ball; Flt extra_ball_r2;
   MatrixM matrix;
}extern
   Frustum; // Active Frustum
/******************************************************************************/
