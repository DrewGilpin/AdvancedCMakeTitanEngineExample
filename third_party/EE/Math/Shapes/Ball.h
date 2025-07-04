/******************************************************************************

   Use 'Ball'  to handle ball shapes, Flt type
   Use 'BallD' to handle ball shapes, Dbl type

/******************************************************************************/
struct Ball // Ball Shape
{
   Flt r  ; // radius
   Vec pos; // center position

   Ball& zero(                         ) {T.r=0; T.pos.zero(); return T;}
   Ball& set (Flt r, C Vec &pos=VecZero) {T.r=r; T.pos=pos   ; return T;}

#if EE_PRIVATE
   Ball& setAnimated(C Extent &ext, C Matrix           &matrix   ); // set ball from 'ext' animated by 'matrix'
#endif
   Ball& setAnimated(C Extent &ext, C AnimatedSkeleton &anim_skel); // set approximate ball encapsulating 'ext' animated by 'anim_skel' skeleton

   Ball& operator+=(C Vec     &v) {pos+=v; return T;}
   Ball& operator-=(C Vec     &v) {pos-=v; return T;}
   Ball& operator*=(  Flt      f);
   Ball& operator/=(  Flt      f);
   Ball& operator*=(C Matrix3 &m);
   Ball& operator/=(C Matrix3 &m);
   Ball& operator*=(C Matrix  &m);
   Ball& operator/=(C Matrix  &m);
   Ball& operator*=(C MatrixM &m);
   Ball& operator/=(C MatrixM &m);

   Ball& operator|=(C Vec  &v); // include 'v'
   Ball& operator|=(C Ball &b); // include 'b'

   friend Ball operator+ (C Ball &ball, C Vec     &v) {return Ball(ball)+=v;}
   friend Ball operator- (C Ball &ball, C Vec     &v) {return Ball(ball)-=v;}
   friend Ball operator* (C Ball &ball,   Flt      f) {return Ball(ball)*=f;}
   friend Ball operator/ (C Ball &ball,   Flt      f) {return Ball(ball)/=f;}
   friend Ball operator* (C Ball &ball, C Matrix3 &m) {return Ball(ball)*=m;}
   friend Ball operator/ (C Ball &ball, C Matrix3 &m) {return Ball(ball)/=m;}
   friend Ball operator* (C Ball &ball, C Matrix  &m) {return Ball(ball)*=m;}
   friend Ball operator/ (C Ball &ball, C Matrix  &m) {return Ball(ball)/=m;}

   // get
   Bool valid()C {return r>=0;} // if ball is valid, radius>=0

   Flt area  ()C {return (PI*4  )*Sqr (r);} // get surface area
   Flt volume()C {return (PI*4/3)*Cube(r);} // get volume

   Vec nearest(C Vec &normal)C; // get nearest point on ball towards normal

   Str asText()C {return S+"Radius: "+r+", Pos: "+pos;} // get text description

   // operations
   Ball& extend(Flt e) {r+=e; return T;} // extend

   void includeSafe(C Vec &v); // include 'v', but if 'r' is negative, then set to 'v'
   Bool from       (C Vec *point, Int points                  ); // set ball from an array of points                        , false on fail (if there are no points)
   Bool from       (C Vec *point, Int points, C Matrix &matrix); // set ball from an array of points transformed by 'matrix', false on fail (if there are no points)

   // draw
#if EE_PRIVATE
   void drawVI   (                                                   Bool fill=false, C VecI2 &resolution=VecI2(-1))C; // draw, this relies on active object matrix which can be set using 'SetMatrix' function
#endif
   void draw     (C Color &color=WHITE,                              Bool fill=false, C VecI2 &resolution=VecI2(-1))C; // draw                  , this relies on active object matrix which can be set using 'SetMatrix' function
   void drawAngle(C Color &color      , Flt from, Flt to, C Vec &up, Bool fill=false, C VecI2 &resolution=VecI2(-1))C; // draw with angle ranges, this relies on active object matrix which can be set using 'SetMatrix' function
   void draw2    (C Color &color=WHITE,                              Bool fill=false,   Int    resolution=      -1 )C; // draw box based        , this relies on active object matrix which can be set using 'SetMatrix' function

