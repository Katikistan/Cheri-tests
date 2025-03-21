#include <stdio.h>
#include <stdlib.h>
#include <cheriintrin.h> // Include this header before cheri.h to avoid issues with macros
#include <cheri/cheri.h>

int main() {
    int * __capability cap_ptr;
    int *ptr = malloc(sizeof(int));

    *ptr = 42;

    // Create a capability for the allocated memory with load and store permissions
    cap_ptr = (int* __capability)cheri_perms_and(ptr, CHERI_PERM_LOAD);

    // Access and modify the value through the capability
    printf("Value before: %d\n", *ptr);
    printf("ptr %#p\n", cap_ptr);
    *cap_ptr = 84;
    printf("Value after: %d\n", *ptr);

    free(ptr);

    return EXIT_SUCCESS;
}
