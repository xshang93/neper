/* This file is part of the Neper software package. */
/* Copyright (C) 2003-2022, Romain Quey. */
/* See the COPYING file in the top-level directory. */

#include "neut_tesr_gen_.h"

void
neut_tesr_cell (struct TESR Tesr, char **pcell)
{
  if (Tesr.Dim == 0)
    ut_string_string ("ver", pcell);
  else if (Tesr.Dim == 1)
    ut_string_string ("edge", pcell);
  else if (Tesr.Dim == 2)
    ut_string_string ("face", pcell);
  else if (Tesr.Dim == 3)
    ut_string_string ("poly", pcell);
  else
    ut_print_neperbug ();

  return;
}

void
neut_tesr_entity_qty (struct TESR Tesr, char *entity, int *pqty)
{
  if (!strcmp (entity, "tesr"))
    (*pqty) = 1;
  else if (!strcmp (entity, "poly") || !strcmp (entity, "cell"))
    (*pqty) = Tesr.CellQty;
  else if (!strcmp (entity, "seed"))
    (*pqty) = Tesr.CellQty;
  else if (!strcmp (entity, "vox"))
    (*pqty) = ut_array_1d_int_prod (Tesr.size, 3);
  else if (!strcmp (entity, "group"))
    (*pqty) = Tesr.CellGroup ? ut_array_1d_int_max (Tesr.CellGroup + 1, Tesr.CellQty) : 0;
  else
    (*pqty) = -1;

  return;
}

void
neut_tesr_var_list (char *entity, char ***pvar, int *pvarqty)
{
  int id = 0;

  if (!strcmp (entity, "tesr"))
  {
    (*pvarqty) = 22;
    (*pvar) = ut_alloc_2d_char (*pvarqty, 10);
    strcpy ((*pvar)[id++], "dim");
    strcpy ((*pvar)[id++], "voxnbx");
    strcpy ((*pvar)[id++], "voxnby");
    strcpy ((*pvar)[id++], "voxnbz");
    strcpy ((*pvar)[id++], "voxnb");
    strcpy ((*pvar)[id++], "originx");
    strcpy ((*pvar)[id++], "originy");
    strcpy ((*pvar)[id++], "originz");
    strcpy ((*pvar)[id++], "voxsizex");
    strcpy ((*pvar)[id++], "voxsizey");
    strcpy ((*pvar)[id++], "voxsizez");
    strcpy ((*pvar)[id++], "rastersizex");
    strcpy ((*pvar)[id++], "rastersizey");
    strcpy ((*pvar)[id++], "rastersizez");
    strcpy ((*pvar)[id++], "rastersize");
    strcpy ((*pvar)[id++], "area");
    strcpy ((*pvar)[id++], "vol");
    strcpy ((*pvar)[id++], "size");
    strcpy ((*pvar)[id++], "x");
    strcpy ((*pvar)[id++], "y");
    strcpy ((*pvar)[id++], "z");
    strcpy ((*pvar)[id++], "coo");
  }
  else if (!strcmp (entity, "cell"))
  {
    (*pvarqty) = 27;
    (*pvar) = ut_alloc_2d_char (*pvarqty, 30);
    strcpy ((*pvar)[0], "id");
    strcpy ((*pvar)[1], "x");
    strcpy ((*pvar)[2], "y");
    strcpy ((*pvar)[3], "z");
    strcpy ((*pvar)[4], "vol");
    strcpy ((*pvar)[5], "diameq");
    strcpy ((*pvar)[6], "radeq");
    strcpy ((*pvar)[7], "size");
    strcpy ((*pvar)[8], "convexity");
    strcpy ((*pvar)[9], "coo");
    strcpy ((*pvar)[10], "group");
    strcpy ((*pvar)[11], "oridisanisoangles");
    strcpy ((*pvar)[12], "oridisanisoaxes");
    strcpy ((*pvar)[13], "oridisanisofact");
    strcpy ((*pvar)[14], "oridisanisodeltas");
    strcpy ((*pvar)[15], "vxmin");
    strcpy ((*pvar)[16], "vymin");
    strcpy ((*pvar)[17], "vzmin");
    strcpy ((*pvar)[18], "vxmax");
    strcpy ((*pvar)[19], "vymax");
    strcpy ((*pvar)[20], "vzmax");
    strcpy ((*pvar)[21], "domvxmin");
    strcpy ((*pvar)[22], "domvymin");
    strcpy ((*pvar)[23], "domvzmin");
    strcpy ((*pvar)[24], "domvxmax");
    strcpy ((*pvar)[25], "domvymax");
    strcpy ((*pvar)[26], "domvzmax");
  }
  else if (!strcmp (entity, "vox"))
  {
    (*pvarqty) = 10;
    (*pvar) = ut_alloc_2d_char (*pvarqty, 10);
    strcpy ((*pvar)[0], "id");
    strcpy ((*pvar)[1], "cell");
    strcpy ((*pvar)[2], "x");
    strcpy ((*pvar)[3], "y");
    strcpy ((*pvar)[4], "z");
    strcpy ((*pvar)[5], "vx");
    strcpy ((*pvar)[6], "vy");
    strcpy ((*pvar)[7], "vz");
    strcpy ((*pvar)[8], "coo");
    strcpy ((*pvar)[9], "vcoo");
  }
  else if (!strcmp (entity, "group"))
  {
    (*pvarqty) = 7;
    (*pvar) = ut_alloc_2d_char (*pvarqty, 10);
    strcpy ((*pvar)[0], "id");
    strcpy ((*pvar)[1], "vol");
    strcpy ((*pvar)[2], "volfrac");
    strcpy ((*pvar)[3], "area");
    strcpy ((*pvar)[4], "areafrac");
    strcpy ((*pvar)[5], "size");
    strcpy ((*pvar)[6], "sizefrac");
  }
  else
    ut_print_neperbug ();

  return;
}

