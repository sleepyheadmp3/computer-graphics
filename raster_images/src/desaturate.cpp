#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());

  double r, g, b, h, s, v;

  for (int i = 0; i < width*height*3; i += 3) {
    r = rgb[i] / 255.0;
    g = rgb[i + 1] / 255.0;
    b = rgb[i + 2] / 255.0;
    rgb_to_hsv(r, g, b, h, s, v);

    s -= s * factor;

    hsv_to_rgb(h, s, v, r, g, b);
    desaturated[i] = r * 255.0;
    desaturated[i + 1] = g * 255.0;
    desaturated[i + 2] = b * 255.0;
  }


}
