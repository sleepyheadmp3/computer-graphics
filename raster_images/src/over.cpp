// Reference: https://en.wikipedia.org/wiki/Alpha_compositing

#include "over.h"

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());

  for (int i = 0; i < width*height*4; i += 4) {

    double alpha_a = A[i + 3] / 255.0;
    double alpha_b = B[i + 3] / 255.0;
    double alpha = alpha_a + (alpha_b * (1 - alpha_a));
    C[i + 3] = alpha * 255.0;

    double c_a, c_b;

    // rgb values
    for (int j = 0; j < 3; j++) {
      c_a = A[i + j];
      c_b = B[i + j];
      C[i + j] = ((c_a * alpha_a) + ((c_b * alpha_b) * (1 - alpha_a))) / alpha;
    }

  }
  
}