int
neut_tesr_expr_val_int (struct TESR Tesr, char *entity, int id, char *expr,
                        int **pvals, int *pvalqty, char **ptype)
{
  int status;
  double *tmp = NULL;

  status = neut_tesr_expr_val (Tesr, entity, id, expr, &tmp, pvalqty, ptype);

  (*pvals) = ut_realloc_1d_int (*pvals, *pvalqty);
  ut_array_1d_round (tmp, *pvalqty, *pvals);

  ut_free_1d (&tmp);

  return status;
}

int
neut_tesr_expr_val (struct TESR Tesr, char *entity, int id, char *expr,
                    double **pvals, int *pvalqty, char **ptype)
{
  int i, status, varqty, isvar;
  char **vars = NULL;
  double *vals = NULL;

  neut_tesr_var_list (entity, &vars, &varqty);
  vals = ut_alloc_1d (varqty);

  isvar = 0;
  for (i = 0; i < varqty; i++)
    if (!strcmp (expr, vars[i]))
    {
      isvar = 1;
      status =
        neut_tesr_var_val (Tesr, entity, id, expr, pvals, pvalqty, ptype);
      break;
    }

  if (!isvar)
  {
    for (i = 0; i < varqty; i++)
      if (strstr (expr, vars[i]))
        neut_tesr_var_val_one (Tesr, entity, id, vars[i], vals + i, NULL);

    (*pvalqty) = 1;
    (*pvals) = ut_realloc_1d (*pvals, *pvalqty);
    status = ut_math_eval (expr, varqty, vars, vals, *pvals);

    if (ptype)
      ut_string_string ("%f", ptype);
  }

  ut_free_2d_char (&vars, varqty);
  ut_free_1d (&vals);

  return status;
}

