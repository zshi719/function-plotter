// Zichen Shi (zshi34)

#include <cassert>
#include "fill.h"


Fill::Fill(double opacity, Color color) : opacity(opacity), color(color) {}

Fill::~Fill() {}


Color Fill::get_fill_color(Color old) const {
    return old * (1 - opacity) + color * opacity;
}


FillAbove::FillAbove(double opacity, Color color, Function *func) 
    : Fill(opacity, color), func(func) {

    }


bool FillAbove::get_fill_range(double x, double ymin, double ymax, double &range_min, double &range_max) const {
    double y = func->get_expr()->eval(x);
    if (y < ymin) {
        range_min = ymin;
        range_max = ymax;
        return true;
    }
    else if (y < ymax) {
        range_min = y;
        range_max = ymax;
        return true;
    }
    return false;
}

FillBelow::FillBelow(double opacity, Color color, Function *func) 
    : Fill(opacity, color), func(func) {
    }


bool FillBelow::get_fill_range(double x, double ymin, double ymax, double &range_min, double &range_max) const {
    double y = func->get_expr()->eval(x);
    if (y > ymax) {
        range_min = ymin;
        range_max = ymax;
        return true;
    }
    else if (y > ymin) {
        range_min = ymin;
        range_max = y;
        return true;
    }
    return false;
}

FillBetween::FillBetween(double opacity, Color color, Function *func1, Function *func2) 
    : Fill(opacity, color), func1(func1), func2(func2) {
    }


bool FillBetween::get_fill_range(double x, double ymin, double ymax, double &range_min, double &range_max) const {
    double y1 = func1->get_expr()->eval(x);
    double y2 = func2->get_expr()->eval(x);
    if (y1 > y2) {
        std::swap(y1, y2);
    }
    if (y2 >= ymin && y1 <= ymin) {
        range_min = ymin;
        range_max = y2;
        return true;
    }
    else if (y1 >= ymin && y2 <= ymax) {
        range_min = y1;
        range_max = y2;
        return true;
    }
    else if (y1 <= ymax && y2 >= ymax) {
        range_min = y1;
        range_max = ymax;
        return true;
    }
    return false;
}