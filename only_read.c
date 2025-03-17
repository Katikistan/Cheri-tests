#include <stdio.h>
#include <stdlib.h>
#include <cheri/cheric.h>


int main(void) {
    void * __capability cap_variable = cheri_from_address(&variable, sizeof(variable));

    // Set the capability permissions to read-only
    cap_variable = cheri_perms_and(cap_variable, CHERI_PERM_LOAD);

    printf("Capability: %p#\n", ptr);
    printf("Capability: %p#\n", cap);

    
    
    return 0;
}
