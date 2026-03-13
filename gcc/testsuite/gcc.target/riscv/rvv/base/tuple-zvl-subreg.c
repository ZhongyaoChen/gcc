/* { dg-do compile } */
/* { dg-options "-march=rv64gcv_zvl256b -mabi=lp64d -O3" } */
/* { dg-additional-options "-mrvv-vector-bits=zvl" } */
/* { dg-additional-options "-fno-schedule-insns -fno-schedule-insns2" } */

#include <stddef.h>
#include "riscv_vector.h"

/* Two disjoint tuple field updates should not require whole-register
   copies when -mrvv-vector-bits=zvl represents the fields as VLS
   subregs.  */

__attribute__ ((noipa))
void
foo (float *dst)
{
  const size_t vl = 8;
  const ptrdiff_t stride = (ptrdiff_t) sizeof (*dst);
  vfloat32m1x8_t tuple = __riscv_vlsseg8e32_v_f32m1x8 (dst, stride, vl);

  tuple = __riscv_vset_v_f32m1_f32m1x8 (
    tuple, 0,
    __riscv_vfadd_vf_f32m1 (
      __riscv_vget_v_f32m1x8_f32m1 (tuple, 0), 1.0f, vl));
  tuple = __riscv_vset_v_f32m1_f32m1x8 (
    tuple, 7,
    __riscv_vfadd_vf_f32m1 (
      __riscv_vget_v_f32m1x8_f32m1 (tuple, 7), 2.0f, vl));

  __riscv_vssseg8e32_v_f32m1x8 (dst, stride, tuple, vl);
}

/* { dg-final { scan-assembler-not {vmv[1248]r\.v\s+v[0-9]+,\s*v[0-9]+} } } */
