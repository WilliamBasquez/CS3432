void divide_unsigned(unsigned int *quot, unsigned int *rem, unsigned int a, unsigned int b){
    int i;
    unsigned int q, r;

    if (b == 0) {
        *quot = (unsigned int) 0;
        *rem = a;
        return;
    }

    q = (unsigned int) 0;
    r = (unsigned int) 0;

    for (i = (sizeof(unsigned int) << 3)-1; i >= 0; i--){   //count from 31, down to 0.. this can become negative... 
    // i = 31
    // while (i >= 0){
        r <<= 1;
        r |= (a >> i) & ((unsigned int) 1);
        /*
        r = r | (a >> i) & ((unsigned int) 1);
        r = r | AND((a >> i), 1)
        r = OR(r, (AND((a >> i), 1)))
        */
        if (r >= b){
            q |= ((unsigned int) 1 << i);
            /*
            q = OR(q, (1 << i))
            */
            r -= b;
        }
    }
    *quot = q;
    *rem = r;
}
