// Create a bumpy surface by using procedural noise to generate a height (
// displacement in normal direction).
//
// Inputs:
//   is_moon  whether we're looking at the moon or centre planet
//   s  3D position of seed for noise generation
// Returns elevation adjust along normal (values between -0.1 and 0.1 are
//   reasonable.
float bump_height( bool is_moon, vec3 s)
{
  if (is_moon) {
    return 0.1 * improved_perlin_noise(s * 3.0);
  }
  else {
    // if (s.x < 0.5 && s.y > 0.5) {
    //   return 0.1 * improved_perlin_noise(s * 2.0);
    // }
    float p_noise = 0.5 + 0.5 * improved_perlin_noise(3.0 * s);

    // land is raised in same areas that are colored green
    float land = (p_noise - 0.5) / 0.06;
    if (land > 1.0) {
      land = 1.0;
    }
    if (land < 0.0) {
      land = 0.0;
    }

    return 0.1 * land;
  }
}
