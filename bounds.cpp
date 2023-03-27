// Zichen Shi (zshi34)

#include <cmath>
#include "bounds.h"


Bounds::Bounds() {
}

void Bounds::init(double xmin, double xmax, double ymin, double ymax, int width, int height) {
    this->xmin = xmin;
    this->xmax = xmax;
    this->ymin = ymin;
    this->ymax = ymax;
    this->width = width;
    this->height = height;
}

// Find the x coordinates that evenly divide the x-range
std::vector<double> Bounds::get_x_list() const {
    std::vector<double> res;
    double delta = (xmax - xmin) / width;
    for (int i = 0; i < width; ++i) {
        res.push_back(i * delta + xmin);
    }
    return res;
}

// map y values onto y-axis
int Bounds::map_y_to_height(double y_val) const {
    int y = (int) ((y_val - ymin) * height / (ymax - ymin));
    return y;
}


int Bounds::get_width() const {
    return width;
}

int Bounds::get_height() const {
    return height;
}

double Bounds::get_ymin() const {
    return ymin;
}

double Bounds::get_ymax() const {
    return ymax;
}