#include <stdio.h>

#define TESTNUM "11"

void test11_v( void )
{
  printf("Running Test #" TESTNUM ".\n");
}

int test11_i( void )
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 0;
}

float test11_f(void)
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 1.0f;
}
