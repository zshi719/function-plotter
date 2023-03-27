// Zichen Shi (zshi34)

#ifndef FILL_H
#define FILL_H

#include <string>
#include "image.h"
#include "func.h"

class Fill {
private:
    double opacity;
    Color color;

public:

    Fill(double opacity, Color color);

    virtual ~Fill();

    virtual bool get_fill_range(double x, double ymin, double ymax, double &range_min, double &range_max) const = 0;

    Color get_fill_color(Color old) const;
};


class FillAbove : public Fill {
private:
    Function *func;
public:
    FillAbove(double opacity, Color color, Function *func);

    bool get_fill_range(double x, double ymin, double ymax, double &range_min, double &range_max) const override;
};


class FillBelow : public Fill {
private:
    Function *func;
public:
    FillBelow(double opacity, Color color, Function *func);

    bool get_fill_range(double x, double ymin, double ymax, double &range_min, double &range_max) const override;
};


class FillBetween : public Fill {
private:
    Function *func1;
    Function *func2;
public:
    FillBetween(double opacity, Color color, Function *func1, Function *func2);

    bool get_fill_range(double x, double ymin, double ymax, double &range_min, double &range_max) const override;
};

#endif // FILL_H