              Ball() {}
              Ball(Flt r, C Vec &pos=VecZero) {set(r, pos);}
   CONVERSION Ball(C BallM    &ball   );
   CONVERSION Ball(C Box      &box    );
   CONVERSION Ball(C OBox     &obox   );
   CONVERSION Ball(C Extent   &ext    );
   CONVERSION Ball(C Capsule  &capsule);
   CONVERSION Ball(C Shape    &shape  );
   CONVERSION Ball(C MeshBase &mesh   );
};
/******************************************************************************/
struct BallM // Ball Shape (mixed precision)
{
   Flt  r  ; // radius
   VecD pos; // center position

   Bool valid()C {return r>=0;} // if ball is valid, radius>=0

   BallM& zero(                  ) {T.r=0; T.pos.zero(); return T;}
   BallM& set (Flt r, C VecD &pos) {T.r=r; T.pos=pos   ; return T;}

   BallM& extend(Flt e) {r+=e; return T;} // extend

   BallM& setAnimated(C Extent &ext, C AnimatedSkeleton &anim_skel); // set approximate ball encapsulating 'ext' animated by 'anim_skel' skeleton

   BallM& operator+=(C VecD    &v) {pos+=v; return T;}
   BallM& operator-=(C VecD    &v) {pos-=v; return T;}
   BallM& operator*=(C MatrixM &m);
   BallM& operator/=(C MatrixM &m);

   friend BallM operator* (C Ball  &ball, C MatrixM &m) {return BallM(ball)*=m;}
   friend BallM operator/ (C Ball  &ball, C MatrixM &m) {return BallM(ball)/=m;}
   friend BallM operator* (C BallM &ball, C MatrixM &m) {return BallM(ball)*=m;}
   friend BallM operator/ (C BallM &ball, C MatrixM &m) {return BallM(ball)/=m;}

   // draw
   void draw(C Color &color=WHITE, Bool fill=false, C VecI2 &resolution=VecI2(-1))C; // draw, this relies on active object matrix which can be set using 'SetMatrix' function

              BallM() {}
              BallM(Flt r, C VecD &pos=VecDZero) {set(r, pos);}
   CONVERSION BallM(C Ball     &ball   );
   CONVERSION BallM(C CapsuleM &capsule);
};
/******************************************************************************/
struct BallD // Ball Shape (double precision)
{
   Dbl  r  ; // radius
   VecD pos; // center position

   Bool valid()C {return r>=0;} // if ball is valid, radius>=0

   BallD& zero(                  ) {T.r=0; T.pos.zero(); return T;}
   BallD& set (Dbl r, C VecD &pos) {T.r=r; T.pos=pos   ; return T;}

   BallD& extend(Dbl e) {r+=e; return T;} // extend

   BallD() {}
   BallD(Dbl r, C VecD &pos=VecDZero) {set(r, pos);}
};
/******************************************************************************/
struct SphereArea : VecI2
{
   DIR_ENUM side;

   VecI2& xy()  {return T;}
 C VecI2& xy()C {return T;}

   SphereArea& zero(                           ) {T.side=DIR_ENUM(0); T.x=0; T.y=0; return T;}
   SphereArea& set (DIR_ENUM side, Int x, Int y) {T.side=side       ; T.x=x; T.y=y; return T;}

   Bool operator==(C SphereArea   &pos)C {return xy()==pos.xy() && side==pos.side;}
   Bool operator!=(C SphereArea   &pos)C {return xy()!=pos.xy() || side!=pos.side;}
   Bool operator==(C SphereAreaUS &pos)C;
   Bool operator!=(C SphereAreaUS &pos)C;

   SphereArea() {}
   SphereArea(DIR_ENUM side, Int x, Int y) {set(side, x, y);}
   SphereArea(C SphereAreaUS &pos        );
};
struct SphereAreaUS : VecUS2
{
   DIR_ENUM side;

   VecUS2& xy()  {return T;}
 C VecUS2& xy()C {return T;}

   SphereAreaUS& zero(                                 ) {T.side=DIR_ENUM(0); T.x=0; T.y=0; return T;}
   SphereAreaUS& set (DIR_ENUM side, UShort x, UShort y) {T.side=side       ; T.x=x; T.y=y; return T;}

   Bool operator==(C SphereAreaUS &pos)C {return xy()==pos.xy() && side==pos.side;}
   Bool operator!=(C SphereAreaUS &pos)C {return xy()!=pos.xy() || side!=pos.side;}
   Bool operator==(C SphereArea   &pos)C {return xy()==pos.xy() && side==pos.side;}
   Bool operator!=(C SphereArea   &pos)C {return xy()!=pos.xy() || side!=pos.side;}

