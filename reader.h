//Zichen Shi (zshi34)

#ifndef READER_H
#define READER_H

#include "expr_parser.h"
#include "plot.h"

class Reader {
private:
  // value semantics are prohibited
  Reader(const Reader &);
  Reader &operator=(const Reader &);
  ExprParser expr_parser;

public:
  Reader();
  ~Reader();

  // read plot description from given istream;
  // throw a PlotException if any errors are found
  void read_input(std::istream &in, Plot &plot);


  // helper functions to handle different input
  void read_plot(std::istream &in, Plot &plot);

  void read_function(std::istream &in, Plot &plot);

  void read_color(std::istream &in, Plot &plot);

  void read_fill(const std::string &op, std::istream &in, Plot &plot);

  // helper function to check missing color directive(s) or invalid data values
  // static bool check_color(const Color &c);

};

#endif // READER_H
