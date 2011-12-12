#include <stdio.h>

#define TESTNUM "9"

void test9_v( void )
{
  printf("Running Test #" TESTNUM ".\n");
}

int test9_i( void )
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 0;
}

float test9_f(void)
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 1.0f;
}
