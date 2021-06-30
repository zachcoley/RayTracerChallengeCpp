#ifndef ROTATION_MATRIX_H
#define ROTATION_MATRIX_H

#include <cmath>
#include "matrix4.h"
#include "point.h"
#include "vector.h"

class RotationMatrix : public Matrix4 {
 public:
  RotationMatrix(float x, float y, float z);
  float operator()(unsigned int y, unsigned int x) const override;
  Point operator*(const Point& other) const override;
  Vector operator*(const Vector& other) const;
  Matrix4 inverse() const;
 private:
  Matrix4 rotation_x_, rotation_y_, rotation_z_, result_;
};

#endif // ROTATION_MATRIX_H
