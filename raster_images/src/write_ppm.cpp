// Reference: https://en.wikipedia.org/wiki/Netpbm#Description

#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels == 1) &&
    ".ppm only supports RGB or grayscale images");
  
  std::ofstream myfile;
  myfile.open (filename);

  if (!myfile) {
    return false;
  }

  if (num_channels == 3) {
    myfile << "P3\n";
  }
  else {
    myfile << "P2\n";
  }

  myfile << width << " " << height << "\n" << "255" << "\n";

  for (int i = 0; i < height*width*num_channels; i++) {
      myfile << (int)data[i] << " ";
  }

  myfile.close();
  return true;
}
