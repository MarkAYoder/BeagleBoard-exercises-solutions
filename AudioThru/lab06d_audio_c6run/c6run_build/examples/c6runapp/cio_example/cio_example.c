/*
 * cio_example.c
 */

/*
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
 */

/* 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void do_math();
static void do_file(); 

//-----------------------------------------------------------------------------
// USER_MAIN - User code goes here
//-----------------------------------------------------------------------------
int main()
{
  char option,cont;

  do
  {
    printf("\n\nWhat operation do you want to do (enter the number)? \n");
    printf("\t1. Test Simple Math\n");
    printf("\t2. Test Simple File I/O\n");
    fflush(stdout);
    option = getchar();
    while (getchar() != '\n');

    switch(option)
    {
      case '1':
        do_math();
        break;
      case '2':
        do_file();
        break;
      default:
        printf("Unknown option (%d) selected\n", option);
        break;
    }
    printf("Would you like to go again (y/n)?\n");
    fflush(stdout);
    cont = getchar();
    while (getchar() != '\n');
  }
  while((cont == 'y') || (cont == 'Y'));
    
  return 0;
}

/* Does simple math operations based on user input and outputs the
 * result to the console.
 */
static void do_math()
{
  int x, y, result;
  char c;

  //Doing a simple math library here
  printf("\nChose a math operation to perform:\n");
  printf("\t+\n");
  printf("\t-\n");
  printf("\t*\n");
  printf("\t/\n");
  printf("\t%%\n");
  printf("Choice: \n");
  fflush(stdout);
  c = getchar();
  while (getchar() != '\n');

  /* Error check the input */
  switch(c)
  {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
      break;
    default:
      printf("Unknown option (%c) selected\n", c);
      return;
  }

  printf("\nOperation will be x%cy\n", c);
  printf("Enter the value for x: \n");
  fflush(stdout);
  scanf("%d", &x);
  while (getchar() != '\n');
  printf("Enter the value for y: \n");
  fflush(stdout);  
  scanf("%d", &y);
  while (getchar() != '\n');

  switch(c)
  {
    case '+':
        result = x + y;
        break;
    case '-':
        result = x - y;
        break;
    case '*':
        result = x * y;
        break;
    case '/':
        result = x / y;
        break;
    case '%':
        result = x % y;
        break;
  }

  printf("\nThe result is %d\n\n\n", result);
  return;
}

/* Reads input from a file and can either leave it alone or reverse
 * the file contents.  User can select whether output should be to 
 * stdout or to another file.
 */
static void do_file()
{
  int len, i;
  char in_file[256], out_file[256];
  char option, out_option;
  int size;
  char *buf = NULL;
  FILE *in = NULL;
  FILE *out = NULL;;

  printf("\nWhat operation do you want to do to this file?\n");
  printf("\t1. Read/Print contents\n");
  printf("\t2. Reverse contents\n");
  fflush(stdout);
  option = getchar();
  while (getchar() != '\n');

  if ((option < '1') || (option > '2'))
  {
    printf("Unknown Option (%d) selected\n", option);
    return;
  }

  printf("\ninput file name: \n");
  if (fgets(in_file, sizeof in_file, stdin))
  {
    len = strlen(in_file) - 1;
    if (in_file[len] == '\n')
    {
      in_file[len] = '\0';
    }
  }

  printf("Where would you like the results written?\n");
  printf("\t1. stdout\n");
  printf("\t2. output file\n");
  fflush(stdout);
  out_option = getchar();
  while (getchar() != '\n');  

  switch(out_option)
  {
    case '1':
      break;
    case '2':
      printf("\noutput file name: \n");
      if (fgets(out_file, sizeof out_file, stdin))
      {
        len = strlen(out_file) - 1;
        if (out_file[len] == '\n')
        {
          out_file[len] = '\0';
        }
      }

      if ((out = fopen(out_file, "w+")) == NULL)
      {
        printf("Could not open output file\n");
        goto error;
      }
      break;
    default:
      printf("Option Unknown (%d) selected\n", out_option);
      return;
  }

  if ((in = fopen(in_file, "rw")) == NULL)
  {
    printf("Could not open input file\n");
    goto error;
  }

  fseek(in, 0, SEEK_END);
  size = ftell(in);
  fseek(in, 0, SEEK_SET);
  buf = malloc(size * sizeof(char));

  if (buf == NULL)
  {
    printf("Could not allocate buffer of size %d.  Try a smaller file\n", size);
    goto error;
  }

  buf[size - 1] = '\0';
  size--;

  //Are we reversing the file contents?
  if (option == '2')
  {
    for(i=size-1; i >= 0; i--)
    {
      buf[i] = fgetc(in);
    }
  } 
  else
  {
    for(i=0; i <= size-1; i++)
    {
        buf[i] = fgetc(in);
    }
  }

  if(out)
  {
    fprintf(out, "%s", buf);
    fprintf(out, "%c", EOF);
  } 
  else
  {
    printf("Output: %s\n", buf);
  }

error:
  if (buf)
  {
    free(buf);
  }
  if (in)
  {
    fclose(in);
  }
  if (out)
  {
    fclose(out);
  }
  return;
}
