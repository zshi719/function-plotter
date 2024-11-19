//Zichen Shi (zshi34)

#ifndef PLOT_H
#define PLOT_H

#include <vector>
#include <map>
#include <string>
#include "bounds.h"
#include "image.h"
#include "func.h"
#include "fill.h"

// Plot is a series of directives separated by at least one whitespace character.
class Plot {
private:
  // functions to be plotted
  std::vector<Function *> func_list;
  
  // plot bounds
  Bounds bounds;

  // vector of fill directives
  std::vector<Fill *> fill_list;

  // color
  std::map<std::string, Color> func_color;

  // value semantics are prohibited
  Plot(const Plot &);
  Plot &operator=(const Plot &);

public:
  Plot();
  ~Plot();

  // set and modify plot data
  int get_width() const;

  int get_height() const;

  const std::vector<Fill *> &get_fill_list() const;

  const std::vector<Function *> &get_func_list() const;

  const Bounds &get_bounds() const;

  void set_bounds(double xmin, double xmax, double ymin, double ymax, int width, int height);

  void insert_function(Function *func);

  void insert_fill(Fill *fill);

  void set_func_color(const std::string &name, Color color);

  Function *get_func(const std::string &func_name) const;

  const Color &get_func_color(const std::string &func_name) const;
};

#endif // PLOT_H
