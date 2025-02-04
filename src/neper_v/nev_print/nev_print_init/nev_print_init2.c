/* This file is part of the Neper software package. */
/* Copyright (C) 2003-2022, Romain Quey. */
/* See the COPYING file in the top-level directory. */

#include"nev_print_init_.h"

void
nev_print_init_data (struct PRINT Print,
               struct TESS Tess, struct DATA *TessData, struct TESR Tesr,
               struct DATA *pTesrData, struct NODES Nodes,
               struct MESH *Mesh, struct POINT Point,
               struct DATA *pData, struct DATA *MeshData,
               struct DATA *pCsysData, struct DATA *pPointData)
{
  int dim, meshdim;
  double size;

  /*
  if (Tess.Dim == 0 && Tess.CellQty < 1)
    Tess.CellQty = 1;
  */

  if (Print.showtess && !neut_tess_isvoid (Tess))
    for (dim = 0; dim <= 4; dim++)
      nev_print_init_data_tess (Print, Tess, TessData + dim);

  if (Print.showtesr && (*pTesrData).Qty > 0)
    nev_print_init_data_tesr (Print, Tesr, pTesrData);

  if ((Print.shownode || Print.showmesh || Print.showslice) && Nodes.NodeQty > 0)
    nev_print_init_data_nodes (Print, Nodes, Nodes.NodeQty, pData);

  meshdim = neut_mesh_array_dim (Mesh);
  if ((Print.showmesh || Print.showslice) && meshdim > 0)
  {
    neut_mesh_size (Nodes, Mesh[meshdim], &size);

    for (dim = 0; dim <= meshdim; dim++)
      if (!neut_mesh_isvoid (Mesh[dim]))
        nev_print_init_data_mesh (Print, Mesh[dim], size, Mesh[dim].ElsetQty, meshdim, MeshData + dim);
  }

  if (Print.showcsys)
    nev_print_init_data_csys (Print, pCsysData);

  if (Print.showpoint && Point.PointQty > 0)
    nev_print_init_data_points (Print, Point, pPointData);

  return;
}

void
nev_print_init_show (struct TESS Tess, struct TESR Tesr, struct NODES Nodes,
               struct MESH *Mesh, int SQty, struct POINT Point,
               struct PRINT *pPrint)
{
  int dim = neut_mesh_array_dim (Mesh);
  int i, j, cellqty;
  int *cells = NULL;

  if (SQty > 0)
  {
    if ((*pPrint).showslice == -1)
      (*pPrint).showslice = 1;
    if ((*pPrint).showmesh == -1)
      (*pPrint).showmesh = 0;
    if ((*pPrint).showtess == -1)
      (*pPrint).showtess = 0;
    if ((*pPrint).showtesr == -1)
      (*pPrint).showtesr = 0;
  }

  if (dim >= 0 && (*pPrint).showmesh == -1)
  {
    (*pPrint).showmesh = 1;
    if ((*pPrint).showtess == -1)
      (*pPrint).showtess = 0;
    if ((*pPrint).showtesr == -1)
      (*pPrint).showtesr = 0;
  }

  if (Tess.VerQty > 0 && (*pPrint).showtess == -1)
    (*pPrint).showtess = 1;

  if (Tesr.CellQty > 0 && (*pPrint).showtesr == -1)
    (*pPrint).showtesr = 1;

  if (Point.PointQty > 0)
    if ((*pPrint).showpoint[0] == -1)
    {
      (*pPrint).showpoint =
        ut_realloc_1d_int ((*pPrint).showpoint, Point.PointQty + 1);
      ut_array_1d_int_set ((*pPrint).showpoint + 1, Point.PointQty, 1);
      (*pPrint).showpoint[0] = Point.PointQty;
    }

