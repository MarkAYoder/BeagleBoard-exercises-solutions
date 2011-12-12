#include <stdio.h>

#define TESTNUM "9"

short test9_s( void )
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 1;
}

long long test9_ll( void )
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 0;
}

double test9_d(void)
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 1.0;
}
