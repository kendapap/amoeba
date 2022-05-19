#ifndef ANS_WIDGET_HPP
#define ANS_WIDGET_HPP

#include "graphics.hpp"
#include <string>

class Widget
{
protected:
    int _posx, _posy, _length, _height;
public:
    Widget (int x, int y, int l, int h);
    virtual void draw () = 0;
    virtual void use (genv::event ev) = 0;
    bool over (int x, int y);
};

#endif