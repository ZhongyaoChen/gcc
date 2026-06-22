/* { dg-do compile } */
/* { dg-require-effective-target vect_double } */
/* { dg-additional-options "-O2 -ftree-vectorize -fno-vect-cost-model -fdump-tree-slp1-details" } */

void
pr125800 (double *__restrict colY0, double *__restrict colY1,
	  const double *__restrict colA0, const double *__restrict colA1,
	  const double *__restrict colX0, const double *__restrict colX1,
	  int ncolA)
{
  double rsum00 = 0, isum00 = 0, rsum01 = 0, isum01 = 0;
  double rsum10 = 0, isum10 = 0, rsum11 = 0, isum11 = 0;

  for (int kcolA = 0; kcolA < ncolA; kcolA++)
    {
      int raloc = 2 * kcolA;
      int ialoc = raloc + 1;
      double ar0 = colA0[raloc];
      double ai0 = colA0[ialoc];
      double ar1 = colA1[raloc];
      double ai1 = colA1[ialoc];

      int rxloc = 2 * kcolA;
      int ixloc = rxloc + 1;
      double xr0 = colX0[rxloc];
      double xi0 = colX0[ixloc];
      double xr1 = colX1[rxloc];
      double xi1 = colX1[ixloc];

      rsum00 += ar0 * xr0 - ai0 * xi0;
      isum00 += ar0 * xi0 + ai0 * xr0;
      rsum01 += ar0 * xr1 - ai0 * xi1;
      isum01 += ar0 * xi1 + ai0 * xr1;
      rsum10 += ar1 * xr0 - ai1 * xi0;
      isum10 += ar1 * xi0 + ai1 * xr0;
      rsum11 += ar1 * xr1 - ai1 * xi1;
      isum11 += ar1 * xi1 + ai1 * xr1;
    }

  colY0[0] -= rsum00;
  colY0[1] -= isum00;
  colY1[0] -= rsum01;
  colY1[1] -= isum01;
  colY0[2] -= rsum10;
  colY0[3] -= isum10;
  colY1[2] -= rsum11;
  colY1[3] -= isum11;
}

/* { dg-final { scan-tree-dump "vectorizing stmts using SLP" "slp1" } } */
/* { dg-final { scan-tree-dump "SLP size 19" "slp1" { target { ! vect_partial_vectors } } } } */