int
neut_tesr_var_val_int (struct TESR Tesr, char *entity, int id, char *var,
                       int **pvals, int *pvalqty, char **ptype)
{
  int status;
  double *tmp = NULL;

  status = neut_tesr_var_val (Tesr, entity, id, var, &tmp, pvalqty, ptype);
  (*pvals) = ut_realloc_1d_int (*pvals, *pvalqty);
  ut_array_1d_round (tmp, *pvalqty, *pvals);

  return status;
}

int
neut_tesr_var_val (struct TESR Tesr, char *entity, int id, char *var,
                   double **pvals, int *pvalqty, char **ptype)
{
  int i, status, b, tmpint, tmpint3[3];
  double *c = NULL;
  char *typetmp = NULL;

  (*pvals) = ut_realloc_1d (*pvals, 1);

  if (pvalqty)
    (*pvalqty) = 1;

  // this is for a quick evaluation
  if (!strcmp (entity, "vox")
      && (!strcmp (var, "x") || !strcmp (var, "y") || !strcmp (var, "z")))
  {
    double *coo = ut_alloc_1d (3);
    neut_tesr_vox_coo (Tesr, id, coo);
    (*pvals)[0] = coo[var[0] - 'x'];
    if (ptype)
      ut_string_string ("%f", ptype);
    ut_free_1d (&coo);

    return 0;
  }

  c = ut_alloc_1d (3);
  ut_string_string ("%f", &typetmp);

  // b = (Tess.CellQty > 0) ? Tess.CellBody[id] : 0;
  b = 0;

  if (strcmp (entity, "vox")
      && (!strcmp (var, "x") || !strcmp (var, "y") || !strcmp (var, "z")
          || !strcmp (var, "coo")))
    neut_tesr_cell_centre (Tesr, id, c);

  status = -1;
  if (!strcmp (entity, "tesr"))
  {
    status = 0;
    if (!strcmp (var, "dim"))
    {
      (*pvals)[0] = Tesr.Dim;
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "voxnb"))
    {
      (*pvals)[0] = Tesr.size[0] * Tesr.size[1] * Tesr.size[2];
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "voxnbx"))
    {
      (*pvals)[0] = Tesr.size[0];
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "voxnby"))
    {
      (*pvals)[0] = Tesr.size[1];
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "voxnbz"))
    {
      (*pvals)[0] = Tesr.size[2];
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "voxsizex"))
      (*pvals)[0] = Tesr.vsize[0];
    else if (!strcmp (var, "voxsizey"))
      (*pvals)[0] = Tesr.vsize[1];
    else if (!strcmp (var, "voxsizez"))
      (*pvals)[0] = Tesr.vsize[2];
    else if (!strcmp (var, "rastersizex"))
      (*pvals)[0] = Tesr.vsize[0] * Tesr.size[0];
    else if (!strcmp (var, "rastersizey"))
      (*pvals)[0] = Tesr.vsize[1] * Tesr.size[1];
    else if (!strcmp (var, "rastersizez"))
      (*pvals)[0] = Tesr.vsize[2] * Tesr.size[2];
    else if (!strcmp (var, "rastersize"))
      neut_tesr_rastersize (Tesr, *pvals);
    else if (!strcmp (var, "area"))
      neut_tesr_area (Tesr, *pvals);
    else if (!strcmp (var, "vol"))
      neut_tesr_volume (Tesr, *pvals);
    else if (!strcmp (var, "size"))
      neut_tesr_size (Tesr, *pvals);
    else if (!strcmp (var, "x"))
      neut_tesr_centre_x (Tesr, *pvals);
    else if (!strcmp (var, "y"))
      neut_tesr_centre_y (Tesr, *pvals);
    else if (!strcmp (var, "z"))
      neut_tesr_centre_z (Tesr, *pvals);
    else if (!strcmp (var, "coo"))
    {
      neut_tesr_centre (Tesr, *pvals);
      (*pvalqty) = 3;
    }
    else if (!strcmp (var, "originx"))
      (*pvals)[0] = Tesr.Origin[0];
    else if (!strcmp (var, "originy"))
      (*pvals)[0] = Tesr.Origin[1];
    else if (!strcmp (var, "originz"))
      (*pvals)[0] = Tesr.Origin[2];
  }
  else if (!strcmp (entity, "cell") || !strcmp (entity, "poly")
        || !strcmp (entity, "face") || !strcmp (entity, "edge"))
  {
    status = 0;
    if (!strcmp (var, "id"))
    {
      if (strcmp (entity, "cell") != 0)
        (*pvals)[0] = id;
      else
        (*pvals)[0] = neut_tesr_cell_id (Tesr, id);
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "group"))
    {
      (*pvals)[0] = Tesr.CellGroup ? Tesr.CellGroup[id] : -1;
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "body"))
    {
      (*pvals)[0] = b;
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "x"))
      (*pvals)[0] = c[0];
    else if (!strcmp (var, "y"))
      (*pvals)[0] = c[1];
    else if (!strcmp (var, "z"))
      (*pvals)[0] = c[2];
    else if (!strcmp (var, "coo"))
    {
      (*pvalqty) = 3;
      (*pvals) = ut_realloc_1d (*pvals, *pvalqty);
      ut_array_1d_memcpy (c, 3, *pvals);
    }
    else if (!strcmp (var, "vol"))
      neut_tesr_cell_volume (Tesr, id, *pvals);
    else if (!strcmp (var, "diameq"))
      neut_tesr_cell_diameq (Tesr, id, *pvals);
    else if (!strcmp (var, "radeq"))
      neut_tesr_cell_radeq (Tesr, id, *pvals);
    else if (!strcmp (var, "size"))
      neut_tesr_cell_size (Tesr, id, *pvals);
    else if (!strcmp (var, "convexity"))
      neut_tesr_cell_convexity (Tesr, id, *pvals);
    else if (!strcmp (var, "oridisanisoangles"))
    {
      double **evect = ut_alloc_2d (3, 3);
      neut_tesr_cell_orianiso (Tesr, id, evect, *pvals);
      (*pvalqty) = 3;
      ut_free_2d (&evect, 3);
    }
    else if (!strcmp (var, "oridisanisofact"))
    {
      double **evect = ut_alloc_2d (3, 3);
      double *eval = ut_alloc_1d (3);
      neut_tesr_cell_orianiso (Tesr, id, evect, eval);
      (*pvals)[0] = eval[0] / pow (eval[0] * eval[1] * eval[2], 1. / 3);
      ut_free_2d (&evect, 3);
      ut_free_1d (&eval);
    }
    else if (!strcmp (var, "oridisanisoaxes"))
    {
      double **evect = ut_alloc_2d (3, 3);
      double *eval = ut_alloc_1d (3);
      neut_tesr_cell_orianiso (Tesr, id, evect, eval);
      (*pvals) = ut_realloc_1d (*pvals, 9);
      ut_array_1d_memcpy (evect[0], 3, *pvals);
      ut_array_1d_memcpy (evect[1], 3, *pvals + 3);
      ut_array_1d_memcpy (evect[2], 3, *pvals + 6);
      (*pvalqty) = 9;
      ut_free_2d (&evect, 3);
      ut_free_1d (&eval);
    }
    else if (!strcmp (var, "oridisanisodeltas"))
    {
      double **evect = ut_alloc_2d (3, 3);
      neut_tesr_cell_orianiso_delta (Tesr, id, evect, *pvals);
      (*pvalqty) = 3;
      ut_free_2d (&evect, 3);
    }
    else if (!strcmp (var, "vxmin"))
    {
      (*pvals)[0] = Tesr.CellBBox[id][0][0];
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "vymin"))
    {
      (*pvals)[0] = Tesr.CellBBox[id][1][0];
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "vzmin"))
    {
      (*pvals)[0] = Tesr.CellBBox[id][2][0];
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "vxmax"))
    {
      (*pvals)[0] = Tesr.CellBBox[id][0][1];
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "vymax"))
    {
      (*pvals)[0] = Tesr.CellBBox[id][1][1];
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "vzmax"))
    {
      (*pvals)[0] = Tesr.CellBBox[id][2][1];
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "domvxmin"))
    {
      (*pvals)[0] = 1;
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "domvymin"))
    {
      (*pvals)[0] = 1;
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "domvzmin"))
    {
      (*pvals)[0] = 1;
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "domvxmax"))
    {
      (*pvals)[0] = Tesr.size[0];
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "domvymax"))
    {
      (*pvals)[0] = Tesr.size[1];
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "domvzmax"))
    {
      (*pvals)[0] = Tesr.size[2];
      ut_string_string ("%d", &typetmp);
    }
  }
  else if (!strcmp (entity, "seed"))
  {
    status = 0;
    if (!strcmp (var, "id"))
    {
      (*pvals)[0] = id;
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "x"))
      (*pvals)[0] = Tesr.SeedCoo[id][0];
    else if (!strcmp (var, "y"))
      (*pvals)[0] = Tesr.SeedCoo[id][1];
    else if (!strcmp (var, "z"))
      (*pvals)[0] = Tesr.SeedCoo[id][2];
    else if (!strcmp (var, "w"))
      (*pvals)[0] = Tesr.SeedWeight[id];
    else if (!strcmp (var, "vol"))
      neut_tesr_cell_volume (Tesr, id, *pvals);
  }

  else if (!strcmp (entity, "vox"))
  {
    status = 0;
    if (!strcmp (var, "id"))
    {
      (*pvals)[0] = id;
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "cell"))
    {
      neut_tesr_vox_cellid (Tesr, id, &tmpint);
      (*pvals)[0] = tmpint;
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "vx"))
    {
      neut_tesr_vox_pos (Tesr, id, tmpint3);
      (*pvals)[0] = tmpint3[0];
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "vy"))
    {
      neut_tesr_vox_pos (Tesr, id, tmpint3);
      (*pvals)[0] = tmpint3[1];
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "vz"))
    {
      neut_tesr_vox_pos (Tesr, id, tmpint3);
      (*pvals)[0] = tmpint3[2];
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "vcoo"))
    {
      (*pvalqty) = 3;
      (*pvals) = ut_realloc_1d (*pvals, *pvalqty);
      neut_tesr_vox_pos (Tesr, id, tmpint3);
      for (i = 0; i < 3; i++)
        (*pvals)[i] = tmpint3[i];
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "x"))
    {
      neut_tesr_vox_coo (Tesr, id, c);
      (*pvals)[0] = c[0];
    }
    else if (!strcmp (var, "y"))
    {
      neut_tesr_vox_coo (Tesr, id, c);
      (*pvals)[0] = c[1];
    }
    else if (!strcmp (var, "z"))
    {
      neut_tesr_vox_coo (Tesr, id, c);
      (*pvals)[0] = c[2];
    }
    else if (!strcmp (var, "coo"))
    {
      (*pvalqty) = 3;
      (*pvals) = ut_realloc_1d (*pvals, *pvalqty);
      neut_tesr_vox_coo (Tesr, id, *pvals);
    }
    else
      status = -1;
  }

  else if (!strcmp (entity, "group"))
  {
    status = 0;
    if (!strcmp (var, "id"))
    {
      (*pvals)[0] = id;
      ut_string_string ("%d", &typetmp);
    }
    else if (!strcmp (var, "vol"))
      neut_tesr_group_volume (Tesr, id, *pvals);
    else if (!strcmp (var, "volfrac"))
      neut_tesr_group_volfrac (Tesr, id, *pvals);
    else if (!strcmp (var, "area"))
      neut_tesr_group_area (Tesr, id, *pvals);
    else if (!strcmp (var, "areafrac"))
      neut_tesr_group_areafrac (Tesr, id, *pvals);
    else if (!strcmp (var, "size"))
      neut_tesr_group_size (Tesr, id, *pvals);
    else if (!strcmp (var, "sizefrac"))
      neut_tesr_group_sizefrac (Tesr, id, *pvals);
    else
      status = -1;
  }

  else
    ut_print_message (2, 0, "Failed to process expression `%s'.\n", entity);

  if (ptype)
    ut_string_string (typetmp, ptype);

  ut_free_1d (&c);
  ut_free_1d_char (&typetmp);

  return status;
}

