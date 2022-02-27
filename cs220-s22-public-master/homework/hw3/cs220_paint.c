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
    printf("ERROR");
    return 0;
  }

  fprintf(out, "%d ", width);
  fprintf(out, "%d\n", height);

  int num_vals = width * height * 3;

  for(int i = 0; i < num_vals; i++) {
    fprintf(out, "%x ", buf[i]);
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
  int x = 0;
  int y = 0;
  // Do lâu lâu ông thầy đặtc cái chiều dài của rect quá cái img_width với height nên ảnh nó bị tràn qua. này 
  // ta giớ hạn nó lại nếu quá gioi hạn thì ko vẽ thêm gì hết
  for (int i = rect_y; i < rect_y + rect_h; i++) {
    if(i >= img_height) {
      y = img_height - 1;
    }
    else {
      y = i;
    }
    for (int j = rect_x; j < rect_x + rect_w; j++) {
      if(j >= img_width) {
        x = img_width - 1;
      }
      else {
        x = j;
      }
      pixel_data[point_r(x, y, img_width)] = r;
      pixel_data[point_g(x, y, img_width)] = g;
      pixel_data[point_b(x, y, img_width)] = b;
    }
  }
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
  double focal_point_dist = geom_dist(x1, y1, x2, y2);
  // double focal_point_dist = 0;
  double first_focal_to_pixel_dist = 0;
  double second_focal_to_pixel_dist = 0;
  double sum = 0;

  for(int y = 0; y < img_height; y++) {
    for(int x = 0; x < img_width; x++) {
      first_focal_to_pixel_dist = geom_dist(x, y, x1, y1);
      second_focal_to_pixel_dist = geom_dist(x, y, x2, y2);
      sum = first_focal_to_pixel_dist + second_focal_to_pixel_dist + focal_point_dist;
      if(sum <= len) {
        pixel_data[point_r(x, y, img_width)] = r;
        pixel_data[point_g(x, y, img_width)] = g;
        pixel_data[point_b(x, y, img_width)] = b;
      }
    }
  }
}



void flood_fill(unsigned char *pixel_data, int img_width, int img_height,
                int x, int y, int r, int g, int b) {
  // TODO: implement this function
  int orig_r = pixel_data[point_r(x, y, img_width)];
  int orig_g = pixel_data[point_g(x, y, img_width)];
  int orig_b = pixel_data[point_b(x, y, img_width)];
  rec_flood_fill(pixel_data, img_width, img_height, x, y, orig_r, orig_g, orig_b, r, g, b, 1);
}

void rec_flood_fill(unsigned char *pixel_data, int img_width, int img_height,
                    int x, int y,
                    int orig_r, int orig_g, int orig_b,
                    int r, int g, int b,
                    int dir) {
  // TODO: implement this function
  // printf("recurse\n");

  // base case  BOUND
  // printf("x = %d y = %d\n", x, y);
  if(x > img_width - 1 || y > img_height - 1 ) {
    // printf("QUIT BOUND\n");
    return;
  }
  
  int current_r = pixel_data[point_r(x,y, img_width)];
  int current_g = pixel_data[point_g(x,y, img_width)];
  int current_b = pixel_data[point_b(x,y, img_width)];

  // printf("orig_r: %d current_r: %d\n", orig_r, current_r);
  // printf("orig_b: %d current_b: %d\n", orig_b, current_b);
  // printf("orig_g: %d current_g: %d\n", orig_g, current_g);

  // base case color 
  if((orig_r != current_r) || (orig_g != current_g) || (orig_b != current_b)) {
    // printf("QUIT COLOR\n");
    return;
  }

  // coloring
  pixel_data[point_r(x,y, img_width)] = r;
  pixel_data[point_b(x,y, img_width)] = b;
  pixel_data[point_g(x,y, img_width)] = g;
  // recusrion 
  rec_flood_fill(pixel_data, img_width, img_height, x + 1, y, orig_r, orig_g, orig_b, r, g, b, dir);
  rec_flood_fill(pixel_data, img_width, img_height, x, y + 1, orig_r, orig_g, orig_b, r, g, b, dir);
  rec_flood_fill(pixel_data, img_width, img_height, x - 1, y, orig_r, orig_g, orig_b, r, g, b, dir);
  rec_flood_fill(pixel_data, img_width, img_height, x, y - 1, orig_r, orig_g, orig_b, r, g, b, dir);

  rec_flood_fill(pixel_data, img_width, img_height, x + 1, y + 1, orig_r, orig_g, orig_b, r, g, b, dir);
  rec_flood_fill(pixel_data, img_width, img_height, x + 1, y - 1, orig_r, orig_g, orig_b, r, g, b, dir);
  rec_flood_fill(pixel_data, img_width, img_height, x - 1, y - 1, orig_r, orig_g, orig_b, r, g, b, dir);
  rec_flood_fill(pixel_data, img_width, img_height, x - 1, y + 1, orig_r, orig_g, orig_b, r, g, b, dir);
}


