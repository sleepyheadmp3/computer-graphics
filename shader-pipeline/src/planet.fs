// Generate a procedural planet and orbiting moon. Use layers of (improved)
// Perlin noise to generate planetary features such as vegetation, gaseous
// clouds, mountains, valleys, ice caps, rivers, oceans. Don't forget about the
// moon. Use `animation_seconds` in your noise input to create (periodic)
// temporal effects.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
  // from procedural_color.fs
  float theta = (M_PI / 3.0) * -animation_seconds;
  float x_offset = 6.0;
  vec4 light_pos = view * vec4(x_offset * cos(theta), 3.0, x_offset * -sin(theta), 1.0);

  vec3 T, B;
  vec3 N = normalize(sphere_fs_in);
  tangent(N, T, B);

  // from bump.fs
  float h = bump_height(is_moon, sphere_fs_in);
  float e = 0.001;
  float d_T = (bump_height(is_moon, sphere_fs_in + e * T) - h) / e;  // slope along T after shifting by e
  float d_B = (bump_height(is_moon, sphere_fs_in + e * B) - h) / e;
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

    // normalizes to (0, 1)
    p_noise = 0.5 + 0.5 * improved_perlin_noise(st);

    x = vec3(0.25);
    y = vec3(0.67);
    ka = vec3(0.10);
    kd = mix(x, y, p_noise);
    ks = vec3(0.80);
    p = 60.0;
  }
  else {
    st = 3.0 * sphere_fs_in;
    p_noise = 0.5 + 0.5 * improved_perlin_noise(st);

    vec3 water = vec3(0.10, 0.25, 0.75);
    vec3 green = vec3(0.20, 0.60, 0.25);

    // 0 in water, 1 on land
    float land = (p_noise - 0.5) / 0.06;
    if (land > 1.0) {
      land = 1.0;
    }
    if (land < 0.0) {
      land = 0.0;
    }

    // rivers
    float a = (M_PI / 3.0) * animation_seconds;
    vec3 rq = vec3(cos(a) * sphere_fs_in.x - sin(a) * sphere_fs_in.z,
                   sphere_fs_in.y,
                   sin(a) * sphere_fs_in.x + cos(a) * sphere_fs_in.z);
    if (sin(16.0 * improved_perlin_noise(rq)) > 0.9) {
      kd = vec3(0.0, 1.0, 1.0);
    }
    else {
      kd = mix(water, green, land);
    }

    ka = 0.2 * kd;
    ks = vec3(mix(0.80, 0.10, land));
    p = 80.0;
  }

  color = blinn_phong(ka, kd, ks, p, n, v, l);
}
