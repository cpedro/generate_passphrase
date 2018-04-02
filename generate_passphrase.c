
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
 *
 * MIT License
 *
 * Copyright (c) 2018 Chris Pedro
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


/*
 * getDiceWd - defined in diceware8k.c
 */
char *getDiceWd(int n);

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

