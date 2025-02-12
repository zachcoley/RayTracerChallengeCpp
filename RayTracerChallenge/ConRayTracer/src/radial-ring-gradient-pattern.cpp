#include "radial-ring-gradient-pattern.h"

RadialRingGradientPattern::RadialRingGradientPattern(const Color& a, const Color& b)
  : Pattern(a, b) {}

Color RadialRingGradientPattern::pattern_at(const Point& point) {
  auto a_variant = this->GetA();
  auto b_variant = this->GetB();
  Color colorA = (*(std::get_if<Color>(&a_variant)));
  Color colorB = (*(std::get_if<Color>(&b_variant)));

  Color distance = colorB - colorA;
  float fraction = sqrt(pow(point[0], 2) + pow(point[2], 2)) - floor(sqrt(pow(point[0], 2) + pow(point[2], 2)));
  return colorA + distance * fraction;
}