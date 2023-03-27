//Zichen Shi (zshi34)

#ifndef RENDERER_H
#define RENDERER_H

#include "plot.h"
#include "image.h"

class Renderer {
private:
  // it's convenient to have these as fields, to avoid the need
  // to pass them explicitly to helper functions
  const Plot &m_plot;
  Image *m_img;

  // value semantics prohibited
  Renderer(const Renderer &);
  Renderer &operator=(const Renderer &);

  // private helper functions
  void render_fill(const std::vector<double> &x_list, Fill *fill);
  void render_function(const std::vector<double> &x_list, Function *func);

public:
  Renderer(const Plot &plot);
  ~Renderer();

  Image *render();
  
};

#endif // RENDERER_H
