

#include <stdio.h>
#include <string.h>

/* Gets input from the user in the form of a string. The string
   contains up to n characters, including the end marker '\0'.

   No changes are needed here.

*/
void input_string(char *str, int m) {
  char c;
  int i;
  
  if (m <= 0) return;  
  for (i=0; i<m-1; i++) {
    scanf("%c", &c);
    if (c == '\n') {
      break;
    }
    str[i] = c;
  } 
  str[i] = '\0';
}

/* Prints an array of n strings, i.e. prints each of 
   n strings, given each as a pointer to an array of 
   characters. All pointers are in an array of pointers
   to characters.

   Prints each string on a separate line.

   If n is less than or equal to zero, does nothing.

*/
void print_array_of_strings(char *array[], int n) {
  int i;

  for (i=0;i<n;i++) {
    printf("%s\n", array[i]);
  }
}

/* Prompts the user to input an array of n strings. Inputs each of n
   strings, given each as a pointer to an array of characters. All
   pointers are in an array of pointers to characters. Each string is
   up to m characters long.

   If n is less than or equal to zero, does nothing, does not even
   prompt the user.

   Prompts the user with

   "Please enter %d lines of text.\n"

   Calls input_string() on each of the strings.

*/
void input_array_of_strings(char *array[], int n, int m) {
  int i;
  
  if (n <= 0) return;

  printf("Please enter %d lines of text.\n", n);
  for (i=0;i<n;i++) {
    input_string(array[i], m);
  }
}

/* Copies the pointers in an array src of n pointers into 
   an array dst of n pointers.

   Does not call strcpy() or strdup() or any other function!!! This
   means that the strings are not actually getting moved, just the
   pointers pointing to their first characters.
 
   Does nothing if n is less than or equal to zero.

*/
void copy_array_of_strings(char *dst[], char *src[], int n) {
  int i;

  for (i=0;i<n;i++) {
    dst[i] = src[i];
  }
}

/* Merges a sorted array of pointers a of size size_a and a sorted
   array of pointers b of size size_b into an array of pointers dst of
   size size_a + size_b.

   The arrays are sorted in the following way:

   * The pointers they contain in their different elements point to
     the first characters in arrays of characters, considered strings.

   * The strings are sorted in lexicographical order, i.e.  in the
     order induced by strcmp().

   The function does nothing if both size_a and size_b are less than
   or equal to zero.

   The function calls strcmp() to compare the strings.

   The function does not call any other function, not strcpy(), not
   strdup() not any other function!

   The pointers in the output array dst are the pointers in the input
   arrays. This means that the strings are not actually getting moved,
   just the pointers pointing to their first characters.

*/
void merge_sorted_arrays_of_strings(char *dst[],
				    char *a[], int size_a,
				    char *b[], int size_b) {
  int idx_dst, idx_a, idx_b;

  idx_dst = 0;
  idx_a = 0;
  idx_b = 0;
  while ((idx_a < size_a) && (idx_b < size_b)) {
    if (strcmp(a[idx_a], b[idx_b]) < 0) {
      dst[idx_dst] = a[idx_a];
      idx_a++;
    } else {
      dst[idx_dst] = b[idx_b];
      idx_b++;
    }
    idx_dst++;
  }
  while (idx_a < size_a) {
    dst[idx_dst] = a[idx_a];
    idx_a++;
    idx_dst++;
  }
  while (idx_b < size_b) {
    dst[idx_dst] = b[idx_b];
    idx_b++;
    idx_dst++;
  }
}

/* Sorts array of pointers of size n.

   The array gets sorted in the following way:

   * The pointers it contains in its different elements point to
     the first characters in arrays of characters, considered strings.

   * The strings are sorted in lexicographical order, i.e.  in the
     order induced by strcmp().

   The function is recursive, so it calls itself.

   The function also calls merge_sorted_arrays_of_strings() and
   copy_array_of_strings(). 

   The function does not call any other functions besides itself,
   merge_sorted_arrays_of_strings() and copy_array_of_strings().

   The pointers in the eventually sorted array are the pointers in the
   original array. This means that the strings are not actually
   getting moved, just the pointers pointing to their first
   characters.

   The function implements the Merge Sort algorithm.

   The function uses a temporary array of n pointers to
   characters. Such a dynamically sized array of n elements requires
   the use of a C99-compliant C compiler.

   The function works correctly for all possible sizes of n. In
   particular, the function does nothing if n is negative. The
   function works for odd sizes n, when the two subarrays used by the
   merge sort algorithm cannot be equally sized.

*/
void sort_array_of_strings(char *array[], int n) {
  int n_left, n_right;
  char **array_left, **array_right;
  char *temp[n];

  /* Base case: Nothing to sort if n <= 1 */
  if (n <= 1) return;

  /* Cut the array into sub-arrays */
  n_left = n / 2;
  n_right = n - n_left;
  array_left = array;
  array_right = &array[n_left];

  /* Recursive calls */
  sort_array_of_strings(array_left, n_left);
  sort_array_of_strings(array_right, n_right);

  /* Merge the sub-arrays */
  merge_sorted_arrays_of_strings(temp,
				 array_left, n_left,
				 array_right, n_right);

  /* Copy the temporary array into the original array */
  copy_array_of_strings(array, temp, n);
}


/* A main() to test the functions specified and coded above.

   No changes are needed here.

   This main() function uses a couple of C features students 
   might not know yet.

*/
int main(int argc, char **argv) {
  const int NUM_STRINGS = 10;
  const int BUF_LEN = 128;
  char raw_buffer[NUM_STRINGS * BUF_LEN];
  char *array[NUM_STRINGS];
  int i;

  /* Set up the array of strings */
  for (i=0;i<NUM_STRINGS;i++) {
    array[i] = &raw_buffer[i * BUF_LEN];
  }

  /* Get the strings from the user */
  input_array_of_strings(array, NUM_STRINGS, BUF_LEN);

  /* Print out the strings that the user entered */
  printf("You have entered the following strings:\n");
  print_array_of_strings(array, NUM_STRINGS);

  /* Sort the strings in the array in lexicographical order */
  sort_array_of_strings(array, NUM_STRINGS);

  /* Print out the strings in the sorted array */
  printf("The ordered list of strings is:\n");
  print_array_of_strings(array, NUM_STRINGS);
  
  return 0;
}
