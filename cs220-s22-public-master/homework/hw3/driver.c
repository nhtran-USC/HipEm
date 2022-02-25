#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cs220_paint.h"

int main(int argc, char *argv[]) {
  // TODO: check that correct number of command line arguments were passed
  // report error if not

  const char *in_filename, *out_filename;
  // TODO: get command line arguments

  // TODO: open input file

  // TODO: read header (width and height) from input file

  // TODO: allocate pixel buffer, and set every pixel
  // to be black

  // TODO: process commands, call helper functions
  // to perform drawing operations

  int error = 0;
  char command;

  int rc = fscanf(in, " %c", &command); // read first command

  while (!error && rc != EOF) {
    switch (command) {
    case 'c':   // set current color
      {
        // TODO: implement
      }
      break;

    case 'r':   // rectangle
      {
        // TODO: implement
      }
      break;

    case 'e':   // ellipse
      {
        // TODO: implement
      }
      break;

    case 'f':   // flood fill
      {
        // TODO: implement
      }
      break;

    default:    // unknown command
      printf("Error: Unknown command '%c'\n", command);
      error = 1;
      break;
    }

    if (!error) {
      rc = fscanf(in, " %c", &command); // read next command
    }
  }

  // TODO: close input file

  // TODO: if an error occurred while processing commands, report it

  // TODO: try to write output file by calling write_image

  // TODO: if output couldn't be written, report error

  printf("Success\n");

  return 0;
}
