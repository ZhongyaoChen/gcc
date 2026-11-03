/* { dg-do compile } */
/* { dg-additional-options "-march=rv64gcv -mabi=lp64d" } */

#include <stdint-gcc.h>

typedef int16_t vnx16hi __attribute__ ((vector_size (32)));

__attribute__ ((noipa)) void
f_vnx16hi (int16_t a, int16_t b, int16_t c, int16_t d, int16_t e, int16_t f,
	   int16_t g, int16_t h, int16_t i, int16_t j, int16_t k, int16_t l,
	   int16_t m, int16_t n, int16_t o, int16_t p, int16_t *out)
{
  vnx16hi v = {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p};
  *(vnx16hi *) out = v;
}

/*
 {a,b} {c,d} {e,f} {g,h} {i,j} {k,l} {m,n} {o,p}  mf4: 8 vmv + 8 vslide1down
   \   /       \   /       \   /       \   /
  {a,b,c,d}   {e,f,g,h}   {i,j,k,l}   {m,n,o,p}   mf2: 4 vslideup
      \           /           \           /
   {a,b,c,d,e,f,g,h}       {i,j,k,l,m,n,o,p}      m1:  2 vslideup
            \                       /
      {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p}           m2:  0 insns  */
/* { dg-final { scan-assembler-times {vmv\.v\.x\tv[0-9]+,\s*[a-x0-9]+} 8 } } */
/* { dg-final { scan-assembler-times {vslide1down\.vx\tv[0-9]+,\s*v[0-9]+,\s*[a-x0-9]+} 8 } } */
/* { dg-final { scan-assembler-times {vslideup\.vi\tv[0-9]+,\s*v[0-9]+,\s*[0-9]+} 6 } } */
