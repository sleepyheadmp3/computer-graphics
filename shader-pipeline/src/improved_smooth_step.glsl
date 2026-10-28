// Filter an input value to perform an even smoother step. This function should
// be a quintic polynomial with improved_smooth_step(0) = 0,
// improved_smooth_step(1) = 1, and zero first _and_ second derivatives at f=0
// and f=1. "Improving Noise" [Perlin 2002].
//
// Inputs:
//   f  input value
// Returns filtered output value
float improved_smooth_step( float f)
{
  // reference: fade function from https://adrianb.io/2014/08/09/perlinnoise.html
  if (f <= 0) {
    return 0.0;
  }

  if (f >= 1) {
    return 1.0;
  }

  // 6t^5 - 15t^4 + 10t^3
  return f * f * f * (f * (f * 6 - 15) + 10);
}

vec3 improved_smooth_step( vec3 f)
{
  return vec3(improved_smooth_step(f.x), 
    improved_smooth_step(f.y), 
    improved_smooth_step(f.z));
}