   SphereAreaUS() {}
   SphereAreaUS(DIR_ENUM side, UShort x, UShort y) {set(    side,     x,     y);}
   SphereAreaUS(C SphereArea &pos                ) {set(pos.side, pos.x, pos.y);}
};
inline      SphereArea::SphereArea(C SphereAreaUS &pos)  {set(pos.side, pos.x, pos.y);}
inline Bool SphereArea::operator==(C SphereAreaUS &pos)C {return xy()==pos.xy() && side==pos.side;}
inline Bool SphereArea::operator!=(C SphereAreaUS &pos)C {return xy()!=pos.xy() || side!=pos.side;}
#if EE_PRIVATE
struct SphereAreaDist : SphereArea
{
   Flt dist;
};
struct SphereAreaUSDist : SphereAreaUS
{
   Flt dist;
};
inline Int Compare (C SphereAreaDist   &a, C SphereAreaDist   &b) {return Compare(a.dist, b.dist);}
inline Int CompareR(C SphereAreaDist   &a, C SphereAreaDist   &b) {return Compare(b.dist, a.dist);}
inline Int Compare (C SphereAreaUSDist &a, C SphereAreaUSDist &b) {return Compare(a.dist, b.dist);}
inline Int CompareR(C SphereAreaUSDist &a, C SphereAreaUSDist &b) {return Compare(b.dist, a.dist);}
#endif
/******************************************************************************/
struct SphereConvert
{
   Int       res;
   Flt       pos_to_cell_mul, pos_to_cell_add, cell_to_pos_mul/*, cell_to_pos_add=-PI_4*/;
   Mems<Flt> tans;

   void init(Int res);
   void del ();

   Flt   posToCell    (  Flt   pos)C {return Atan(pos)*pos_to_cell_mul+pos_to_cell_add;}
   Int   posToCellI   (  Flt   pos)C {return     Floor(posToCell(pos));}
   Int   posToCellIMid(  Flt   pos)C {return Mid(Trunc(posToCell(pos)), 0, res-1);}
   Vec2  posToCell    (C Vec2 &pos)C {return Vec2 (posToCell    (pos.x), posToCell    (pos.y));}
   VecI2 posToCellI   (C Vec2 &pos)C {return VecI2(posToCellI   (pos.x), posToCellI   (pos.y));}
   VecI2 posToCellIMid(C Vec2 &pos)C {return VecI2(posToCellIMid(pos.x), posToCellIMid(pos.y));}

   Flt   cellToPos(  Flt    cell)C {return Tan (cell*cell_to_pos_mul+(-PI_4));}
   Flt   cellToPos(  Int    cell)C {return Tan (cell*cell_to_pos_mul+(-PI_4));}
   Flt  _cellToPos(  Int    cell)C {return tans[cell]                                  ;} // !! 'cell' MUST BE IN RANGE "0..res" !!
   Vec2  cellToPos(C Vec2  &cell)C {return Vec2( cellToPos(cell.x),  cellToPos(cell.y));}
   Vec2  cellToPos(C VecI2 &cell)C {return Vec2( cellToPos(cell.x),  cellToPos(cell.y));}
   Vec2 _cellToPos(C VecI2 &cell)C {return Vec2(_cellToPos(cell.x), _cellToPos(cell.y));} // !! 'cell' MUST BE IN RANGE "0..res" !!

   Vec _cellNrmLeft (Int cell)C {return Vec(-1,  0,  _cellToPos(cell));} // get cell left  normal, it's not normalized !! 'cell' MUST BE IN RANGE "0..res" !!
   Vec _cellNrmRight(Int cell)C {return Vec( 1,  0, -_cellToPos(cell));} // get cell right normal, it's not normalized !! 'cell' MUST BE IN RANGE "0..res" !!
   Vec _cellNrmDown (Int cell)C {return Vec( 0, -1,  _cellToPos(cell));} // get cell down  normal, it's not normalized !! 'cell' MUST BE IN RANGE "0..res" !!
   Vec _cellNrmUp   (Int cell)C {return Vec( 0,  1, -_cellToPos(cell));} // get cell up    normal, it's not normalized !! 'cell' MUST BE IN RANGE "0..res" !!

