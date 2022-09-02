/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************

   In following functions 'hit_face' can indicate a triangle or a quad index
   If it's a quad then 'hit_face' has XOR'ed SIGN_BIT into its value
   Determining triangle or quad looks like this:

   if(hit_face&SIGN_BIT)quad_index=hit_face^SIGN_BIT; // it's a quad
   else                  tri_index=hit_face         ; // it's a triangle

/******************************************************************************/
// if moving 3D point cuts through a static mesh, if mesh is transformed pass its matrix to 'mesh_matrix', 'hit_frac'=0..1, 'hit_pos'=hit position, 'hit_face'=index of hit face, if you're sure that quads are fully valid (their triangles are coplanar) set 'test_quads_as_2_tris'=false for performance boost
Bool Sweep(C Vec  &point, C Vec  &move, C MeshBase   &mshb, C Matrix  *mesh_matrix=null, Flt *hit_frac=null, Vec  *hit_pos=null, Int *hit_face=null                                        , Bool test_quads_as_2_tris=true, Bool two_sided=false                     ); //                                                                 'two_sided'=if mesh faces are two-sided
Bool Sweep(C Vec  &point, C Vec  &move, C MeshRender &mshr, C Matrix  *mesh_matrix=null, Flt *hit_frac=null, Vec  *hit_pos=null, Int *hit_face=null                                                                        , Bool two_sided=false                     ); //                                                                 'two_sided'=if mesh faces are two-sided
Bool Sweep(C Vec  &point, C Vec  &move, C MeshPart   &part, C Matrix  *mesh_matrix=null, Flt *hit_frac=null, Vec  *hit_pos=null, Int *hit_face=null                                        , Bool test_quads_as_2_tris=true, Int  two_sided=-1, Bool only_visible=true); //                                                               , 'two_sided'=if mesh faces are two-sided (use -1 to set according to material cull), 'only_visible'=if process only visible mesh parts
Bool Sweep(C Vec  &point, C Vec  &move, C MeshLod    &mesh, C Matrix  *mesh_matrix=null, Flt *hit_frac=null, Vec  *hit_pos=null, Int *hit_face=null, Int *hit_part=null                    , Bool test_quads_as_2_tris=true, Int  two_sided=-1, Bool only_visible=true); // 'hit_part'=index of hit MeshPart                              , 'two_sided'=if mesh faces are two-sided (use -1 to set according to material cull), 'only_visible'=if process only visible mesh parts
Bool Sweep(C Vec  &point, C Vec  &move, C Mesh       &mesh, C Matrix  *mesh_matrix=null, Flt *hit_frac=null, Vec  *hit_pos=null, Int *hit_face=null, Int *hit_part=null                    , Bool test_quads_as_2_tris=true, Int  two_sided=-1, Bool only_visible=true); // 'hit_part'=index of hit MeshPart                              , 'two_sided'=if mesh faces are two-sided (use -1 to set according to material cull), 'only_visible'=if process only visible mesh parts
Bool Sweep(C VecD &point, C VecD &move, C Mesh       &mesh, C MatrixM *mesh_matrix=null, Flt *hit_frac=null, VecD *hit_pos=null, Int *hit_face=null, Int *hit_part=null                    , Bool test_quads_as_2_tris=true, Int  two_sided=-1, Bool only_visible=true); // 'hit_part'=index of hit MeshPart                              , 'two_sided'=if mesh faces are two-sided (use -1 to set according to material cull), 'only_visible'=if process only visible mesh parts
Bool Sweep(C Vec  &point, C Vec  &move, C MeshGroup  &mshg, C Matrix  *mesh_matrix=null, Flt *hit_frac=null, Vec  *hit_pos=null, Int *hit_face=null, Int *hit_part=null, Int *hit_mesh=null, Bool test_quads_as_2_tris=true, Int  two_sided=-1, Bool only_visible=true); // 'hit_part'=index of hit MeshPart, 'hit_mesh'=index of hit Mesh, 'two_sided'=if mesh faces are two-sided (use -1 to set according to material cull), 'only_visible'=if process only visible mesh parts
/******************************************************************************/
// raycast left from (+Inf, point.y, point.z) ('point.x' is ignored), return if hit, 'hit_pos'=hit position, 'hit_face'=index of hit face, if you're sure that quads are fully valid (their triangles are coplanar) set 'test_quads_as_2_tris'=false for performance boost
Bool PosPointMeshXL(C Vec &point, C MeshBase  &mshb, Vec *hit_pos=null, Int *hit_face=null,                                         Bool test_quads_as_2_tris=true);
Bool PosPointMeshXL(C Vec &point, C Mesh      &mesh, Vec *hit_pos=null, Int *hit_face=null, Int *hit_part=null                    , Bool test_quads_as_2_tris=true); // 'hit_part'=index of hit MeshPart
Bool PosPointMeshXL(C Vec &point, C MeshGroup &mshg, Vec *hit_pos=null, Int *hit_face=null, Int *hit_part=null, Int *hit_mesh=null, Bool test_quads_as_2_tris=true); // 'hit_part'=index of hit MeshPart, 'hit_mesh'=index of hit Mesh

