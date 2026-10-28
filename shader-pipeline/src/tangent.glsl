// Given a (normal) vector, find any two other vectors that are orthogonal to it and to each other
// Input:
//   N  3D unit normal vector
// Outputs:
//   T  3D unit tangent vector
//   B  3D unit bitangent vector
void tangent(in vec3 N, out vec3 T, out vec3 B)
{
  T = vec3(1,0,0);
  B = vec3(0,1,0);

  // use axis further from N
  if (abs(N.x) >= 0.95) {
    T = normalize(cross(B, N));
    B = normalize(cross(N, T));
  }
  else {
    B = normalize(cross(N, T));
    T = normalize(cross(B, N));
  }
}
