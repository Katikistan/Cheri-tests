#include <stdio.h>
#include <cheriintrin.h>

int main(void) {
    int variable;
    void *capability = &variable;

    printf("Capability details:\n");
    printf("  Address: %p\n", capability);
    printf("  Address: %#p\n", capability);
    printf("  Base: %lu\n", cheri_base_get(capability));
    printf("  Length: %lu\n", cheri_length_get(capability));
    printf("  Offset: %lu\n", cheri_offset_get(capability));
    printf("  Permissions: 0x%x\n", cheri_perms_get(capability));

    return 0;
}

