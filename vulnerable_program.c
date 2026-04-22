#include <stdio.h>
#include <string.h>

void access_granted()
{
  printf("\n====================================\n");
  printf("ACCESS GRANTED - Welcome, authorized user!\n");
  printf("====================================\n\n");
}

void access_denied()
{
  printf("\n====================================\n");
  printf("ACCESS DENIED - Incorrect password.\n");
  printf("====================================\n\n");
}

int main()
{
  int authenticated = 0; // Flag that should stay 0 unless password is correct
  char password[8];      // Very small buffer (only 8 bytes)

  printf("=== Secure Login System (Demonstration) ===\n");
  printf("Enter your password (max 7 characters): ");

  // Dangerous: no bounds checking!
  // gets() is deprecated and unsafe - reads until newline without limit
  gets(password);

  printf("\nPassword received.\n");

  // Check authentication
  if (authenticated != 0)
  {
    access_granted();
  }
  else
  {
    access_denied();
  }

  return 0;
}