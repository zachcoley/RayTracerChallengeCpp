#include "cube.h"
#include "utils.h"
#include <algorithm>

Cube::Cube()
  : Shape("cube", ObjectType::kCube) {}

Cube::Cube(const std::string& name)
  : Shape(name, ObjectType::kCube) {}

Cube::Cube(const std::string& name, const Material& material)
  : Shape(name, ObjectType::kCube, material) {}

Cube::Cube(const std::string& name, const Matrix4& transform)
  : Shape(name, ObjectType::kCube, transform) {}

Cube::Cube(const std::string& name, const Material& material, const Matrix4& transform)
  : Shape(name, ObjectType::kCube, material, transform) {}

bool Cube::operator==(const Object& object) {
  Cube* other = (Cube*)&object;
  return(this->GetName() == other->GetName() &&
    this->GetTransform() == other->GetTransform() &&
    this->GetObjectType() == other->GetObjectType() &&
    this->GetMaterial() == other->GetMaterial());
}

Cube& Cube::operator=(const Object& object) {
  Cube* other = (Cube*)&object;
  this->SetName(other->GetName());
  this->SetObjectType(other->GetObjectType());
  this->SetTransform(other->GetTransform());
  this->SetMaterial(other->GetMaterial());
  this->SetMaterial(other->GetMaterial());
  return *this;
}

std::vector<Intersection> Cube::local_intersect(const utils::RayStruct& local_ray) {
  utils::TimeValuePair x = utils::check_axis(local_ray.origin[0], local_ray.direction[0], -1, 1);
  utils::TimeValuePair y = utils::check_axis(local_ray.origin[1], local_ray.direction[1], -1, 1);
  utils::TimeValuePair z = utils::check_axis(local_ray.origin[2], local_ray.direction[2], -1, 1);

  const auto tmin = std::max({ x.tmin, y.tmin, z.tmin });
  const auto tmax = std::min({ x.tmax, y.tmax, z.tmax });

  if (tmin > tmax || tmax < 0) return {};

  return { Intersection(tmin, this), Intersection(tmax, this) };
}

Vector Cube::local_normal_at(const Point& local_point) const {
  const auto maxc = std::max({ abs(local_point[0]), abs(local_point[1]), abs(local_point[2]) });

  if (maxc == abs(local_point[0])) {
    return Vector(local_point[0], 0, 0);
  }
  else if (maxc == abs(local_point[1])) {
    return Vector(0, local_point[1], 0);
  }
  return Vector(0, 0, local_point[2]);
}

BoundingBox Cube::bounds() const {
  return BoundingBox(Point(-1, -1, -1), Point(1, 1, 1));
}