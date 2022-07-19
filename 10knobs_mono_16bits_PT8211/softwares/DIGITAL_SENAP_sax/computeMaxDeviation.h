#ifndef _CMD_
#define _CMD_
#include <mozzi_fixmath.h>

void computeMaxDeviation(Q16n16 * LUT, float exponent, float prefactor, int size)
{
  for (int i =0; i<size; i++)
  {
    LUT[i] = float_to_Q16n16(prefactor*exp(-1.*i*exponent));
  }
}




#endif