   DIR_ENUM dirToSphereGroundPixel    (C Vec &dir, Vec2   &xy        )C; // convert vector direction (doesn't need to be normalized) to cube face and spherical ground coordinates, 'xy'=image pixel coordinates (0..res  )
   DIR_ENUM dirToSphereGroundPixelI   (C Vec &dir, VecI2  &xy        )C; // convert vector direction (doesn't need to be normalized) to cube face and spherical ground coordinates, 'xy'=image pixel coordinates (0..res  )
   DIR_ENUM dirToSphereGroundPixelIMid(C Vec &dir, VecI2  &xy        )C; // convert vector direction (doesn't need to be normalized) to cube face and spherical ground coordinates, 'xy'=image pixel coordinates (0..res-1)
   DIR_ENUM dirToSphereGroundPixelIMid(C Vec &dir, VecUS2 &xy        )C; // convert vector direction (doesn't need to be normalized) to cube face and spherical ground coordinates, 'xy'=image pixel coordinates (0..res-1)
   Vec2     dirToSphereGroundPixel    (C Vec &dir, DIR_ENUM cube_face)C; // convert vector direction (doesn't need to be normalized) to               spherical ground coordinates, 'cube_face'=cube face that 'dir' belongs to, returns image pixel coordinates (0..res)
   VecI2    dirToSphereGroundPixelI   (C Vec &dir, DIR_ENUM cube_face)C; // convert vector direction (doesn't need to be normalized) to               spherical ground coordinates, 'cube_face'=cube face that 'dir' belongs to, returns image pixel coordinates (0..res)

   Vec   sphereGroundPixelToDir      (            DIR_ENUM cube_face, Flt x, Flt y)C; // convert spherical ground coordinates to vector direction, 'cube_face'=ground cube face, 'x,y'=ground pixel coordinates (0..res  ), returned vector is not normalized, however it's on a cube with radius=1 ("Abs(dir).max()=1")
   Vec  _sphereGroundPixelToDir      (            DIR_ENUM cube_face, Int x, Int y)C; // convert spherical ground coordinates to vector direction, 'cube_face'=ground cube face, 'x,y'=ground pixel coordinates (0..res  ), returned vector is not normalized, however it's on a cube with radius=1 ("Abs(dir).max()=1"), !! 'x' 'y' MUST BE IN RANGE "0..res"   !!
   Vec  _sphereGroundPixelCenterToDir(            DIR_ENUM cube_face, Int x, Int y)C; // convert spherical ground coordinates to vector direction, 'cube_face'=ground cube face, 'x,y'=ground pixel coordinates (0..res-1), returned vector is not normalized, however it's on a cube with radius=1 ("Abs(dir).max()=1"), !! 'x' 'y' MUST BE IN RANGE "0..res-1" !! THIS IS FAST APPROXIMATION !!
   void _sphereGroundPixelToQuad     (Quad &quad, DIR_ENUM cube_face, Int x, Int y)C; // convert spherical ground coordinates to quad            , 'cube_face'=ground cube face, 'x,y'=ground pixel coordinates (0..res-1), returned quad   is not normalized, however it's on a cube with radius=1 ("Abs(pos).max()=1"), !! 'x' 'y' MUST BE IN RANGE "0..res-1" !!

   void getIntersectingAreas      (MemPtr<SphereArea> area_pos, C Ball &ball, Flt min_height)C;
   void getIntersectingAreas      (MemPtr<SphereArea> area_pos, C Vec  &dir , Flt angle     )C; // get areas        around 'dir' up to 'angle' !! 'dir' MUST BE NORMALIZED !!
   void getIntersectingAreaOrigins(MemPtr<SphereArea> area_pos, C Vec  &dir , Flt angle     )C; // get area origins around 'dir' up to 'angle' !! 'dir' MUST BE NORMALIZED !!
   Bool    intersects             (     C SphereArea &area_pos, C Ball &ball, Flt min_height)C; // !! 'area_pos.xy' MUST BE IN RANGE "0..res-1" !!

#if EE_PRIVATE
   void draw()C;
   void drawCell(C Color &color, C VecI2 &cell)C;
#endif
   void drawCell(C Color &color, C SphereArea &area, Flt radius)C;
};
struct SphereConvertEx : SphereConvert
{
   Mems<Flt> tan_mids;

   Flt  _cellCenterToPos(  Int    cell)C {return tan_mids[cell]                              ;} // !! 'cell' MUST BE IN RANGE "0..res-1" !!
   Vec2 _cellCenterToPos(C VecI2 &cell)C {return Vec2(_cellToPos(cell.x), _cellToPos(cell.y));} // !! 'cell' MUST BE IN RANGE "0..res-1" !!

   void init(Int res);
   void del ();

