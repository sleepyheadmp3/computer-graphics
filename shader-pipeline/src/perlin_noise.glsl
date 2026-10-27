// Given a 3d position as a seed, compute a smooth procedural noise
// value: "Perlin Noise", also known as "Gradient noise".
//
// Inputs:
//   st  3D seed
// Returns a smooth value between (-1,1)
//
// expects: random_direction, smooth_step
float perlin_noise(vec3 st) 
{
  // reference: https://adrianb.io/2014/08/09/perlinnoise.html
  // for any input 3D (seed) position, find the int grid cell that said point belongs to
  int xi = st.x & 255;
  int yi = st.y & 255;
  int zi = st.z & 255;

  // generate random 3D vector directions at each of the corners of the cell
  vec3 aaa = random_direction(vec3(xi, yi, zi));
  vec3 aba = random_direction(vec3(xi, yi + 1.0, zi));
  vec3 aab = random_direction(vec3(xi, yi, zi + 1.0));
  vec3 abb = random_direction(vec3(xi, yi + 1.0, zi + 1.0));
  vec3 baa = random_direction(vec3(xi + 1.0, yi, zi));
  vec3 bba = random_direction(vec3(xi + 1.0, yi + 1.0, zi));
  vec3 bab = random_direction(vec3(xi + 1.0, yi, zi + 1.0));
  vec3 bbb = random_direction(vec3(xi + 1.0, yi + 1.0, zi + 1.0));

  // vectors from seed point -> corner
  double xf = st.x - xi;
  double yf = st.y - yi;
  double zf = st.z - zi;

  // smooth_step instead of fade function from ref
  double u = smooth_step(xf);
  double v = smooth_step(yf);
  double w = smooth_step(zf);

  // take the dot products between the randomly generated vectors and the vectors from seed point -> each of the corners
  // interpolate between all these dot products using a smoothed step function
  double a, b, x1, x2, y1, y2;
  a = dot(aaa, vec3(xf, yf, zf));
  b = dot(baa, vec3(xf - 1.0, yf, zf));
  x1 = a + u * (b - a);

  a = dot(aba, vec3(xf, yf - 1.0, zf));
  b = dot(bba, vec3(xf - 1.0, yf - 1.0, zf));
  x2 = a + u * (b - a);

  y1 = x1 + v * (x2 - x1);

  a = dot(aab, vec3(xf, yf, zf - 1.0));
  b = dot(bab, vec3(xf - 1.0, yf, zf - 1.0));
  x1 = a + u * (b - a);

  a = dot(abb, vec3(xf, yf - 1.0, zf - 1.0));
  b = dot(bbb, vec3(xf - 1.0, yf - 1.0, zf - 1.0));
  x2 = a + u * (b - a);

  y2 = x1 + v * (x2 - x1);

  return ((y1 + w * (y2 - y1)) + 1) / 2;
}