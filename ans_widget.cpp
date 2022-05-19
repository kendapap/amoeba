#include "ans_widget.hpp"

using namespace genv;

Widget::Widget (int x, int y, int l, int h) : 
    _posx (x), _posy (y), _length(l), _height(h)
{}

bool Widget::over (int x, int y)
{
    return x >= _posx && x <= _posx + _length &&
           y >= _posy && y <= _posy + _height;
}