   Vec _sphereGroundPixelCenterToDir(DIR_ENUM cube_face, Int x, Int y)C; // convert spherical ground coordinates to vector direction, 'cube_face'=ground cube face, 'x,y'=ground pixel coordinates (0..res-1), returned vector is not normalized, however it's on a cube with radius=1 ("Abs(dir).max()=1"), !! 'x' 'y' MUST BE IN RANGE "0..res-1" !!

   Flt sortCompareValue(C SphereArea   &area, C Vec &pos)C; // get value for sort compare, that sorts areas based on distance to 'pos'
   Flt sortCompareValue(C SphereAreaUS &area, C Vec &pos)C; // get value for sort compare, that sorts areas based on distance to 'pos'

   void sort(MemPtr<SphereArea  > areas, C Vec &pos, Bool reverse=false)C; // sort 'areas' based on distance to 'pos', 'reverse'=if reverse sort order
   void sort(MemPtr<SphereAreaUS> areas, C Vec &pos, Bool reverse=false)C; // sort 'areas' based on distance to 'pos', 'reverse'=if reverse sort order

   void getIntersectingAreas      (MemPtr<SphereArea> area_pos, C Ball &ball, Flt min_height)C {return super::getIntersectingAreas(area_pos, ball, min_height);}
   void getIntersectingAreas      (MemPtr<SphereArea> area_pos, C Vec  &dir , Flt angle     )C {return super::getIntersectingAreas(area_pos, dir , angle     );} // get areas around 'dir' up to 'angle' !! 'dir' MUST BE NORMALIZED !!
   void getIntersectingAreas      (MemPtr<SphereArea> area_pos, C VecD *point, Int points, C VecI2 *edge, Int edges, C BallM *distance_check, C Vec *sort_by_distance, Bool extend, Flt min_height)C; // get 'area_pos' coordinates of areas intersecting with 'points' and 'edges', 'distance_check'=list only areas within ball (optional), 'sort_by_distance'=if sort areas by distance along this direction vector (optional, doesn't need to be normalized), 'extend'=if extend coverage by half of area size, 'min_height'=assume that area data is located only above this distance from center of sphere
   void getIntersectingAreaCenters(MemPtr<SphereArea> area_pos, C Vec &dir, Flt angle)C; // get area centers around 'dir' up to 'angle' !! 'dir' MUST BE NORMALIZED !!
};
/******************************************************************************/
DIR_ENUM DirToCubeFace               (C Vec &dir                   ); // convert vector direction (doesn't need to be normalized) to cube face
DIR_ENUM DirToCubeFacePixel          (C Vec &dir, Int res, Vec2 &xy); // convert vector direction (doesn't need to be normalized) to           cube face and image  coordinates, 'res'=cube image resolution, 'xy'=image pixel coordinates (0..res-1)
DIR_ENUM DirToSphereCubeFacePixel    (C Vec &dir, Int res, Vec2 &xy); // convert vector direction (doesn't need to be normalized) to spherical cube face and image  coordinates, 'res'=cube image resolution, 'xy'=image pixel coordinates (0..res-1)
DIR_ENUM DirToSphereGroundPixel      (C Vec &dir, Int res, Vec2 &xy); // convert vector direction (doesn't need to be normalized) to spherical cube face and ground coordinates, 'res'=ground     resolution, 'xy'=image pixel coordinates (0..res  )
DIR_ENUM DirToSphereGroundPixelCenter(C Vec &dir, Int res, Vec2 &xy); // convert vector direction (doesn't need to be normalized) to spherical cube face and ground coordinates, 'res'=ground     resolution, 'xy'=image pixel coordinates (0..res-1)

