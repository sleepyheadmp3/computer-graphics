#include "rgb_to_hsv.h"
#include <algorithm>
using namespace std;

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  double maxi = max({r, g, b});
  double mini = min({r, g, b});
  double c = maxi - mini;

  if (c == 0) {
    h = 0;
  }
  else if (maxi == r) {
    h = fmod(((g - b) / c), 6.0) * 60;
  }
  else if (maxi == g) {
    h = (((b - r) / c) + 2) * 60;
  }
  else {
    h = (((r - g) / c) + 4) * 60;
  }

  v = maxi;

  if (maxi == 0) {
    s = 0;
  }
  else {
    s = c / v;
  }
}
