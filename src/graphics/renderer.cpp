//Zichen Shi (zshi34)

#include <iostream>
#include <cmath>
#include <cassert>
#include <memory>
#include "exception.h"
#include "renderer.h"

//#define DEBUG_FILL
//#define DEBUG_PLOT

Renderer::Renderer(const Plot &plot) : m_plot(plot), m_img(nullptr) {
}

Renderer::~Renderer() {
  // Note: the Renderer object does not "own" the Image object,
  // since the render() member function transfers ownership of
  // the Image object to the caller (in the main function)
}

Image *Renderer::render() {
    int width = m_plot.get_width();
    int height = m_plot.get_height();

  // the unique_ptr will take care of deleting the Image object
  // if an exception is thrown
    std::unique_ptr<Image> img(new Image(width, height));
    m_img = img.get();

  // render the plot image
    std::vector<double> x_list = m_plot.get_bounds().get_x_list();
    for (Fill *fill: m_plot.get_fill_list()) {
        render_fill(x_list, fill);
    }
    for (Function *func: m_plot.get_func_list()) {
        render_function(x_list, func);
    }
    
    return img.release();
}

// render the fills
void Renderer::render_fill(const std::vector<double> &x_list, Fill *fill) {
    double ymin = m_plot.get_bounds().get_ymin();
    double ymax = m_plot.get_bounds().get_ymax();

    if (ymin >= ymax){
        throw PlotException(std::string("invalid bound"));
    }

    for (int x = 0; x < (int) x_list.size(); ++x) {
        //determine the x and y coordinates of each pixel
        double x_val = x_list[x];
        double range_min;
        double range_max;

        if (!fill->get_fill_range(x_val, ymin, ymax, range_min, range_max)) {
            continue;
        }

        if (range_min > range_max){
            throw PlotException(std::string("invalid range"));
        }

        int min_y_pos = m_plot.get_bounds().map_y_to_height(range_min);
        int max_y_pos = m_plot.get_bounds().map_y_to_height(range_max);

        if (min_y_pos > max_y_pos){
            throw PlotException(std::string("invalid bound"));
        }
        
        // iterate through every pixel in the image, adjust or set colors based on the fill’s opacity and color values
        for (int y = min_y_pos; y < max_y_pos; ++y) {
            Color old = m_img->get(x, y);
            m_img->set(x, y, fill->get_fill_color(old));
        }
    }
}

// render the Functions in the order in which they appear in the plot file
void Renderer::render_function(const std::vector<double> &x_list, Function *func) {
    // iterate over the vector storing all x-coordinates, calculate the y-value through the function for x,
    // and map y-values to the y-axis
    for (int x = 0; x < (int) x_list.size(); ++x) {
        double x_val = x_list[x];
        double y_val = func->get_expr()->eval(x_val);
        int y = m_plot.get_bounds().map_y_to_height(y_val);
        Color color = m_plot.get_func_color(func->get_name());
        m_img->set(x, y, color, 1);
    }
}