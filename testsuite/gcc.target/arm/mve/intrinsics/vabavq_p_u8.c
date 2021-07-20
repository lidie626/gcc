/* { dg-require-effective-target arm_v8_1m_mve_ok } */
/* { dg-add-options arm_v8_1m_mve } */
/* { dg-additional-options "-O2" } */

#include "arm_mve.h"

uint32_t
foo (uint32_t a, uint8x16_t b, uint8x16_t c, mve_pred16_t p)
{
  return vabavq_p_u8 (a, b, c, p);
}

/* { dg-final { scan-assembler "vabavt.u8"  }  } */

uint32_t
foo1 (uint32_t a, uint8x16_t b, uint8x16_t c, mve_pred16_t p)
{
  return vabavq_p (a, b, c, p);
}

/* { dg-final { scan-assembler "vabavt.u8"  }  } */