/* Test the vmulxq_laneq_f64 AArch64 SIMD intrinsic.  */

/* { dg-do run } */
/* { dg-options "-save-temps -O3" } */

#include "arm_neon.h"

extern void abort (void);

float64x2_t __attribute__ ((noinline))
test_vmulxq_laneq_f64_lane0 (float64x2_t vec1_1, float64x2_t vec1_2)
{
  return vmulxq_laneq_f64 (vec1_1, vec1_2, 0);
}

float64x2_t __attribute__ ((noinline))
test_vmulxq_laneq_f64_lane1 (float64x2_t vec1_1, float64x2_t vec1_2)
{
  return vmulxq_laneq_f64 (vec1_1, vec1_2, 1);
}

#define PASS_ARRAY(...) {__VA_ARGS__}

#define SETUP_VEC(V1_D, V2_D, EXP0, EXP1, I)				\
  void set_and_test_case##I ()						\
  {									\
    int i;								\
    float64_t vec1_data[] = V1_D;					\
    float64x2_t vec1 = vld1q_f64 (vec1_data);				\
    float64_t vec2_data[] =  V2_D;					\
    float64x2_t vec2 = vld1q_f64 (vec2_data);				\
									\
    float64_t expected_lane0[] = EXP0;					\
    float64_t expected_lane1[] = EXP1;					\
									\
    float64x2_t actual_lane0_v =					\
      test_vmulxq_laneq_f64_lane0 (vec1, vec2);				\
    float64_t actual_lane0[2];						\
    vst1q_f64 (actual_lane0, actual_lane0_v);				\
    for (i = 0; i < 2; ++i)						\
      if (actual_lane0[i] != expected_lane0[i])				\
	abort ();							\
									\
    float64x2_t actual_lane1_v =					\
      test_vmulxq_laneq_f64_lane1 (vec1, vec2);				\
    float64_t actual_lane1[2];						\
    vst1q_f64 (actual_lane1, actual_lane1_v);				\
    for (i = 0; i < 2; ++i)						\
      if (actual_lane1[i] != expected_lane1[i])				\
	abort ();							\
									\
  }									\

float64_t v1 = 3.14159265359;
float64_t v2 = 1.383894;

float64_t v3 = 0.0;
float64_t v4 = -0.0;
float64_t v5 = __builtin_huge_val ();
float64_t v6 = -__builtin_huge_val ();

float64_t spec = __builtin_huge_val () * __builtin_huge_val ();

SETUP_VEC (PASS_ARRAY (v1, v2), PASS_ARRAY (v1, v2), PASS_ARRAY (v1*v1, v2*v1),
	   PASS_ARRAY (v1*v2, v2*v2), 1)

SETUP_VEC (PASS_ARRAY (v3, v4), PASS_ARRAY (v5, v6), PASS_ARRAY (2.0, -2.0),
	   PASS_ARRAY (-2.0, 2.0), 2)

int
main (void)
{
  set_and_test_case1 ();
  set_and_test_case2 ();
  return 0;
}
/* { dg-final { scan-assembler-times "fmulx\[ \t\]+\[vV\]\[0-9\]+\.2\[dD\], ?\[vV\]\[0-9\]+\.2\[dD\], ?\[vV\]\[0-9\]+\.\[dD\]\\\[0\\\]\n" 1 } } */
/* { dg-final { scan-assembler-times "fmulx\[ \t\]+\[vV\]\[0-9\]+\.2\[dD\], ?\[vV\]\[0-9\]+\.2\[dD\], ?\[vV\]\[0-9\]+\.\[dD\]\\\[1\\\]\n" 1 } } */
