/* { dg-do compile } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -mrvv-vector-bits=zvl" } */

typedef char v8qi __attribute__ ((vector_size (8)));
typedef char v16qi __attribute__ ((vector_size (16)));
typedef short v4hi __attribute__ ((vector_size (8)));
typedef short v8hi __attribute__ ((vector_size (16)));
typedef short v16hi __attribute__ ((vector_size (32)));
typedef int v2si __attribute__ ((vector_size (8)));
typedef int v4si __attribute__ ((vector_size (16)));
typedef int v8si __attribute__ ((vector_size (32)));
typedef float v2sf __attribute__ ((vector_size (8)));
typedef float v4sf __attribute__ ((vector_size (16)));
typedef float v8sf __attribute__ ((vector_size (32)));

/* LMUL <= 1 cases (uses vslideup) */
v16qi
concat_v8qi (v8qi a, v8qi b)
{
  return __builtin_shufflevector (a, b, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
}

v4si
concat_v2si (v2si a, v2si b)
{
  return __builtin_shufflevector (a, b, 0, 1, 2, 3);
}

v4sf
concat_v2sf (v2sf a, v2sf b)
{
  return __builtin_shufflevector (a, b, 0, 1, 2, 3);
}

/* LMUL > 1 cases */
v8si
concat_v4si (v4si a, v4si b)
{
  return __builtin_shufflevector (a, b, 0, 1, 2, 3, 4, 5, 6, 7);
}

v16hi
concat_v8hi (v8hi a, v8hi b)
{
  return __builtin_shufflevector (a, b, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
}

v8sf
concat_v4sf (v4sf a, v4sf b)
{
  return __builtin_shufflevector (a, b, 0, 1, 2, 3, 4, 5, 6, 7);
}

/* Even/odd deinterleave pattern testing (uses expand_vec_concat in shuffle_even_odd_patterns) */
v4si
even_v4si (v4si a, v4si b)
{
  return __builtin_shufflevector (a, b, 0, 2, 4, 6);
}

v8si
even_v8si (v8si a, v8si b)
{
  return __builtin_shufflevector (a, b, 0, 2, 4, 6, 8, 10, 12, 14);
}

/* { dg-final { scan-assembler "vslideup" } } */
/* { dg-final { scan-assembler "vnsrl" } } */
