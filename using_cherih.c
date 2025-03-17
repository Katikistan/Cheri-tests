#include <stdio.h>
#include <stdlib.h>
#include <cheriintrin.h> // Include this header for CHERI intrinsics
#include <cheri/cheri.h>

int main() {
    int * __capability cap_ptr;
    int *ptr = malloc(sizeof(int));

    *ptr = 42;

    // Create a capability for the allocated memory with load and store permissions
    cap_ptr = (int* __capability)cheri_perms_and(ptr, CHERI_PERM_LOAD | CHERI_PERM_STORE);

    // Access and modify the value through the capability
    printf("Value before: %d\n", *ptr);
    *cap_ptr = 84;
    printf("Value after: %d\n", *ptr);

    free(ptr);

    return EXIT_SUCCESS;
}
