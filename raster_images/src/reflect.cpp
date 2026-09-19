#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);

  int i = 0;

  for (int row = 0; row < height; row++) {
    // columns reversed to reflect horizontally
    for (int col = width - 1; col >= 0; col--) {
      for (int cha = 0; cha < num_channels; cha++) {
        reflected[i] = input[((row*width) + col)*num_channels + cha];
        i++;
      }
    }
  }
}
