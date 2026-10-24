// Inputs:
//   s  amount to scale in all directions
// Return a 4x4 matrix that scales an input 3D position/vector by s in all 3
// directions.
mat4 uniform_scale(float s)
{
  vec4 scalar = vec4(s, s, s, 1);
  return identity() * scalar;
}

