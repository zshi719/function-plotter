// Zichen Shi (zshi34)

#ifndef COLOR_H
#define COLOR_H

#include <iostream>

struct Color {
  uint8_t r, g, b;

  Color() {}

  Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
  
  // overload +
  Color operator+(const Color &o) const { return Color(r + o.r, g + o.g, b + o.b); }
  
  // overload *, adjust opacity of colors
  Color operator*(double o) const { return Color(o * r, o * g, o * b); }
};

// overload standard input >>
std::istream &operator>>(std::istream &in, Color &color);

#endif // COLOR_H

