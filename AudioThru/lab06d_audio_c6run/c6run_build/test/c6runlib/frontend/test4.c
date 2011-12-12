#include <stdio.h>

#define TESTNUM "4"

void test4_v( void )
{
  printf("Running Test #" TESTNUM ".\n");
}

int test4_i( void )
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 0;
}

float test4_f(void)
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 1.0f;
}
