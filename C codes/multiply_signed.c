int multiply_signed(int a, int b){
    unsigned int abs_a, abs_b, abs_res;
    int sa, sb, sr, res;

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

    abs_res = multiply_unsigned(abs_a, abs_b);
    if (sr) {
        res = -((int) abs_res);
    } else {
        res = (int) abs_res;
    }
    return res;
}