Vec       CubeFacePosToDir      (DIR_ENUM cube_face, C Vec2 &xy           ); // convert           cube image position    to vector direction, 'cube_face'=image  cube face, 'xy' =image  position          (-1..1   ) on plane Z=1                , returned vector is not normalized, however it's on a cube with radius=1 ("Abs(dir).max()=1")
Vec       CubeFacePixelToDir    (DIR_ENUM cube_face, Flt x, Flt y, Int res); // convert           cube image coordinates to vector direction, 'cube_face'=image  cube face, 'x,y'=image  pixel coordinates (0..res-1), 'res'=cube image resolution, returned vector is not normalized, however it's on a cube with radius=1 ("Abs(dir).max()=1")
Vec SphereCubeFacePixelToDir    (DIR_ENUM cube_face, Flt x, Flt y, Int res); // convert spherical cube image coordinates to vector direction, 'cube_face'=image  cube face, 'x,y'=image  pixel coordinates (0..res-1), 'res'=cube image resolution, returned vector is not normalized, however it's on a cube with radius=1 ("Abs(dir).max()=1")
Vec       GroundPosToDir        (DIR_ENUM cube_face, C Vec2 &xy           ); // convert           ground     position    to vector direction, 'cube_face'=ground cube face, 'xy' =ground position          (-1..1   ) on plane Z=1                , returned vector is not normalized, however it's on a cube with radius=1 ("Abs(dir).max()=1")
Vec SphereGroundPixelToDir      (DIR_ENUM cube_face, Flt x, Flt y, Int res); // convert spherical ground     coordinates to vector direction, 'cube_face'=ground cube face, 'x,y'=ground pixel coordinates (0..res  ), 'res'=ground     resolution, returned vector is not normalized, however it's on a cube with radius=1 ("Abs(dir).max()=1")
Vec SphereGroundPixelCenterToDir(DIR_ENUM cube_face, Flt x, Flt y, Int res); // convert spherical ground     coordinates to vector direction, 'cube_face'=ground cube face, 'x,y'=ground pixel coordinates (0..res-1), 'res'=ground     resolution, returned vector is not normalized, however it's on a cube with radius=1 ("Abs(dir).max()=1")

void CubeFacePosToPos(DIR_ENUM cube_face, Vec  &dest, C Vec  &src          ); // convert 'cube_face'        position 'src' where XY=plane position, Z=height to world space        position 'dest'
void PosToCubeFacePos(DIR_ENUM cube_face, Vec  &dest, C Vec  &src          ); // convert world space        position 'src'                                   to 'cube_face'        position 'dest' where XY=plane position, Z=height
void GroundPosToPos  (DIR_ENUM cube_face, Vec  &dest, C Vec  &src          ); // convert 'cube_face' ground position 'src' where XY=plane position, Z=height to world space        position 'dest'
void PosToGroundPos  (DIR_ENUM cube_face, Vec2 &dest, C Vec  &src          ); // convert world space        position 'src'                                   to 'cube_face' ground position 'dest' where XY=plane position
void PosToGroundPos  (DIR_ENUM cube_face, Vec  &dest, C Vec  &src          ); // convert world space        position 'src'                                   to 'cube_face' ground position 'dest' where XY=plane position, Z=height
void PosToGroundPos  (DIR_ENUM cube_face, Edge &dest, C Edge &src          ); // convert world space        position 'src'                                   to 'cube_face' ground position 'dest' where XY=plane position, Z=height
void PosToGroundPos  (DIR_ENUM cube_face, VecD *dest, C VecD *src, Int elms); // convert world space        position 'src'                                   to 'cube_face' ground position 'dest' where XY=plane position, Z=height

void TransformByGroundOrient(DIR_ENUM cube_face, Vec &dest, C Vec &src); // convert             ground vector 'src' to 'cube_face' ground vector 'dest', same as "dest=src*Matrix3().setGroundOrient(cube_face)" but faster
void    DivideByGroundOrient(DIR_ENUM cube_face, Vec &dest, C Vec &src); // convert 'cube_face' ground vector 'src' to             ground vector 'dest', same as "dest=src/Matrix3().setGroundOrient(cube_face)" but faster

void WrapCubeFacePixel          (SphereArea &dest, C SphereArea &src, Int res); // wrap 'src' pixel to be in 0..res-1 range and store in 'dest'
void WrapSphereGroundPixel      (SphereArea &dest, C SphereArea &src, Int res); // wrap 'src' pixel to be in 0..res   range and store in 'dest'
void WrapSphereGroundPixelCenter(SphereArea &dest, C SphereArea &src, Int res); // wrap 'src' pixel to be in 0..res-1 range and store in 'dest'

Bool ClipToGroundAndProject(DIR_ENUM cube_face, Edge2 &dest, C Edge &src, Flt min_z); // convert 'src' edge to 'cube_face' ground, clip Z with min_z and project to 'dest', returns false if fully clipped

#if EE_PRIVATE
INLINE Vec _GroundPosToDir(DIR_ENUM cube_face, Flt x, Flt y) // same as 'PosToGroundPos' with src.z=1
{
   switch(cube_face) // #GroundOrient
   {
      case DIR_RIGHT  : return Vec( 1,  y,  x);
      case DIR_LEFT   : return Vec(-1,  y, -x);
      case DIR_UP     : return Vec( x,  1,  y);
      case DIR_DOWN   : return Vec( x, -1, -y);
      case DIR_FORWARD: return Vec(-x,  y,  1);
      case DIR_BACK   : return Vec( x,  y, -1);
   }
   return VecZero;
}
#endif
/******************************************************************************/
Ball Avg(C Ball &a, C Ball &b);

