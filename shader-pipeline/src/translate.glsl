// Inputs:
//   t  3D vector by which to translate
// Return a 4x4 matrix that translates a 3D point by the given 3D vector
mat4 translate(vec3 t)
{
  return mat4(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    t[0], t[1], t[2], 1
  );
}

