#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  int i = 0;

  for (int col = width - 1; col >= 0; col--) {
    for (int row = 0; row < height; row++) {
      for (int cha = 0; cha < num_channels; cha++) {
        rotated[i] = input[((row*width) + col)*num_channels + cha];
        i++;
      }
    }
  }
}
