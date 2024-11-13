/*
        ============================================================================
        Name        : sobel.c
        Author      : kdesnos
        Version     : 1.2
        Copyright   : CECILL-C
        Description :
        ============================================================================
*/

#include "sobel.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

void sobel(int width, int height, unsigned char *input, unsigned char *output) {
    int i, j;
    // Ceci est un test
    //  Apply the averaging filter SOURCE CHAT-GPT FLEMME DE CODER CELA
    for (j = 1; j < height - 1; j++) {
        for (i = 1; i < width - 1; i++) {
            // Calculate the average of the 3x3 neighborhood
            int sum =
                input[(j - 1) * width + (i - 1)] + input[(j - 1) * width + i] +
                input[(j - 1) * width + (i + 1)] + input[j * width + (i - 1)] +
                input[j * width + i] + input[j * width + (i + 1)] +
                input[(j + 1) * width + (i - 1)] + input[(j + 1) * width + i] +
                input[(j + 1) * width + (i + 1)];
            output[j * width + i] = sum / 9;
        }
    }

    // Fill the left and right sides (optional, here we zero them)
    for (j = 0; j < height - 2; j++) {
        output[j * width] = 0;
        output[(j + 1) * width - 1] = 0;
    }
    /*
  // Apply the filter
  for (j = 1; j < height - 1; j++) {
    for (i = 1; i < width - 1; i++) {
      int gx = -input[(j - 1) * width + i + 1] - 2 * input[j * width + i - 1] -
               input[(j + 1) * width + i - 1] + input[(j - 1) * width + i + 1] +
               2 * input[j * width + i + 1] + input[(j + 1) * width + i + 1];
      int gy = -input[(j - 1) * width + i - 1] -
               2 * input[(j - 1) * width + i] - input[(j - 1) * width + i + 1] +
               input[(j + 1) * width + i - 1] + 2 * input[(j + 1) * width + i] +
               input[(j + 1) * width + i + 1];

      output[(j - 1) * width + i] = (gx * gx + gy * gy) / 8; // TODO

    }
  }

  // Fill the left and right sides
  for (j = 0; j < height - 2; j++) {
    output[j * width] = 0;
    output[(j + 1) * width - 1] = 0;
  }*/
}
