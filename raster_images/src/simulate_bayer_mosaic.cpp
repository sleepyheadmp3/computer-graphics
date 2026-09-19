#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  int i = 0;
  
  for (int r = 0; r < height; r++) {
    for (int c = 0; c < width; c++, i++) {

      // green - blue - green - blue row
      if (r % 2 == 0) {
        if (c % 2 == 0) {
          bayer[i] = rgb[(width*r + c)*3 + 1];    // green value
        }
        else {
          bayer[i] = rgb[(width*r + c)*3 + 2];    // blue value
        }
      }

      // red - green - red - green row
      else {
        if (c % 2 == 0) {
          bayer[i] = rgb[(width*r + c)*3];    // red value
        }
        else {
          bayer[i] = rgb[(width*r + c)*3 + 1];    // green value
        }

      }
    }
  }
}
