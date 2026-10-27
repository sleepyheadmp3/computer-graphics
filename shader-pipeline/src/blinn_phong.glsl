// Compute Blinn-Phong Shading given a material specification, a point on a
// surface and a light direction. Assume the light is white and has a low
// ambient intensity.
//
// Inputs:
//   ka  rgb ambient color
//   kd  rgb diffuse color
//   ks  rgb specular color
//   p  specular exponent (shininess)
//   n  unit surface normal direction
//   v  unit direction from point on object to eye
//   l  unit light direction
// Returns rgb color
vec3 blinn_phong(
  vec3 ka,
  vec3 kd,
  vec3 ks,
  float p,
  vec3 n,
  vec3 v,
  vec3 l)
{
  // L = ambient + lambertian + specular
  vec3 rgb = ka * 0.1;

  // lambertian shading: kd * max(0, n.dot(l))
  rgb += kd * max(0, dot(n, l));

  // specular shading: ks * max(0, cos(n, h))^p
  // h = halfway vector btwn point -> light and point -> viewer
  vec3 h = normalize(l + v);

  rgb += ks * pow(max(0, dot(n, h)), p);

  return rgb;
}