  if ((*pPrint).showmesh == 1)
  {
    if ((*pPrint).showelt3d[0] == -1)
    {
      (*pPrint).showelt3d =
        ut_realloc_1d_int ((*pPrint).showelt3d, Mesh[3].EltQty + 1);

      (*pPrint).showelt3d[0] = (dim == 3) ? Mesh[3].EltQty : 0;
      ut_array_1d_int_set ((*pPrint).showelt3d + 1, Mesh[3].EltQty, dim == 3);
    }

    if ((*pPrint).showelt2d[0] == -1)
    {
      (*pPrint).showelt2d =
        ut_realloc_1d_int ((*pPrint).showelt2d, Mesh[2].EltQty + 1);

      (*pPrint).showelt2d[0] = (dim == 2) ? Mesh[2].EltQty : 0;
      ut_array_1d_int_set ((*pPrint).showelt2d + 1, Mesh[2].EltQty, dim == 2);
    }

    if ((*pPrint).showelt1d[0] == -1)
    {
      (*pPrint).showelt1d =
        ut_realloc_1d_int ((*pPrint).showelt1d, Mesh[1].EltQty + 1);

      (*pPrint).showelt1d[0] = (dim == 1) ? Mesh[1].EltQty : 0;
      ut_array_1d_int_set ((*pPrint).showelt1d + 1, Mesh[1].EltQty, dim == 1);
    }

    if ((*pPrint).showelt0d[0] == -1)
    {
      (*pPrint).showelt0d =
        ut_realloc_1d_int ((*pPrint).showelt0d, Mesh[0].EltQty + 1);

      (*pPrint).showelt0d[0] = (dim == 0) ? Mesh[0].EltQty : 0;
      ut_array_1d_int_set ((*pPrint).showelt0d + 1, Mesh[0].EltQty, dim == 0);
    }

    if ((*pPrint).shownode[0] == -1)
    {
      (*pPrint).shownode =
        ut_realloc_1d_int ((*pPrint).shownode, Nodes.NodeQty + 1);

      (*pPrint).shownode[0] = 0;
      ut_array_1d_int_set ((*pPrint).shownode + 1, Nodes.NodeQty, 0);
    }
  }

  if ((*pPrint).showtess == 1)
  {
    if (Tess.Dim == 3 && (*pPrint).showpoly[0] == -1)
    {
      (*pPrint).showpoly =
        ut_realloc_1d_int ((*pPrint).showpoly, Tess.PolyQty + 1);
      (*pPrint).showpoly[0] = Tess.PolyQty;
      ut_array_1d_int_set ((*pPrint).showpoly + 1, Tess.PolyQty, 1);
    }

    if ((*pPrint).showface[0] == -1)
    {
      (*pPrint).showface =
        ut_realloc_1d_int ((*pPrint).showface, Tess.FaceQty + 1);
      if (Tess.Dim == 2)
      {
        (*pPrint).showface[0] = Tess.FaceQty;
        ut_array_1d_int_set ((*pPrint).showface + 1, Tess.FaceQty, 1);
      }
      else
      {
        (*pPrint).showface[0] = 0;
        ut_array_1d_int_set ((*pPrint).showface + 1, Tess.FaceQty, 0);
      }
    }

    if ((*pPrint).showedge[0] == -1)
    {
      (*pPrint).showedge =
        ut_realloc_1d_int ((*pPrint).showedge, Tess.EdgeQty + 1);
      ut_array_1d_int_set ((*pPrint).showedge, Tess.EdgeQty + 1, 0);

      for (i = 1; i <= Tess.EdgeQty; i++)
      {
        neut_tess_edge_cells (Tess, i, &cells, &cellqty);
        for (j = 0; j < cellqty; j++)
          if ((Tess.Dim == 3 && (*pPrint).showpoly[cells[j]] == 1)
              || (Tess.Dim == 2 && (*pPrint).showface[cells[j]] == 1))
          {
            (*pPrint).showedge[i] = 1;
            break;
          }
        ut_free_1d_int (&cells);
      }
    }

    if ((*pPrint).showver[0] == -1)
    {
      (*pPrint).showver =
        ut_realloc_1d_int ((*pPrint).showver, Tess.VerQty + 1);
      ut_array_1d_int_set ((*pPrint).showver, Tess.VerQty + 1, 0);
    }

    if ((*pPrint).showseed[0] == -1)
    {
      (*pPrint).showseed =
        ut_realloc_1d_int ((*pPrint).showseed, Tess.SeedQty + 1);
      ut_array_1d_int_set ((*pPrint).showseed, Tess.SeedQty + 1, 0);
    }
  }