// raycast right from (-Inf, point.y, point.z) ('point.x' is ignored), return if hit, 'hit_pos'=hit position, 'hit_face'=index of hit face, if you're sure that quads are fully valid (their triangles are coplanar) set 'test_quads_as_2_tris'=false for performance boost
Bool PosPointMeshXR(C Vec &point, C MeshBase  &mshb, Vec *hit_pos=null, Int *hit_face=null,                                         Bool test_quads_as_2_tris=true);
Bool PosPointMeshXR(C Vec &point, C Mesh      &mesh, Vec *hit_pos=null, Int *hit_face=null, Int *hit_part=null                    , Bool test_quads_as_2_tris=true); // 'hit_part'=index of hit MeshPart
Bool PosPointMeshXR(C Vec &point, C MeshGroup &mshg, Vec *hit_pos=null, Int *hit_face=null, Int *hit_part=null, Int *hit_mesh=null, Bool test_quads_as_2_tris=true); // 'hit_part'=index of hit MeshPart, 'hit_mesh'=index of hit Mesh

// raycast downward from (point.x, +Inf, point.z)  ('point.y' is ignored), return if hit, 'hit_pos'=hit position, 'hit_face'=index of hit face, if you're sure that quads are fully valid (their triangles are coplanar) set 'test_quads_as_2_tris'=false for performance boost
Bool PosPointMeshY(C Vec &point, C MeshBase  &mshb, Vec *hit_pos=null, Int *hit_face=null,                                         Bool test_quads_as_2_tris=true);
Bool PosPointMeshY(C Vec &point, C Mesh      &mesh, Vec *hit_pos=null, Int *hit_face=null, Int *hit_part=null                    , Bool test_quads_as_2_tris=true); // 'hit_part'=index of hit MeshPart
Bool PosPointMeshY(C Vec &point, C MeshGroup &mshg, Vec *hit_pos=null, Int *hit_face=null, Int *hit_part=null, Int *hit_mesh=null, Bool test_quads_as_2_tris=true); // 'hit_part'=index of hit MeshPart, 'hit_mesh'=index of hit Mesh

// raycast forward from (point.x, point.y, -Inf)  ('point.z' is ignored), return if hit, 'hit_pos'=hit position, 'hit_face'=index of hit face, if you're sure that quads are fully valid (their triangles are coplanar) set 'test_quads_as_2_tris'=false for performance boost
Bool PosPointMeshZF(C Vec &point, C MeshBase  &mshb, Vec *hit_pos=null, Int *hit_face=null,                                         Bool test_quads_as_2_tris=true);
Bool PosPointMeshZF(C Vec &point, C Mesh      &mesh, Vec *hit_pos=null, Int *hit_face=null, Int *hit_part=null                    , Bool test_quads_as_2_tris=true); // 'hit_part'=index of hit MeshPart
Bool PosPointMeshZF(C Vec &point, C MeshGroup &mshg, Vec *hit_pos=null, Int *hit_face=null, Int *hit_part=null, Int *hit_mesh=null, Bool test_quads_as_2_tris=true); // 'hit_part'=index of hit MeshPart, 'hit_mesh'=index of hit Mesh

// raycast backward from (point.x, point.y, +Inf)  ('point.z' is ignored), return if hit, 'hit_pos'=hit position, 'hit_face'=index of hit face, if you're sure that quads are fully valid (their triangles are coplanar) set 'test_quads_as_2_tris'=false for performance boost
Bool PosPointMeshZB(C Vec &point, C MeshBase  &mshb, Vec *hit_pos=null, Int *hit_face=null,                                         Bool test_quads_as_2_tris=true);
Bool PosPointMeshZB(C Vec &point, C Mesh      &mesh, Vec *hit_pos=null, Int *hit_face=null, Int *hit_part=null                    , Bool test_quads_as_2_tris=true); // 'hit_part'=index of hit MeshPart
Bool PosPointMeshZB(C Vec &point, C MeshGroup &mshg, Vec *hit_pos=null, Int *hit_face=null, Int *hit_part=null, Int *hit_mesh=null, Bool test_quads_as_2_tris=true); // 'hit_part'=index of hit MeshPart, 'hit_mesh'=index of hit Mesh
/******************************************************************************/
// get mesh rest matrix as if it has fallen on the ground and lying there, 'initial_matrix'=initial matrix of the mesh (use null for no custom matrix), 'mass_center'=mesh center of mass (use null for auto-detect), 'min_dist'=minimum distance between vertexes to consider them as contact points, 'rest_box'=if specified then it will be set to the precise box of the mesh after being transformed by the rest matrix, 'max_steps'=maximum number of steps to perform the calculation (<0 = unlimited), 'only_visible'=if process only visible mesh parts, 'only_phys'=if process only mesh parts without 'MSHP_NO_PHYS_BODY'
Matrix GetRestMatrix(C MeshBase             &mesh  , C Matrix *initial_matrix=null, C Vec *mass_center=null, Flt min_dist=0.01f, Box *rest_box=null, Int max_steps=-1);
Matrix GetRestMatrix(C MeshLod              &mesh  , C Matrix *initial_matrix=null, C Vec *mass_center=null, Flt min_dist=0.01f, Box *rest_box=null, Int max_steps=-1, Bool only_visible=true, Bool only_phys=true);
Matrix GetRestMatrix(C Mesh                 &mesh  , C Matrix *initial_matrix=null, C Vec *mass_center=null, Flt min_dist=0.01f, Box *rest_box=null, Int max_steps=-1, Bool only_visible=true, Bool only_phys=true);
Matrix GetRestMatrix(C CMemPtr<C MeshPart*> &meshes, C Matrix *initial_matrix=null, C Vec *mass_center=null, Flt min_dist=0.01f, Box *rest_box=null, Int max_steps=-1, Bool only_visible=true, Bool only_phys=true);
Matrix GetRestMatrix(C CMemPtr<C MeshLod *> &meshes, C Matrix *initial_matrix=null, C Vec *mass_center=null, Flt min_dist=0.01f, Box *rest_box=null, Int max_steps=-1, Bool only_visible=true, Bool only_phys=true);
/******************************************************************************/
