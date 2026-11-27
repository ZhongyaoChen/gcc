/* { dg-do compile } */
/* { dg-options "-O3 -march=rv64gcv_zvl128b -mrvv-vector-bits=zvl -mabi=lp64d -mno-vector-strict-align -mrvv-max-lmul=conv-dynamic -fdump-tree-vect-details" } */

typedef unsigned char uint8_t;

void
foo (uint8_t *__restrict dst, uint8_t *__restrict src,
     uint8_t *__restrict c, int n, int s)
{
  for (int i = 0; i < n; i++, dst += s, src += s)
    {
      uint8_t x = c[i];
      dst[0] = src[0] + x;
      dst[1] = src[1] + x;
      dst[2] = src[2] + x;
      dst[3] = src[3] + x;
    }
}

/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 1 "vect" } } */
/* { dg-final { scan-assembler "vlse32\\.v" } } */
/* { dg-final { scan-assembler "vsse32\\.v" } } */
