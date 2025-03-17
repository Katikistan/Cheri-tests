#include <stdio.h>
#include <stdlib.h>
#include <cheriintrin.h> // Add this line
#include <cheri/cheri.h>


int main() {
    // Allocate memory for an array of 10 integers
    int * __capability cap_array;
    int *array = malloc(10 * sizeof(int));

    // Initialize the array
    for (int i = 0; i < 10; i++) {
        array[i] = i;
    }

    // Create a capability for the allocated memory with load permission
    cap_array = (int * __capability)cheri_perms_and(array, CHERI_PERM_LOAD);


    // Attempt to access an out-of-bounds element
    // This will cause a capability violation
    printf("Out-of-bounds access: %d\n", cap_array[10]);

    // Free the allocated memory
    free(array);

    return EXIT_SUCCESS;
}
