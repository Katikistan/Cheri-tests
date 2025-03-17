#include <stdio.h>
#include <stdlib.h>

int main() {
  void *x = (void *)malloc(1);
  printf("The address in this capability is %p\n", x);
  printf("The full capability (incl metadata) is %#p\n", x);
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