/* CODE WITH A FOR-LOOP */
unsigned int multiply_unsigned(unsigned int a, unsigned int b){
	unsigned int res;
	unsigned int ta;
	unsigned int tb;

	res = ((unsigned int) 0);
	ta = a;
	tb = b;

	for (int i = 0; i < (sizeof(a) << 3); i++){ //compare to 32 first
		if ((ta & ((unsigned int) 1)) != ((unsigned int) 0)){
			res += tb;
		}
		ta >>= 1;
		tb <<= 1;
	}
	return res;
}

/* CODE WITH A WHILE-LOOP*/
unsigned int multiply_unsigned(unsigned int a, unsigned int b){
	unsigned int res;
	unsigned int ta;
	unsigned int tb;

	res = ((unsigned int) 0);
	ta = a;
	tb = b;

	int i = 0;

	while (i < (sizeof(a) << 3)){ // compare i to 32
		if ((ta & ((unsigned int) 1)) != ((unsigned int) 0)){
			res += tb;
		}
		ta >>= 1;
		tb <<= 1;

		i++;
	}
	
	return res;
}

/* CODE WITH AN INFINITE WHILE-LOOP*/
unsigned int multiply_unsigned(unsigned int a, unsigned int b){
	unsigned int res;
	unsigned int ta;
	unsigned int tb;

	res = ((unsigned int) 0);
	ta = a;
	tb = b;

	int i = 0;

	while (1){
		if (i >= (sizeof(a) << 3)){ // Compare i to 32
			break;
		}

		if ((ta & ((unsigned int) 1)) != ((unsigned int) 0)){
			res += tb;
		}
		ta >>= 1;
		tb <<= 1;

		i++;
	}
	
	return res;
}

/* CODE WITH AN INFINITE LOOP AND USING TEMP */
unsigned int multiply_unsigned(unsigned int a, unsigned int b){
	unsigned int res;
	unsigned int ta;
	unsigned int tb;

	res = ((unsigned int) 0);
	ta = a;
	tb = b;

	int i = 0;

	while (1){

		char cmp = (i >= (sizeof(a) << 3)); //i < 32

		if (cmp == 0){ // Compare i to 32; if 0, end loop
			break;
		}
		
		unsigned int temp = (ta & (unsigned int) 1);

		if (temp != ((unsigned int) 0)){
			res += tb;
		}
		ta >>= 1;
		tb <<= 1;

		i++;
	}
	
	return res;
}
