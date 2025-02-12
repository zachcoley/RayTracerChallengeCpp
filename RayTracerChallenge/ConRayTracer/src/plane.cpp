   #include "plane.h"
#include "vector.h"
#include "point.h"


Plane::Plane() : Shape("plane", ObjectType::kPlane) {}

Plane::Plane(const std::string& name) : Shape(name, ObjectType::kPlane) {}

Plane::Plane(const std::string& name, const Material& material)
  : Shape(name, ObjectType::kPlane, material) {}

Plane::Plane(const std::string& name, const Matrix4& transform)
  : Shape(name, ObjectType::kPlane, transform) {}

Plane::Plane(const std::string& name, const Material& material, const Matrix4& transform)
  : Shape(name, ObjectType::kPlane, material, transform) {}

bool Plane::operator==(const Object& object) const {
  Plane* other = (Plane*)&object;
  return(name_ == other->GetName() &&
    transform_ == other->GetTransform() &&
    type_ == other->GetObjectType() &&
    id_ == other->GetID() &&
    material_ == other->GetMaterial() &&
    parent_ == other->GetParent());
}

Plane& Plane::operator=(const Object& object) {
  Plane* other = (Plane*)&object;
  name_ = other->GetName();
  type_ = other->GetObjectType();
  transform_ = other->GetTransform();
  material_ = other->GetMaterial();
  parent_ = other->GetParent();
  return *this;
}

std::vector<Intersection> Plane::local_intersect(const utils::RayStruct& local_ray) {
  std::vector<Intersection> intersections;
  if (abs(local_ray.direction[1]) < utils::kEPSILON) {
    return intersections; // empty set -- no intersections
  }

  // remaining intersection logic goes here
  float t = -local_ray.origin[1] / local_ray.direction[1];
  return { Intersection(t, this) };
}

Vector Plane::local_normal_at(const Point& local_point, const Intersection& hit) const {
  Vector local_normal = Vector(0, 1, 0);
  return local_normal.normalize();
}

BoundingBox Plane::bounds() const {
  return BoundingBox(Point(-utils::kINFINITY, -0.1f, -utils::kINFINITY), Point(utils::kINFINITY, 0.1f, utils::kINFINITY));;
}
