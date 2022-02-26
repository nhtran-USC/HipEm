#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cs220_paint.h"

int main(int argc, char *argv[]) {
  // TODO: check that correct number of command line arguments were passed
  // report error if not
  if (argc != 3) {
    printf("Error: not correct argv :\n");
    return 1;
  }
  // TODO: get command line arguments
  const char *in_filename = argv[1];
  const char *out_filename = argv[2];
  // printf(argv[1]);
  // TODO: open input file
  FILE *in = fopen(in_filename, "rb");
  if (in == NULL) {
    printf("Fail to read cmd file\n");
    return 0;
  }
  // TODO: read header (width and height) from input file
  int width = 0;
  int height = 0;
  int num_vals = 0;
  if (fscanf(in, "%d %d", &width, &height) != 2) {
    fclose(in);
    return 0;
  }
  num_vals = width * height * 3;
  // TODO: allocate pixel buffer, and set every pixel
  // to be black
  unsigned char *buf = (unsigned char *) malloc(num_vals * sizeof(unsigned char));
  for(int i = 0; i < num_vals; i++) {
    buf[i] = 0;
  }
  // TODO: process commands, call helper functions
  // to perform drawing operations
  int error = 0;
  char command;
  int r = 0;
  int g = 0;
  int b = 0;
  int rc = fscanf(in, " %c", &command); // read first command

  while (!error && rc != EOF) {
    switch (command) {
    case 'c':   // set current color
      {
        // TODO: implement
        fscanf(in, "%d %d %d", &r, &g, &b); // read first command
        // printf( "%d %d %d \n", r, g, b);
      }
      break;

    case 'r':   // rectangle
      {
        // TODO: implement
        int rect_x = 0;
        int rect_y = 0;
        int rect_h = 0;
        int rect_w = 0;
        fscanf(in, "%d %d %d %d", &rect_x, &rect_y, &rect_w, &rect_h);
        render_rectangle(buf,width, height, rect_x, rect_y, rect_w, rect_h, r, g, b);
      }
      break;

    case 'e':   // ellipse
      {
        // TODO: implement
        double x1 = 0;
        double y1 = 0;
        double x2 = 0;
        double y2 = 0;
        double len = 0;
        fscanf(in, "%lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &len);
        render_ellipse(buf, width, height, x1, y1, x2, y2, len, r, g, b);
      }
      break;

    case 'f':   // flood fill
      {
        // TODO: implement
        int x = 0;
        int y = 0;
        fscanf(in, "%d %d", &x, &y);
        flood_fill(buf, width, height, x, y, r, g, b);
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
  fclose(in);
  // TODO: if an error occurred while processing commands, report it

  // TODO: try to write output file by calling write_image
  write_image(out_filename, width, height, buf);
  // TODO: if output couldn't be written, report error
  
  printf("Success\n");

  return 0;
}
