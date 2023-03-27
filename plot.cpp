//Zichen Shi (zshi34)

#include <cassert>
#include "plot.h"
#include  "exception.h"

Plot::Plot() { }

Plot::~Plot() {
    for (Function *p: func_list) {
        delete p;
    }

    for (Fill *fill: fill_list) {
        delete fill;
    }
}

int Plot::get_width() const {
    return bounds.get_width();
}

int Plot::get_height() const {
    return bounds.get_height();
}

void Plot::set_bounds(double xmin, double xmax, double ymin, double ymax, int width, int height) {
    this->bounds.init(xmin, xmax, ymin, ymax, width, height);
}

void Plot::insert_function(Function *func) {
    func_list.push_back(func);
}

void Plot::insert_fill(Fill *fill) {
    fill_list.push_back(fill);
}

void Plot::set_func_color(const std::string& name, Color color) {
    // enforce no more than one Color directive for a function
    if (func_color.count(name)){
        throw PlotException("more than 1 Color detected");
    }
    func_color[name] = color;
}

Function *Plot::get_func(const std::string& func_name) const {
    for (Function *func: func_list) {
        if (func->get_name() == func_name) {
            return func;
        }
    }
    return nullptr;
}

const std::vector<Fill *> &Plot::get_fill_list() const {
    return fill_list;
}

const Bounds &Plot::get_bounds() const {
    return bounds;
}

const Color &Plot::get_func_color(const std::string& func_name) const {
    return func_color.at(func_name);
}

const std::vector<Function *> &Plot::get_func_list() const {
    return func_list;
}