int
neut_tesr_var_val_one (struct TESR Tesr, char *entity, int id, char *var,
                       double *pval, char **ptype)
{
  int qty;
  double *tmp = NULL;

  neut_tesr_var_val (Tesr, entity, id, var, &tmp, &qty, ptype);
  if (qty != 1)
    abort ();

  *pval = tmp[0];

  ut_free_1d (&tmp);

  return 0;
}

int
neut_tesr_var_val_int_one (struct TESR Tesr, char *entity, int id, char *var,
                           int *pval, char **ptype)
{
  int qty, *tmp = NULL;

  neut_tesr_var_val_int (Tesr, entity, id, var, &tmp, &qty, ptype);
  if (qty != 1)
    abort ();

  *pval = tmp[0];

  ut_free_1d_int (&tmp);

  return 0;
}

int
neut_tesr_expr_val_int_one (struct TESR Tesr, char *entity, int id,
                            char *expr, int *pval, char **ptype)
{
  int qty, *tmp = NULL;

  neut_tesr_expr_val_int (Tesr, entity, id, expr, &tmp, &qty, ptype);
  if (qty != 1)
    abort ();

  *pval = tmp[0];

  ut_free_1d_int (&tmp);

  return 0;
}

void
neut_tesr_entity_expr_val (struct TESR Tesr, char *entity, char *expr,
                           double *val, char **ptype)
{
  int j, k, status, entityqty, varqty;
  char **vars = NULL;
  double *vals = NULL;
  FILE *file = NULL;
  char *type = NULL;

  if (ptype)
    ut_string_string ("%d", ptype);

  neut_tesr_entity_qty (Tesr, entity, &entityqty);
  neut_tesr_var_list (entity, &vars, &varqty);
  vals = ut_alloc_1d (varqty);

  if (ut_string_isfilename (expr))
  {
    file = ut_file_open (expr, "R");
    ut_array_1d_fscanf (file, val + 1, entityqty);
    ut_file_close (file, expr, "R");
  }
  else
  {
    for (j = 1; j <= entityqty; j++)
    {
      for (k = 0; k < varqty; k++)
        if (strstr (expr, vars[k]))
        {
          neut_tesr_var_val_one (Tesr, entity, j, vars[k], vals + k, &type);
          if (ptype && !strcmp (type, "%f"))
            ut_string_string ("%f", ptype);
        }

      status = ut_math_eval (expr, varqty, vars, vals, val + j);

      if (status == -1)
        abort ();
    }
  }

  ut_free_1d_char (&type);
  ut_free_2d_char (&vars, varqty);
  ut_free_1d (&vals);

  return;
}

