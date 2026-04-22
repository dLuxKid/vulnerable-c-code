#include <stdio.h>
#include <string.h>

void access_granted() {
  printf("\n====================================\n");
  printf("ACCESS GRANTED - Welcome, authorized user!\n");
  printf("====================================\n\n");
}

void access_denied() {
  printf("\n====================================\n");
  printf("ACCESS DENIED - Incorrect password.\n");
  printf("====================================\n\n");
}

int main() {
  // Fixed: Larger buffer with extra space for safety
  char password[32];     // Much safer size (32 bytes)
  int authenticated = 0; // Authentication flag

  printf("=== Secure Login System ===\n");
  printf("Enter your password (max 31 characters): ");

  // FIXED: Use fgets() instead of gets()
  // fgets() prevents buffer overflow by limiting input size
  if (fgets(password, sizeof(password), stdin) == NULL) {
    printf("Error reading input.\n");
    return 1;
  }

  // Remove the newline character that fgets() includes
  password[strcspn(password, "\n")] = '\0';

  printf("\nPassword received.\n");

  // Simple password check (for demonstration)
  if (strcmp(password, "letmein") == 0) {
    authenticated = 1;
  }

  // Check authentication
  if (authenticated == 1) {
    access_granted();
  } else {
    access_denied();
  }

  return 0;
}