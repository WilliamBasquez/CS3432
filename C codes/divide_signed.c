void divide_signed(int *quot, int *rem, int a, int b) {
  unsigned int abs_a, abs_b, abs_quot, abs_rem;
  unsigned int sa, sb, sr;

  if (a < 0) {
    abs_a = -a;
    sa = (unsigned int) 1;
  } else {
    abs_a = a;
    sa = (unsigned int) 0;
  }
  if (b < 0) {
    abs_b = -b;
    sb = (unsigned int) 1;
  } else {
    abs_b = b;
    sb = (unsigned int) 0;
  }
  sr = sa ^ sb;
  divide_unsigned(&abs_quot, &abs_rem, abs_a, abs_b);
  if (sr) {
    *quot = -((int) abs_quot);
    *rem = -((int) abs_rem);
  } else {
    *quot = (int) abs_quot;
    *rem = (int) abs_rem;
  }
}