  else if ((*pPrint).showtesr == 1)
  {
    if (Tesr.Dim == 2)
    {
      (*pPrint).showface =
        ut_realloc_1d_int ((*pPrint).showface, Tesr.CellQty + 1);
      ut_array_1d_int_set ((*pPrint).showface + 1, Tess.FaceQty, 0);

      if ((*pPrint).showface[0] == -1)
      {
        (*pPrint).showface[0] = Tesr.CellQty;
        ut_array_1d_int_set ((*pPrint).showface + 1, Tesr.CellQty, 1);
      }

      if (!(*pPrint).showedgestring)
        ut_string_string ("0", &(*pPrint).showedgestring);
      else if (!strcmp ((*pPrint).showedgestring, "all"))
        ut_string_string ("1", &(*pPrint).showedgestring);
      else if (!strcmp ((*pPrint).showedgestring, "none"))
        ut_string_string ("0", &(*pPrint).showedgestring);
    }
    else if (Tesr.Dim == 3)
    {
      (*pPrint).showpoly =
        ut_realloc_1d_int ((*pPrint).showpoly, Tesr.CellQty + 1);
      ut_array_1d_int_set ((*pPrint).showpoly + 1, Tess.PolyQty, 0);

      if ((*pPrint).showpoly[0] == -1)
      {
        (*pPrint).showpoly[0] = Tesr.CellQty;
        ut_array_1d_int_set ((*pPrint).showpoly + 1, Tesr.CellQty, 1);
      }
    }
  }

  if ((*pPrint).sceneshadow == -1)
  {
    if ((*pPrint).showmesh == 1)
    {
    }
    else if ((*pPrint).showtess == 1)
      dim = Tess.Dim;
    else if ((*pPrint).showtesr == 1)
      dim = Tesr.Dim;
    else
      dim = 3;

    (*pPrint).sceneshadow = (dim == 3) ? 1 : 0;
  }

  return;
}

void
nev_print_init_camera (struct TESS Tess, struct TESR Tesr, struct NODES Nodes,
                 struct MESH *Mesh, struct POINT Point,
                 struct DATA NodeData, struct PRINT *pPrint)
{
  int dim = -1;
  struct NODES Nodes2;

  neut_nodes_set_zero (&Nodes2);

  if (NodeData.CooData)
  {
    neut_nodes_memcpy (Nodes, &Nodes2);

    if (!strcmp (NodeData.CooDataType, "coo"))
      ut_array_2d_memcpy (NodeData.CooData + 1, Nodes.NodeQty, 3,
                          Nodes2.NodeCoo + 1);
    else if (!strcmp (NodeData.CooDataType, "disp"))
      ut_array_2d_add (Nodes2.NodeCoo + 1, NodeData.CooData + 1,
                       Nodes.NodeQty, 3, Nodes2.NodeCoo + 1);
    else
      ut_print_neperbug ();
  }
  else
    Nodes2 = Nodes;

  if (Tess.VerQty > 0 && Nodes.NodeQty == 0)
  {
    dim = Tess.Dim;

    nev_print_init_camera_coo_tess (Tess, (*pPrint).cameracoostring,
                              (*pPrint).cameracoo);
    nev_print_init_camera_coo_tess (Tess, (*pPrint).cameralookatstring,
                              (*pPrint).cameralookat);
  }
  else if (Nodes.NodeQty > 0)
  {
    dim = neut_nodes_dim (Nodes);
    if (dim == -1)
      ut_print_neperbug ();

    nev_print_init_camera_coo_mesh (Nodes2, Mesh[dim], (*pPrint).cameracoostring,
                              (*pPrint).cameracoo);
    nev_print_init_camera_coo_mesh (Nodes2, Mesh[dim], (*pPrint).cameralookatstring,
                              (*pPrint).cameralookat);
  }
  else if (Tesr.CellQty > 0)
  {
    dim = Tesr.Dim;

    nev_print_init_camera_coo_tesr (Tesr, (*pPrint).cameracoostring,
                              (*pPrint).cameracoo);
    nev_print_init_camera_coo_tesr (Tesr, (*pPrint).cameralookatstring,
                              (*pPrint).cameralookat);
  }
  else if (Point.PointQty > 0)
  {
    dim = Tesr.Dim;

    nev_print_init_camera_coo_points (Point, (*pPrint).cameracoostring,
                               (*pPrint).cameracoo);
    nev_print_init_camera_coo_points (Point, (*pPrint).cameralookatstring,
                               (*pPrint).cameralookat);
  }

  nev_print_init_camera_sky ((*pPrint).cameraskystring, dim, (*pPrint).camerasky);

  if (!strcmp ((*pPrint).cameraprojection, "default"))
  {
    strcpy ((*pPrint).cameraprojection, "perspective");
    if (dim <= 2)
      strcpy ((*pPrint).cameraprojection, "orthographic");
  }

  if (NodeData.CooData != NULL)
    neut_nodes_free (&Nodes2);

  return;
}
