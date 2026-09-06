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
  return (v16qi) {
    a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7],
    b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]
  };
}

v4si
concat_v2si (v2si a, v2si b)
{
  return (v4si) {a[0], a[1], b[0], b[1]};
}

v4sf
concat_v2sf (v2sf a, v2sf b)
{
  return (v4sf) {a[0], a[1], b[0], b[1]};
}

/* LMUL > 1 cases */
v8si
concat_v4si (v4si a, v4si b)
{
  return (v8si) {a[0], a[1], a[2], a[3], b[0], b[1], b[2], b[3]};
}

v16hi
concat_v8hi (v8hi a, v8hi b)
{
  return (v16hi) {
    a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7],
    b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]
  };
}

v8sf
concat_v4sf (v4sf a, v4sf b)
{
  return (v8sf) {a[0], a[1], a[2], a[3], b[0], b[1], b[2], b[3]};
}

/* { dg-final { scan-assembler "vslideup" } } */
