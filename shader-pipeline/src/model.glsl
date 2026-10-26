// Construct the model transformation matrix. The moon should orbit around the
// origin. The other object should stay still.
//
// Inputs:
//   is_moon  whether we're considering the moon
//   time  seconds on animation clock
// Returns affine model transformation as 4x4 matrix
//
// expects: identity, rotate_about_y, translate, PI
mat4 model(bool is_moon, float time)
{
  if (is_moon) {
    vec3 x_offset = vec3(2, 0, 0);

    // speed = 2 pi r / 4 sec
    float theta = (M_PI / 2.0) * time;

    return rotate_about_y(theta) * translate(x_offset);
  }

  return identity();
}