int
neut_tesr_expr_val_one (struct TESR Tesr, char *entity, int id, char *expr,
                        double *pval, char **ptype)
{
  int qty;
  double *tmp = NULL;

  neut_tesr_expr_val (Tesr, entity, id, expr, &tmp, &qty, ptype);
  if (qty != 1)
    abort ();

  *pval = tmp[0];

  ut_free_1d (&tmp);

  return 0;
}

void
neut_tesr_var_dim (int dim, char *entity, char *var, int *pdim)
{
  neut_tess_var_dim (dim, entity, var, pdim);

  return;
}

int
neut_tesr_pos_valid (struct TESR Tesr, int *pos)
{
  return (pos[0] >= 1 && pos[0] <= Tesr.size[0] && pos[1] >= 1
          && pos[1] <= Tesr.size[1] && pos[2] >= 1 && pos[2] <= Tesr.size[2]);
}

void
neut_tesr_sizestring (struct TESR Tesr, char **psizestring)
{
  (*psizestring) = ut_realloc_1d_char (*psizestring, 1000);

  if (Tesr.Dim == 2)
    sprintf ((*psizestring), "%d%s%d", Tesr.size[0], NEUT_SEP_DEP,
             Tesr.size[1]);
  else if (Tesr.Dim == 3)
    sprintf ((*psizestring), "%d%s%d%s%d", Tesr.size[0], NEUT_SEP_DEP,
             Tesr.size[1], NEUT_SEP_DEP, Tesr.size[2]);
  else
    abort ();

  (*psizestring) =
    ut_realloc_1d_char ((*psizestring), strlen (*psizestring) + 1);

  return;
}

