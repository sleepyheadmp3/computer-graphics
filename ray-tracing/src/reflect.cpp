#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  // reference: https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
  return in - 2 * in.dot(n) * n;
}
