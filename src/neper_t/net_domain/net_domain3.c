/* This file is part of the Neper software package. */
/* Copyright (C) 2003-2022, Romain Quey. */
/* See the COPYING file in the top-level directory. */

#include"net_domain_.h"

void
net_domain_cylinder_planes (double h, double Rad, int qty, double **eq)
{
  int i;
  double *n = ut_alloc_1d (3);
  double *r = ol_r_alloc ();
  double theta;
  double **g = ol_g_alloc ();

  eq[0][1] = 0;
  eq[0][2] = 0;
  eq[0][3] = -1;
  eq[0][0] = 0;

  eq[1][1] = 0;
  eq[1][2] = 0;
  eq[1][3] = 1;
  eq[1][0] = h;

  Rad *= cos (M_PI / qty);

  n[0] = -1;
  ol_r_set_this (r, 0, 0, -1);

  for (i = 0; i < qty; i++)
  {
    theta = 360 * ((double) i) / qty;
    ol_rtheta_g (r, theta, g);
    ol_g_vect_vect (g, n, eq[i + 2] + 1);
    eq[i + 2][0] =
      Rad + (eq[i + 2][1] * Rad + eq[i + 2][2] * Rad + eq[i + 2][3] * Rad);
  }

  ol_r_free (n);
  ol_r_free (r);
  ol_g_free (g);

  return;
}

void
net_domain_stdtriangle_planes (int qty, double **eq)
{
  int i;
  double n[3] = { 0, 0, 1 }, **p = ut_alloc_2d (qty + 1, 3);
  double *r = ol_r_alloc ();
  double *q = ol_q_alloc ();
  double *q2 = ol_q_alloc ();
  double step, p2[3];

  ut_array_1d_set_4 (eq[0], 0, 0, 0, -1);
  ut_array_1d_set_4 (eq[1], 1e-6, 0, 0, 1);
  ut_array_1d_set_4 (eq[2], 0, 0, -1, 0);
  ut_array_1d_set_4 (eq[3], 0, -OL_IS2, OL_IS2, 0);

  ol_r_set_this (r, 0, 1, 0);
  ol_rtheta_q (r, -45, q);

  ol_r_set_this (r, 1, 0, 0);

  ol_theta_rad2deg (acos (sqrt (2. / 3)) / qty, &step);

  for (i = 0; i <= qty; i++)
  {
    ol_rtheta_q (r, i * step, q2);
    ol_q_q_q_ref (q, q2, q2);
    ol_q_ipf_stprojxy (q2, n, p[i]);
  }

  for (i = 0; i < qty; i++)
  {
    ut_array_1d_memcpy (p[i], 3, p2);
    p2[2] += 1;
    ut_space_points_plane (p[i], p[i + 1], p2, eq[i + 4]);
  }

  ol_r_free (r);
  ol_q_free (q);
  ol_q_free (q2);
  ut_free_2d (&p, qty + 1);

  return;
}

void
net_domain_tesspoly_planes (struct TESS Tess, int id, int *pqty, double **eq)
{
  int i, face;

  (*pqty) = Tess.PolyFaceQty[id];
  for (i = 1; i <= Tess.PolyFaceQty[id]; i++)
  {
    face = Tess.PolyFaceNb[id][i];
    ut_array_1d_memcpy (Tess.FaceEq[face], 4, eq[i - 1]);
    if (Tess.PolyFaceOri[id][i] == -1)
      ut_array_1d_scale (eq[i - 1], 4, -1);
  }

  return;
}

void
net_domain_clip (struct POLY *pPoly, double **eq, int qty)
{
  int i, j, shift;
  double **cubesize = ut_alloc_2d (3, 2);
  struct POLYMOD Polymod;

  if ((*pPoly).VerQty == 0)
  {
    cubesize[0][0] = -1e6;
    cubesize[0][1] = 1e6;
    cubesize[1][0] = -1e6;
    cubesize[1][1] = 1e6;
    cubesize[2][0] = -1e6;
    cubesize[2][1] = 1e6;

    net_domain_cube (cubesize, pPoly);
  }

  shift =
    ((*pPoly).FaceQty > 0) ? ut_array_1d_int_min ((*pPoly).FacePoly + 1,
                                                  (*pPoly).FaceQty) : 0;

  neut_polymod_set_zero (&Polymod);

  neut_poly_polymod ((*pPoly), &Polymod);

  int *BadVer = NULL;

  for (i = 0; i < qty; i++)
  {
    BadVer = ut_alloc_1d_int (Polymod.VerQty + 1);

    for (j = 1; j <= Polymod.VerQty; j++)
      if (Polymod.VerUse[j] == 1)
        if (ut_space_point_plane_side (Polymod.VerCoo[j] - 1, eq[i]) == 1)
          BadVer[++BadVer[0]] = j;

    if (BadVer[0] != 0)
      PolyhedronModification (shift - i - 1, eq[i], &Polymod, BadVer);

    ut_free_1d_int (&BadVer);
  }

  // neut_debug_polymod (stdout, Polymod);

  neut_poly_free (pPoly);

  // neut_debug_polymod (stdout, Polymod);
  net_polymod_poly (Polymod, pPoly);
  // neut_debug_poly (stdout, *pPoly);

  neut_polymod_free (&Polymod);

  ut_free_2d (&cubesize, 3);

  return;
}

void
net_domain_sphere_planes (double rad, int qty, double **eq)
{
  int i, j;
  double **pts = ut_alloc_2d (qty, 3);

  ut_space_sphere_points (1, qty, pts);

  for (i = 0; i < qty; i++)
  {
    ut_array_1d_memcpy (pts[i], 3, eq[i] + 1);
    eq[i][0] = rad;
    for (j = 0; j < 3; j++)
      eq[i][0] += rad * eq[i][j + 1];
  }

  ut_free_2d (&pts, qty);

  return;
}
