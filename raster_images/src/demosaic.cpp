#include "demosaic.h"

#define GET_ACTUAL bayer[width * r + c]
#define GET_NORTH bayer[(r - 1) * width + c]
#define GET_SOUTH bayer[(r + 1) * width + c]
#define GET_EAST bayer[width * r + c + 1]
#define GET_WEST bayer[width * r + c - 1]
#define GET_NE bayer[(r - 1) * width + c + 1]
#define GET_NW bayer[(r - 1) * width + c - 1]
#define GET_SE bayer[(r + 1) * width + c - 1]
#define GET_SW bayer[(r + 1) * width + c + 1]


void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);

  int i = 0;
  
  for (int r = 0; r < height; r++) {
    for (int c = 0; c < width; c++, i += 3) {

      // green - blue row
      if (r % 2 == 0) {

        // green pixel
        if (c % 2 == 0) {
          rgb[i + 1] = GET_ACTUAL; 
        
          // first and last row greens
          if (r == 0) { 
            rgb[i] = GET_SOUTH;
          }
          else if (r == height - 1) {
            rgb[i] = GET_NORTH;
          }
          else {
            rgb[i] = (GET_NORTH + GET_SOUTH) / 2;
          }

          // left and right edge greens
          if (c == 0) {
            rgb[i + 2] = GET_EAST;
          }
          else if (c == width - 1) {
            rgb[i + 2] = GET_WEST;
          }
          else {
            rgb[i + 2] = (GET_WEST + GET_EAST) / 2;
          }
        }

        // blue pixel
        else {
          rgb[i + 2] = GET_ACTUAL; 

          // first row blues
          if (r == 0) { 

            // upper right corner blue
            if (c == width - 1) {
              rgb[i + 1] = (GET_WEST + GET_SOUTH) / 2;
              rgb[i] = GET_SW;
            }
            else {
              rgb[i + 1] = (GET_WEST + GET_SOUTH + GET_EAST) / 3;
              rgb[i] = (GET_SW + GET_SE) / 2;
            }
          }

          // last row blues
          else if (r == height - 1) {

            // bottom right corner blue
            if (c == width - 1) {
              rgb[i + 1] = (GET_WEST + GET_NORTH) / 2;
              rgb[i] = GET_NW;
            }
            else {
              rgb[i + 1] = (GET_WEST + GET_NORTH + GET_EAST) / 3;
              rgb[i] = (GET_NW + GET_NE) / 2;
            }
          }

          // right edge blues
          else if (c == width - 1) {
            rgb[i + 1] = (GET_WEST + GET_NORTH + GET_SOUTH) / 3;
            rgb[i] = (GET_NW + GET_SW) / 2;
          }

          else {
            rgb[i + 1] = (GET_EAST + GET_WEST + GET_NORTH + GET_SOUTH) / 4;
            rgb[i] = (GET_NW + GET_SW + GET_NE + GET_SE) / 4;
          }
        }
      }



      // red - green row
      else {

        // green pixel
        if (c % 2 == 1) {
          rgb[i + 1] = GET_ACTUAL; 

          // last row greens
          if (r == height - 1) {
            rgb[i + 2] = GET_NORTH;
          }
          else {
            rgb[i + 2] = (GET_NORTH + GET_SOUTH) / 2;
          }

          // right edge greens
          if (c == width - 1) {
            rgb[i] = GET_WEST;
          }
          else {
            rgb[i] = (GET_WEST + GET_EAST) / 2;
          }
        }

        // red pixel
        else {
          rgb[i] = GET_ACTUAL; 

          // last row reds
          if (r == height - 1) {

            // bottom corners red
            if (c == 0) {
              rgb[i + 1] = (GET_NORTH + GET_EAST) / 2;
              rgb[i + 2] = GET_NE;
            }
            else if (c == width - 1) {
              rgb[i + 1] = (GET_NORTH + GET_WEST) / 2;
              rgb[i + 2] = GET_NW;
            }
            else {
              rgb[i + 1] = (GET_WEST + GET_NORTH + GET_EAST) / 3;
              rgb[i + 2] = (GET_NW + GET_NE) / 2;
            }
          }

          // left edge reds
          else if (c == 0) {
            rgb[i + 1] = (GET_SOUTH + GET_NORTH + GET_EAST) / 3;
            rgb[i + 2] = (GET_NE + GET_SE) / 2;
          }

          // right edge reds
          else if (c == width - 1) {
            rgb[i + 1] = (GET_WEST + GET_NORTH + GET_SOUTH) / 3;
            rgb[i + 2] = (GET_NW + GET_SW) / 2;
          }

          else {
            rgb[i + 1] = (GET_EAST + GET_WEST + GET_NORTH + GET_SOUTH) / 4;
            rgb[i + 2] = (GET_NW + GET_SW + GET_NE + GET_SE) / 4;
          }
        }
      }
    }
  }
}
