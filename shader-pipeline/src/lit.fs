// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;

// Inputs:
in vec3 sphere_fs_in;   // 3D position _before_ applying model, view or projection
                        // transformations (e.g., point on unit sphere)

in vec3 normal_fs_in;   // view and model transformed 3D normal

in vec4 pos_fs_in;      // projected, view, and model transformed 3D position

in vec4 view_pos_fs_in; // view and model transformed 3D position

// Outputs:
out vec3 color;

// expects: PI, blinn_phong
void main()
{
  // equivalent to model()
  float theta = (M_PI / 3.0) * animation_seconds;
  float x_offset = 6.0;

  // view * rotate_about_y(theta) * translate(x_offset) * origin
  vec4 light_pos = view * vec4(x_offset * cos(theta), 6.0, x_offset * -sin(theta), 1.0);

  vec3 ka; 
  vec3 kd;
  vec3 ks;
  float p;
  vec3 n = normal_fs_in;
  vec3 v = normalize(-(view_pos_fs_in.xyz));
  vec3 l = normalize(light_pos - view_pos_fs_in).xyz;

  if (is_moon) {
    ka = vec3(0.10);
    kd = vec3(0.45);
    ks = vec3(0.80);
    p = 60.0;
  }
  else {
    ka = vec3(0.04, 0.08, 0.20);
    kd = vec3(0.15, 0.30, 0.80);
    ks = vec3(0.80);
    p = 80.0;
  }

  color = blinn_phong(ka, kd, ks, p, n, v, l);

}
