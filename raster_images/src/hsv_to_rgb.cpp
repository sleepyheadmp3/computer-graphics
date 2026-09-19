#include "hsv_to_rgb.h"
#include <cmath>
using namespace std;

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  double c = v * s;
  double h_prime = h / 60;
  double x = c * (1 - fabs((fmod(h_prime, 2) - 1)));

  if (h_prime < 1) {
    r = c;
    g = x;
    b = 0;
  }
  else if (h_prime < 2) {
    r = x;
    g = c;
    b = 0;
  }
  else if (h_prime < 3) {
    r = 0;
    g = c;
    b = x;
  }
  else if (h_prime < 4) {
    r = 0;
    g = x;
    b = c;
  }
  else if (h_prime < 5) {
    r = x;
    g = 0;
    b = c;
  }
  else if (h_prime < 6) {
    r = c;
    g = 0;
    b = x;
  }

  double m = v - c;
  r += m;
  g += m;
  b += m;
}
