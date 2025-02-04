/* This file is part of the Neper software package. */
/* Copyright (C) 2003-2022, Romain Quey. */
/* See the COPYING file in the top-level directory. */

#include"neut_oset_.hpp"

void
neut_oset_kdtree_cloud (struct OL_SET *pOSet, struct QCLOUD *pqcloud)
{
  unsigned int i, j, id, nc = ol_crysym_qty ((*pOSet).crysym);

  (*pqcloud).pts.resize ((*pOSet).size * 2 * nc);

  id = 0;
  for (i = 0; i < (*pOSet).size; i++)
  {
    for (j = 0; j < 4; j++)
      (*pqcloud).pts[id].q[j] = (*pOSet).q[i][j];
    id++;
  }

  for (i = 0; i < (*pOSet).size; i++)
  {
    for (j = 0; j < 4; j++)
      (*pqcloud).pts[id].q[j] = -(*pOSet).q[i][j];
    id++;
  }

  // recording their crysym equivalents
  for (i = 2; i <= nc; i++)
    for (j = 0; j < (*pOSet).size * 2; j++)
    {
      ol_q_crysym_nopos ((*pqcloud).pts[j].q, (*pOSet).crysym, i,
                         (*pqcloud).pts[id].q);
      id++;
    }

  return;
}

void
neut_oset_kdtree_build (struct QCLOUD *pqcloud, my_kd_tree_t ** pqindex)
{
  (*pqindex) = new my_kd_tree_t (4, *pqcloud);
  // KDTreeSingleIndexAdaptorParams (10 /* max leaf */ ));
  (*pqindex)->buildIndex ();

  return;
}
