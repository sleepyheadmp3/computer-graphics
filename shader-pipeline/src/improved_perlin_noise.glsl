// Given a 3d position as a seed, compute an even smoother procedural noise
// value. "Improving Noise" [Perlin 2002].
//
// Inputs:
//   st  3D seed
// Values between  -½ and ½ ?
//
// expects: random_direction, improved_smooth_step
float improved_perlin_noise(vec3 st) 
{
  // reference: https://adrianb.io/2014/08/09/perlinnoise.html
  // for any input 3D (seed) position, find the int grid cell that said point belongs to
  int xi = int(st.x) & 255;
  int yi = int(st.y) & 255;
  int zi = int(st.z) & 255;

  // wraps around so accounts for repeat (no line split)
  int xi_inc = (xi + 1) & 255;
  int yi_inc = (yi + 1) & 255;
  int zi_inc = (zi + 1) & 255;

  // generate random 3D vector directions at each of the corners of the cell
  vec3 aaa = random_direction(vec3(xi,  yi,  zi));
  vec3 aba = random_direction(vec3(xi,  yi_inc, zi));
  vec3 aab = random_direction(vec3(xi,  yi,  zi_inc));
  vec3 abb = random_direction(vec3(xi,  yi_inc, zi_inc));
  vec3 baa = random_direction(vec3(xi_inc, yi,  zi));
  vec3 bba = random_direction(vec3(xi_inc, yi_inc, zi));
  vec3 bab = random_direction(vec3(xi_inc, yi,  zi_inc));
  vec3 bbb = random_direction(vec3(xi_inc, yi_inc, zi_inc));

  // vectors from seed point -> corner
  float xf = st.x - floor(st.x);
  float yf = st.y - floor(st.y);
  float zf = st.z - floor(st.z);

  // smooth_step instead of fade function from ref
  float u = improved_smooth_step(xf);
  float v = improved_smooth_step(yf);
  float w = improved_smooth_step(zf);

  // take the dot products between the randomly generated vectors and the vectors from seed point -> each of the corners
  // interpolate between all these dot products using a smoothed step function
  float a, b, x1, x2, y1, y2;
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

  return y1 + w * (y2 - y1);
}

