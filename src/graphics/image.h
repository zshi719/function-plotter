//Zichen Shi (zshi34)

#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <iostream>
#include "color.h"

class Image {
private:
  int m_width, m_height;
  Color *m_pixels;

  // value semantics are prohibited
  Image(const Image &);
  Image &operator=(const Image &);

public:
  Image(int width, int height);
  ~Image();

  int get_width() const { return m_width; }
  int get_height() const { return m_height; }

  // access pixel Color data
  Color *get_pixels() const;

  Color get(int x, int y) const;

  void set(int x, int y, Color color, int r = 0);

  int get_pos(int x, int y) const;

  void write_png(std::ostream &out);
};

#endif // IMAGE_H
