#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cs220_paint.h"

unsigned char *read_image(const char *filename, int *width, int *height) {
  // open file for reading?
  FILE *in = fopen(filename, "rb");
  if (in == NULL) {
    return NULL;
  }

  // read image dimensions
  if (fscanf(in, "%d %d", width, height) != 2) {
    fclose(in);
    return NULL;
  }

  // allocate buffer for RGBA triples
  int num_vals = *width * *height * 3;
  unsigned char *buf = (unsigned char *) malloc(num_vals * sizeof(unsigned char));
  if (buf == NULL) {
    fclose(in);
    return NULL;
  }

  // read RGBA triples
  int error = 0;
  for (int i = 0; i < num_vals; i++) {
    unsigned val;
    if (fscanf(in, "%x", &val) != 1) {
      error = 1;
    } else {
      buf[i] = (unsigned char) val;
    }
  }

  // now can close input
  fclose(in);

  // if error, delete buffer and return NULL
  if (error) {
    free(buf);
    return NULL;
  }

  // return buffer
  return buf;
}

// Suggested helper functions to implement for drawing operations
// (initially commented-out: we encourage you to uncomment and
// implement them)

/*
int write_image(const char *filename, int width, int height, const unsigned char *buf) {
  // TODO: implement this function
}
*/

/*
double geom_dist(double x1, double y1, double x2, double y2) {
  // TODO: implement this function
}
*/

/*
void render_rectangle(unsigned char *pixel_data, int img_width, int img_height,
                      int rect_x, int rect_y, int rect_w, int rect_h,
                      int r, int g, int b) {
  // TODO: implement this function
}
*/

/*
void render_ellipse(unsigned char *pixel_data, int img_width, int img_height,
                      double x1, double y1, double x2, double y2, double len,
                      int r, int g, int b) {
  // TODO: implement this function
}
*/

/*
void flood_fill(unsigned char *pixel_data, int img_width, int img_height,
                int x, int y, int r, int g, int b) {
  // TODO: implement this function
}
*/

/*
void rec_flood_fill(unsigned char *pixel_data, int img_width, int img_height,
                    int x, int y,
                    int orig_r, int orig_g, int orig_b,
                    int r, int g, int b,
                    int dir) {
  // TODO: implement this function
}
*/
