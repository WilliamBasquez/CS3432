
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Searches the array, which must be sorted by increasing values, for
   the value e. Considers only the elements of the array between the
   indices l and r (both included). For the value to have a chance to
   be found, l must be less than or equal to r. The value l is a left
   start index, the value r is a right end index.

   All the array elements and the value e to be sought for are strings, 
   i.e. arrays of characters. 

   In order to compare strings, the function uses the strcmp function
   from string.h.

   The function returns the index of the element of the array that
   contains the value e, considering only the indices between l and r,
   both included. If e does not figure among the elements of the array
   at indices between l and r, the function returns a negative "dummy"
   value, typically -1.

   The function is recursive and proceeds like a usual search in a
   dictionary or phonebook would proceed:

   If l is greater than r, there are no indices at which the value
   might figure in the array. The function returns -1.

   Otherwise the function computes the index (approximately) in the
   middle between l and r: m = (l + r) / 2. It does not matter if m is
   not precisely in the middle, i.e. if l + r is an odd number.

   If the value e is found at that middle index m, the function
   happily returns that middle index m.

   Otherwise the function compares the value e with the element of 
   the array at that middle index m:

   If e is less than the element of the array at m, the function calls
   itself to search the array in the first half of the current range
   between l and r. The function hence calls itself with an index
   range between l and m - 1. The function returns the index returned
   by the recursive call.

   Otherwise, e is greater than the element of the array at the middle
   index m, and the function calls itself of the second half of the
   current range between l and r.  The function hence calls itself
   with an index range between m + 1 and r. The function returns the
   index returned by the recursive call.

   CAUTION: THE FUNCTION MAY CALL strcmp, BUT IT MAY CALL strcmp ONLY
   ONCE PER RECURSIVE CALL.

*/
int search_aux(char *e, char *array[], int l, int r) {
  int m, cmp;
  
  /* Nothing left in the search domain */
  if (l > r) return -1;

  /* Compute middle index */
  m = (l + r) / 2;

  /* Compare e to array element at index m */
  cmp = strcmp(e, array[m]);

  /* Case when we get lucky */
  if (cmp == 0) return m;

  /* Go left or right depending on where we are */
  if (cmp < 0) return search_aux(e, array, l, m-1);
  return search_aux(e, array, m+1, r);
}

/* Searches the array, which must be sorted by increasing values, for
   the value e. The array has n elements.

   The function returns the index of the element of the array that
   contains the value e. If e does not figure among the elements of
   the array, the function returns a negative "dummy" value, typically
   -1.

   The search function is just a wrapper around the auxiliary
   search_aux function above.

*/
int search(char *e, char *array[], int n) {
  if (n < 1) return -1;
  return search_aux(e, array, 0, n-1);
}

/* A function to input a string */
void input_string(char *str, int max_str_len) {
  char c;
  int i;
  
  if (max_str_len < 1) return;  
  for (i=0; i<max_str_len-1; i++) {
    scanf("%c", &c);
    if (c == '\n') {
      break;
    }
    str[i] = c;
  } 
  str[i] = '\0';
}

/* A function to input strings into an array of size n */
void input_array(char *array[], int n, int max_str_len) {
  int i;

  printf("Please enter %d strings.\n", n);
  for (i=0; i<n; i++) {
    input_string(array[i], max_str_len);
  }
}

/* A function to print out an array of size n */
void print_array(char *array[], int n) {
  int i;

  for (i=0; i<n; i++) {
    printf("%s\n", array[i]);
  }
  printf("\n");
}

/* A comparison function suitable for the 
   qsort library function used below in main.

   This function uses features of C you do not know yet. Do not be
   scared. You do not need to understand them.

*/
int comp(const void *a, const void *b) {
  return strcmp(*((char * const *) a), *((char * const *) b));
}


/* The main function

   This function uses features of C you do not know yet. Do not be
   scared. You do not need to understand them.

*/
int main(int argc, char **argv) {
  const int MAX_STR_LEN = 256;
  const int NUM_ELEMENTS = 16;
  char lin_arr[NUM_ELEMENTS * MAX_STR_LEN];
  char *array[NUM_ELEMENTS];
  int i;
  char str[MAX_STR_LEN];

  /* Initialize the array */
  for (i=0; i<NUM_ELEMENTS; i++) {
    array[i] = &lin_arr[i * MAX_STR_LEN];
  }

  /* Ask the user to input values for an array */
  input_array(array, NUM_ELEMENTS, MAX_STR_LEN);

  /* Print out the array as given by the user */
  printf("The input array, not yet sorted is:\n");
  print_array(array, NUM_ELEMENTS);

  /* Sort the array using a predefined sorting algorithm from a
     library 
  */
  qsort(((void *) array), ((size_t) NUM_ELEMENTS), sizeof(char *), comp);

  /* Print out the sorted array */
  printf("The sorted input array:\n");
  print_array(array, NUM_ELEMENTS);

  /* Ask the user to enter a string */
  printf("Please enter a string: ");
  input_string(str, MAX_STR_LEN);

  /* Try to find the string in the array */
  i = search(str, array, NUM_ELEMENTS);

  /* If the "index" returned by the search function is negative the
     integer does not figure in the array. If its non-negative, the
     integer figures at that index.

  */
  if (i < 0) {
    printf("The string \"%s\" does not figure in the array.\n", str);
  } else {
    printf("The string \"%s\" figures in the array at index %d.\n", str, i);
  }

  return 0;
}
