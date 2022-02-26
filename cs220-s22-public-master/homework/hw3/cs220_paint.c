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


int write_image(const char *filename, int width, int height, const unsigned char *buf) {
  // TODO: implement this function
  FILE *out = fopen(filename, "w");
  if (out == NULL) {
    printf("HEREE");
    return 0;
  }

  fprintf(out, "%d ", width);
  fprintf(out, "%d\n", height);

  int num_vals = width * height * 3;

  for(int i = 0; i < width * height * 3; i++) {
    fprintf(out, "%x ", buf[i]);
    fprintf(out, " ");
    if(i % 23 == 0 && i != 0) {
      fprintf(out, "\n");
    }
  }

  fclose(out);
  return 1;
}



double geom_dist(double x1, double y1, double x2, double y2) {
  // TODO: implement this function
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}



void render_rectangle(unsigned char *pixel_data, int img_width, int img_height,
                      int rect_x, int rect_y, int rect_w, int rect_h,
                      int r, int g, int b) {
  // TODO: implement this function
  // int startingPoint = 3 * rect_y * img_width + rect_x * 3;
  // for(int i = startingPoint; i < startingPoint + rect_h * img_width * 3; i+= img_width * 3) {
  //   if(i > startingPoint + img_height * img_width * 3) {
  //     i = startingPoint + img_height * img_width * 3 - 1;
  //   }
  //   for(int j = i; j < i + rect_w * 3; j+=3) {
  //     if(j > i + img_width * 3) {
  //       j = i + img_width * 3 - 1;
  //     }
  //     for(int k = j; k < j + 3; k++){
  //       if(k - j == 0) {
  //         pixel_data[k] = r;
  //       }
  //       else if(k - j == 1) {
  //         pixel_data[k] = g;
  //       }
  //       else {
  //         pixel_data[k] = b;
  //       }
  //     }
  //   }
  // }

  // printf("%d ", rect_x);
  // printf("%d", rect_h);
  for (int i = rect_y; i < rect_y + rect_h; i++) {
    
    for (int j = rect_x; j < rect_x + rect_w; j++) {
      pixel_data[point_r(j, i, img_width)] = r;
      pixel_data[point_g(j, i, img_width)] = g;
      pixel_data[point_b(j, i, img_width)] = b;
    }
  }
  // printf("HERERERER");
  // printf("%d", rect_h);
  // printf("%d", rect_w);

  // for ()
}

int point_r(int x, int y, int img_width) {
  return 3 * y * img_width + x * 3;
}
int point_b(int x, int y, int img_width) {
  return 3 * y * img_width + x * 3 + 1;
}
int point_g(int x, int y, int img_width) {
  return 3 * y * img_width + x * 3 + 2;
}

void render_ellipse(unsigned char *pixel_data, int img_width, int img_height,
                      double x1, double y1, double x2, double y2, double len,
                      int r, int g, int b) {
  // TODO: implement this function
}



void flood_fill(unsigned char *pixel_data, int img_width, int img_height,
                int x, int y, int r, int g, int b) {
  // TODO: implement this function

}



void rec_flood_fill(unsigned char *pixel_data, int img_width, int img_height,
                    int x, int y,
                    int orig_r, int orig_g, int orig_b,
                    int r, int g, int b,
                    int dir) {
  // TODO: implement this function
}

