/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************/
enum SEL_FLAG // Selection Flag
{
   SEL_A =0x1, // if A  present
   SEL_B =0x2, // if B  present
   SEL_AB=0x4, // if AB present

   SEL_OR  =SEL_A|SEL_B|SEL_AB, // A|B
   SEL_XOR =SEL_A|SEL_B       , // A^B
   SEL_AND =            SEL_AB, // A&B
   SEL_ADD =SEL_A|SEL_B|SEL_AB, // A+B
   SEL_SUB =SEL_A             , // A-B
   SEL_SUBR=      SEL_B       , // B-A
   SEL_MUL =            SEL_AB, // A*B
};
/******************************************************************************/
void Csg(MeshBase &a, C MeshBase &b, UInt sel, MeshBase *dest=null, Bool detect_self_intersections=false, Flt weld_pos_eps=0.0001f); // perform a CSG operation on 'a b' meshes, 'sel'=SEL_FLAG, 'dest'=output mesh (if set to null then it will be set to 'a'), 'detect_self_intersections'=if detect self intestections between 'a' mesh faces, and self intersections between 'b' mesh faces (this will make Csg perform slower but correctly handle situations where 'a' mesh faces intersect each other or 'b' mesh faces intersect each other), 'weld_pos_eps'=epsilon used for final vertex position welding, if you're getting incorrect results you can try calling first 'removeDegenerateFaces' on meshes
void Csg(MeshLod  &a, C MeshLod  &b, UInt sel, MeshLod  *dest=null, Bool detect_self_intersections=false, Flt weld_pos_eps=0.0001f); // perform a CSG operation on 'a b' meshes, 'sel'=SEL_FLAG, 'dest'=output mesh (if set to null then it will be set to 'a'), 'detect_self_intersections'=if detect self intestections between 'a' mesh faces, and self intersections between 'b' mesh faces (this will make Csg perform slower but correctly handle situations where 'a' mesh faces intersect each other or 'b' mesh faces intersect each other), 'weld_pos_eps'=epsilon used for final vertex position welding, if you're getting incorrect results you can try calling first 'removeDegenerateFaces' on meshes

void  ClipMesh     (C MeshBase &src, C Matrix *matrix, MeshBase &dest         ,                      C Plane *clip_plane, Int clip_planes,                          MESH_FLAG flag_and=MESH_ALL, Flt weld_pos_eps=EPS); // generate 'src' mesh transformed by 'matrix' and then clipped by 'clip_planes' (if the 'matrix' is null then the mesh is not transformed), result is stored in 'dest'                             , 'weld_pos_eps'=epsilon used for final vertex position welding, 'flag_and'=elements to include in 'dest'   creation
void  ClipMesh     (C MeshLod  &src, C Matrix *matrix, MeshLod  &dest         ,                      C Plane *clip_plane, Int clip_planes,                          MESH_FLAG flag_and=MESH_ALL, Flt weld_pos_eps=EPS); // generate 'src' mesh transformed by 'matrix' and then clipped by 'clip_planes' (if the 'matrix' is null then the mesh is not transformed), result is stored in 'dest'                             , 'weld_pos_eps'=epsilon used for final vertex position welding, 'flag_and'=elements to include in 'dest'   creation
void  ClipMesh     (C Mesh     &src, C Matrix *matrix, Mesh     &dest         ,                      C Plane *clip_plane, Int clip_planes,                          MESH_FLAG flag_and=MESH_ALL, Flt weld_pos_eps=EPS); // generate 'src' mesh transformed by 'matrix' and then clipped by 'clip_planes' (if the 'matrix' is null then the mesh is not transformed), result is stored in 'dest'                             , 'weld_pos_eps'=epsilon used for final vertex position welding, 'flag_and'=elements to include in 'dest'   creation
void SplitMesh     (C Mesh     &src, C Matrix *matrix, Mesh     &dest_positive, Mesh &dest_negative, C Plane &clip_plane,                                           MESH_FLAG flag_and=MESH_ALL, Flt weld_pos_eps=EPS); // generate 'src' mesh transformed by 'matrix' and then split   by 'clip_plane'  (if the 'matrix' is null then the mesh is not transformed), result is stored in 'dest_positive' and 'dest_negative', 'weld_pos_eps'=epsilon used for final vertex position welding, 'flag_and'=elements to include in 'dest_*' creation
void SplitMeshSolid(C Mesh     &src, C Matrix *matrix, Mesh     &dest_positive, Mesh &dest_negative, C Plane &clip_plane, C MaterialPtr &material, Flt tex_scale=1, MESH_FLAG flag_and=MESH_ALL, Flt weld_pos_eps=EPS); // generate 'src' mesh transformed by 'matrix' and then split   by 'clip_plane'  (if the 'matrix' is null then the mesh is not transformed), result is stored in 'dest_positive' and 'dest_negative', 'weld_pos_eps'=epsilon used for final vertex position welding, 'flag_and'=elements to include in 'dest_*' creation, 'material'=material used to fill the "solid inside" created because of the splitting, 'tex_scale'=texture coordinates scale of the "solid inside" part
/******************************************************************************/