void
neut_tesr_cell_olset (struct TESR Tesr, int cell, struct OL_SET *pOSet)
{
  int i, j, k, qty;

  (*pOSet) =
    ol_set_alloc ((Tesr.CellBBox[cell][2][1] - Tesr.CellBBox[cell][2][0] +
                   1) * (Tesr.CellBBox[cell][1][1] -
                         Tesr.CellBBox[cell][1][0] +
                         1) * (Tesr.CellBBox[cell][0][1] -
                               Tesr.CellBBox[cell][0][0] + 1),
                  Tesr.CellCrySym ? Tesr.CellCrySym : "triclinic");

  qty = 0;
  for (k = Tesr.CellBBox[cell][2][0]; k <= Tesr.CellBBox[cell][2][1]; k++)
    for (j = Tesr.CellBBox[cell][1][0]; j <= Tesr.CellBBox[cell][1][1]; j++)
      for (i = Tesr.CellBBox[cell][0][0]; i <= Tesr.CellBBox[cell][0][1]; i++)
        if (Tesr.VoxCell[i][j][k] == cell)
          ol_q_memcpy (Tesr.VoxOri[i][j][k], (*pOSet).q[qty++]);

  (*pOSet).size = (size_t) qty;

  return;
}

int
neut_tesr_isvoid (struct TESR Tesr)
{
  return Tesr.CellQty == 0;
}

