#ifndef _DTP_
#define _DTP_

// For the mod on carrier ratio: half the course give an integer value, the remaining a full continuum


int inline dual_type_pot(int input)
{
  if (input <= 2048) return (input >> 8) << 8;
  else
  {
    return (input - 2048);
  }
}

#endif