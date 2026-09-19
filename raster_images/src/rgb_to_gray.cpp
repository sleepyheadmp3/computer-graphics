#include "rgb_to_gray.h"

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);

  int j = 0;

  for (int i = 0; i < height*width*3; i += 3) {
    gray[j] = ((double)rgb[i] + 
              (double)rgb[i + 1] + 
              (double)rgb[i + 2])
              / 3;
    j++;
  }

  // TODO: 15 or 225??
}


