// Set the pixel color using Blinn-Phong shading (e.g., with constant blue and
// gray material color) with a bumpy texture.
// 
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
//                     linearly interpolated from tessellation evaluation shader
//                     output
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
//               rgb color of this pixel
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
  // from procedural_color.fs
  float theta = (M_PI / 3.0) * -animation_seconds;
  float x_offset = 6.0;
  vec4 light_pos = view * vec4(x_offset * cos(theta), 6.0, x_offset * -sin(theta), 1.0);

  vec3 T, B;
  vec3 N = normalize(sphere_fs_in);
  tangent(N, T, B);

  // reference: https://en.wikipedia.org/wiki/Bump_mapping
  // 1) find height of position on surface
  float h = bump_height(is_moon, sphere_fs_in);

  // 2) calculate surface normal using finte differences
  float e = 0.001;
  float d_T = (bump_height(is_moon, sphere_fs_in + e * T) - h) / e;  // slope along T after shifting by e
  float d_B = (bump_height(is_moon, sphere_fs_in + e * B) - h) / e;

  // 3) combine surface normal w/ geometric normal
  vec3 bump_normal = normalize(N - (d_T * T) - (d_B * B));

  vec3 ka; 
  vec3 kd;
  vec3 ks;
  float p;
  vec3 n = bump_normal;
  vec3 v = normalize(-(view_pos_fs_in.xyz));
  vec3 l = normalize(light_pos - view_pos_fs_in).xyz;

  float p_noise;
  vec3 x, y, st;

  if (is_moon) {
    st = 3.0 * sphere_fs_in;

    x = vec3(0.25);
    y = vec3(0.67);
    ka = vec3(0.10);
    kd = mix(x, y, p_noise);
    ks = vec3(0.80);
    p = 60.0;
  }
  else {
    st = 10.0 * sphere_fs_in;

    x = vec3(0.10, 0.25, 0.75);
    y  = vec3(0.20, 0.60, 0.25);
    ka = vec3(0.9, 0.9, 0.9);
    kd = vec3(0.15, 0.30, 0.80);
    ks = vec3(0.80);
    p = 80.0;
  }

  p_noise = 0.5 + 0.5 * improved_perlin_noise(st);
  kd = mix(x, y, p_noise);

  color = blinn_phong(ka, kd, ks, p, n, v, l);
}