// distance
Flt Dist(C Vec    &point, C Ball  &ball); // distance between point    and a ball
Dbl Dist(C VecD   &point, C BallM &ball); // distance between point    and a ball
Flt Dist(C Edge   &edge , C Ball  &ball); // distance between edge     and a ball
Flt Dist(C TriN   &tri  , C Ball  &ball); // distance between triangle and a ball
Flt Dist(C Box    &box  , C Ball  &ball); // distance between box      and a ball
Flt Dist(C OBox   &obox , C Ball  &ball); // distance between box      and a ball
Flt Dist(C Extent &ext  , C Ball  &ball); // distance between extent   and a ball
Flt Dist(C Ball   &a    , C Ball  &b   ); // distance between ball     and a ball

Flt DistBallPlane(C Ball  &ball, C Vec  &plane_pos, C Vec &plane_normal); // distance between ball and a plane
Dbl DistBallPlane(C Ball  &ball, C VecD &plane_pos, C Vec &plane_normal); // distance between ball and a plane
Dbl DistBallPlane(C BallM &ball, C VecD &plane_pos, C Vec &plane_normal); // distance between ball and a plane

// distance between ball and a plane using 'ray' movement directions ('ray' must be normalized but 'plane_normal' doesn't have to be)
Flt DistBallPlaneRay(C Ball &ball, C Vec &plane_pos, C Vec &plane_normal, C Vec &ray);

inline Flt Dist(C Ball  &ball, C Plane  &plane) {return DistBallPlane(ball, plane.pos, plane.normal);} // distance between ball and a plane
inline Dbl Dist(C Ball  &ball, C PlaneM &plane) {return DistBallPlane(ball, plane.pos, plane.normal);} // distance between ball and a plane
inline Dbl Dist(C BallM &ball, C PlaneM &plane) {return DistBallPlane(ball, plane.pos, plane.normal);} // distance between ball and a plane

// cuts
Bool Cuts(C Vec    &point, C Ball  &ball); // if point    cuts a ball
Bool Cuts(C VecD   &point, C Ball  &ball); // if point    cuts a ball
Bool Cuts(C VecD   &point, C BallM &ball); // if point    cuts a ball
Bool Cuts(C Edge   &edge , C Ball  &ball); // if edge     cuts a ball
Bool Cuts(C Tri    &tri  , C Ball  &ball); // if triangle cuts a ball
Bool Cuts(C TriN   &tri  , C Ball  &ball); // if triangle cuts a ball
Bool Cuts(C Box    &box  , C Ball  &ball); // if box      cuts a ball
Bool Cuts(C OBox   &obox , C Ball  &ball); // if box      cuts a ball
Bool Cuts(C Extent &ext  , C Ball  &ball); // if extent   cuts a ball
Bool Cuts(C Extent &ext  , C BallM &ball); // if extent   cuts a ball
Bool Cuts(C Ball   &a    , C Ball  &b   ); // if ball     cuts a ball
Bool Cuts(C Ball   &a    , C BallM &b   ); // if ball     cuts a ball
Bool Cuts(C BallM  &a    , C BallM &b   ); // if ball     cuts a ball

Bool Cuts(C Ball &a, C Ball &b, Bool &fully_inside); // if ball cuts a ball, 'fully_inside'=if 'a' is fully inside 'b' (this is set only if function returns true, if false then this value is not changed)

Int CutsLineBall(C Vec  &line_pos  , C Vec  &line_dir, C Ball  &ball, Vec  *contact_a=null, Vec  *contact_b=null); // if infinite straight line cuts a ball, return number of contacts, 'line_dir'=straight line direction (must be normalized)
Int CutsLineBall(C VecD &line_pos  , C VecD &line_dir, C BallM &ball, VecD *contact_a=null, VecD *contact_b=null); // if infinite straight line cuts a ball, return number of contacts, 'line_dir'=straight line direction (must be normalized)
Int CutsEdgeBall(C Vec  &edge_start, C Vec  &edge_end, C Ball  &ball, Vec  *contact_a=null, Vec  *contact_b=null); // if edge                   cuts a ball, return number of contacts