void
neut_tesr_entity_expr_val_int (struct TESR Tesr, char *entity, char *expr,
                               int *val)
{
  int qty;
  double *tmp = NULL;

  neut_tesr_entity_qty (Tesr, entity, &qty);
  tmp = ut_alloc_1d (qty + 1);

  neut_tesr_entity_expr_val (Tesr, entity, expr, tmp, NULL);
  ut_array_1d_round (tmp + 1, qty, val + 1);

  ut_free_1d (&tmp);

  return;
}

int
neut_tesr_hascellorispread (struct TESR Tesr)
{
  int i;

  if (Tesr.CellOriDistrib)
    for (i = 1; i <= Tesr.CellQty; i++)
      if (strcmp (Tesr.CellOriDistrib[i], "none"))
        return 1;

  return 0;
}

int
neut_tesr_cellid_cell (struct TESR Tesr, int cellid, int *pcell)
{
  if (pcell)
    *pcell = -1;

  if (!Tesr.CellId)
  {
    if (pcell)
      (*pcell) = cellid;
    return 0;
  }

  else
  {
    int i;
    for (i = 1; i <= Tesr.CellQty; i++)
      if (Tesr.CellId[i] == cellid)
      {
        if (pcell)
          *pcell = i;
        return 0;
      }
  }

  return -1;
}

int
neut_tesr_cell_id (struct TESR Tesr, int cell)
{
  return Tesr.CellId ? Tesr.CellId[cell] : cell;
}
