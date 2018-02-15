
/*
 * generate_passphrase.c
 *
 * Generates random passphrases of lengths given from command line arguments.
 * This code uses the Diceware 8K word list in C, downloaded from
 *   http://world.std.com/%7Ereinhold/diceware.html
 *
 *
 * Command line arguments:
 *   <length1> - number of words to generate for pass phrase 1.
 *   [<length2>] - number of words to generate for pass phrase 2.
 *     ...
 *   [<lengthN>] - number of words to generate for pass phrase N.
 *
 *   Just keep adding numbers to the command line to generate as many pass
 *   phrases as you want.
 *
 * Author: E. Chris Pedro
 * Version: 2018-02-09
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "diceware8k.h"


/**
 * print_passphrase - Generates a random passphrase with <len> number of words.
 *                    This function resets the random seed by calling
 *                    srandomdev() each time it's called.
 * @len: the length of pass phrase in words, should be 4 or more
 */
void print_passphrase(int len)
{
  int i;
  long rand;

  if (len < 4)
  {
    printf("Passphrases should be 4 or more in length.\n");
    return;
  }

  srandomdev();
  for (i = 0; i < len; ++i)
  {
    do
      rand = random();
    while (rand < INT_MIN || rand > INT_MAX);

    if (i != 0)
      putchar(' ');

    printf("%s", getDiceWd(0 + rand));
  }

  putchar('\n');
}

/*
 * main
 */
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("usage: %s <length1> [<length2> ...]\n", argv[0]);
    return EXIT_FAILURE;
  }

  for (--argc, ++argv; argc; --argc, ++argv)
    print_passphrase(atoi(argv[0]));

  return EXIT_SUCCESS;
}

