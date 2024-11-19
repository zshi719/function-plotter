//Zichen Shi (zshi34)

#include <iostream>
#include <map>
#include <sstream>
#include <cstdint>
#include <exception>
#include "exception.h"
#include "plot.h"
#include "reader.h"
#include "expr_parser.h"
#include "fill.h"

std::istream &operator>>(std::istream &in, Color &color) {
    int r, g, b; 
    if(!(in >> r >> g >> b)) {
        throw PlotException("invalid color directives!");
    }
    color.r = (int) r;
    color.g = (int) g;
    color.b = (int) b;
    return in;
}

Reader::Reader() {
}

Reader::~Reader() {
}

void Reader::read_input(std::istream &in, Plot &plot) {
    std::string op;
    while (in >> op) {
        if (op == "Plot") {
            read_plot(in, plot);
        }
        else if (op == "Function") {
            read_function(in, plot);
        }
        else if (op == "Color") {
            read_color(in, plot);
        }
        else if (op == "FillAbove" || op == "FillBelow" || op == "FillBetween") {
            read_fill(op, in, plot);
        }
        else {
            throw PlotException("invalid operation: " + op);
        }
    }
}

void Reader::read_plot(std::istream &in, Plot &plot) {
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    int width;
    int height;
    try {
        in >> xmin >> ymin >> xmax >> ymax >> width >> height;
    } catch (const std::exception &e) {
        throw PlotException(std::string("error parsing Plot operator: ") + e.what());
    }
    
    //invalid plot directives (invalild plot bound)
    if (xmin >= xmax || ymin >= ymax){
        throw PlotException(std::string("invalid plot bounds"));
    }
    // invalid plot directives invalild image dimensions
    if (width <= 0 || height <= 0 ){
        throw PlotException(std::string("invalid image dimensions"));
    }
    plot.set_bounds(xmin, xmax, ymin, ymax, width, height);
}

void Reader::read_function(std::istream &in, Plot &plot) {
    std::string name;
    Expr *expr;
    try {
        in >> name;
        expr = expr_parser.parse(in);
    } catch (const std::exception &e) {
        throw PlotException(std::string("error parsing Function operator: ") + e.what());
    }
    plot.insert_function(new Function(name, expr));
}

void Reader::read_color(std::istream &in, Plot &plot) {
    std::string name;
    Color color;
    try {
        in >> name >> color;
        // check_color(color);
    } catch (const std::exception &e) {
        throw PlotException(std::string("error parsing Color operator: ") + e.what());
    }
    plot.set_func_color(name, color);
}

void Reader::read_fill(const std::string &op, std::istream &in, Plot &plot) {
    std::string func_name1;
    std::string func_name2;
    double opacity;
    Color color;
    try {
        in >> func_name1;
        if (op == "FillBetween") {
            in >> func_name2;
        }
        in >> opacity >> color;

    } catch (const std::exception &e) {
        throw PlotException("error parsing " + op + " operator: " + e.what());
    }

    Function *func1 = plot.get_func(func_name1);
    if (!func1) {
        throw PlotException("invalid function: " + func_name1);
    }
    
    Fill *fill;
    // FillBetween needs two functions
    if (op == "FillBetween") {
        Function *func2 = plot.get_func(func_name2);
        if (!func2) {
            throw PlotException("invalid function: " + func_name2);
        }
        fill = new FillBetween(opacity, color, func1, func2);
    }
    else if (op == "FillAbove") {
        fill = new FillAbove(opacity, color, func1);
    }
    else {
        fill = new FillBelow(opacity, color, func1);
    }
    plot.insert_fill(fill);
}

// bool Reader::check_color(const Color &c) {
//     std::stringstream ss;
//     std::string token;
//     ss >> token;
//     int count = 0;
//     while (ss >> token){
//         if (std::stod(token) < 0 ||std::stod(token) > 255){
//             throw PlotException(std::string("invalid Color data values"));
//         }
//         count ++;
//     }
//     if (count!= 3){
//         throw PlotException(std::string("Color directive missing: expects 3 data values but found "
//             + std::to_string(count)));
//     }
// }