Bool Inside(C Ball   &a, C Ball &b); // if 'a' is fully inside 'b'
Bool Inside(C Box    &a, C Ball &b); // if 'a' is fully inside 'b'
Bool Inside(C Extent &a, C Ball &b); // if 'a' is fully inside 'b'

// sweep
Bool SweepPointBall(C Vec  &point, C Vec  &move, C Ball  &ball, Flt *hit_frac=null, Vec  *hit_normal=null); // if moving point cuts through a static ball
Bool SweepPointBall(C VecD &point, C Vec  &move, C BallM &ball, Flt *hit_frac=null, Vec  *hit_normal=null); // if moving point cuts through a static ball
Bool SweepPointBall(C VecD &point, C VecD &move, C BallD &ball, Dbl *hit_frac=null, VecD *hit_normal=null); // if moving point cuts through a static ball
Bool SweepEdgeBall (C Edge  &edge, C Vec  &move, C Ball  &ball, Flt *hit_frac=null, Vec  *hit_normal=null); // if moving edge  cuts through a static ball
Bool SweepEdgeBall (C EdgeD &edge, C VecD &move, C BallD &ball, Dbl *hit_frac=null, VecD *hit_normal=null); // if moving edge  cuts through a static ball

Bool SweepBallPoint(C Ball  &ball, C Vec  &move, C Vec   &point, Flt *hit_frac=null, Vec  *hit_normal=null); // if moving ball cuts through a static point
Bool SweepBallPoint(C BallM &ball, C Vec  &move, C VecD  &point, Flt *hit_frac=null, Vec  *hit_normal=null); // if moving ball cuts through a static point
Bool SweepBallPoint(C BallD &ball, C VecD &move, C VecD  &point, Dbl *hit_frac=null, VecD *hit_normal=null); // if moving ball cuts through a static point
Bool SweepBallEdge (C Ball  &ball, C Vec  &move, C Edge  &edge , Flt *hit_frac=null, Vec  *hit_normal=null); // if moving ball cuts through a static edge
Bool SweepBallEdge (C BallM &ball, C Vec  &move, C EdgeD &edge , Flt *hit_frac=null, Vec  *hit_normal=null); // if moving ball cuts through a static edge
Bool SweepBallEdge (C BallD &ball, C VecD &move, C EdgeD &edge , Dbl *hit_frac=null, VecD *hit_normal=null); // if moving ball cuts through a static edge
Bool SweepBallBall (C Ball  &ball, C Vec  &move, C Ball  &ball2, Flt *hit_frac=null, Vec  *hit_normal=null); // if moving ball cuts through a static ball
Bool SweepBallBall (C BallD &ball, C VecD &move, C BallD &ball2, Dbl *hit_frac=null, VecD *hit_normal=null); // if moving ball cuts through a static ball

// surface travel
Vec BallSurfaceTravelAngular(C Vec &pos, C Vec &dir, Flt dist); // angular travel along ball surface (ball surface position='pos', ball center=zero, ball radius=pos.length) towards 'dir' (doesn't need to be normalized or aligned on surface normal), 'dist'=travelled distance, returns position on ball surface. Angular distance between 'pos' and returned position will be 'dist'.
Vec BallSurfaceTravelLinear (C Vec &pos, C Vec &dir, Flt dist); // linear  travel along ball surface (ball surface position='pos', ball center=zero, ball radius=pos.length) towards 'dir' (doesn't need to be normalized or aligned on surface normal), 'dist'=travelled distance, returns position on ball surface. Linear  distance between 'pos' and returned position will be 'dist'.

#if EE_PRIVATE
Bool ClipZ(Ball &ball, Flt min_z); // clip ball to retain information only above 'min_z'
#endif
/******************************************************************************/
// SPHERE / CUBE
Int CubePoints(Int res); // get number of unique points on Sphere / Cube

Vec  IndexToSphereCubePos(                   Int i, Int res); // convert point index to vector direction, returned vector is not normalized, however it's on a cube with radius=1 ("Abs(dir).max()=1")
void IndexToCubePos      (  SphereArea &pos, Int i, Int res); // convert point index to coordinates
Int  CubePosToIndex      (C SphereArea &pos,        Int res); // convert coordinates to point index

inline Int CubeQuads(             Int res) {return Sqr(res)*6;} // get number of quads for Sphere / Cube with 'res' resolution
   void SetCubeQuads(VecI4 *quad, Int res); // 'quad'=array of quads to set, it must be big enough to contain "CubeQuads(res)" elements
/******************************************************************************/
