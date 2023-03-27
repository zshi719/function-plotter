// Zichen Shi (zshi34)

#ifndef BOUNDS_H
#define BOUNDS_H

#include <vector>

class Bounds {
private:
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    int width;
    int height;
    
public:
    Bounds();

    void init(double xmin, double xmax, double ymin, double ymax, int width, int height);

    // Find the x coordinates that evenly divide the x-range
    std::vector<double> get_x_list() const;

    // map y values onto y-axis
    int map_y_to_height(double y_val) const;

    // getter functions
    int get_width() const;

    int get_height() const;

    double get_ymin() const;

    double get_ymax() const;
};

#endif // BOUNDS_H
