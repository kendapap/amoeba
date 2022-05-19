#include "mezo.hpp"
#include "window.hpp"

#include <iostream>

using namespace genv;
using namespace std;

Mezo::Mezo(int x, int y, int l, int h, Window *win) : 
    Widget (x,y,l,h), _win(win)
{
    _free = 1;
    _state = 0;
    _usable = 1;
}

void Mezo::draw ()
{

    if (_usable)
    {
        gout << move_to (_posx-2,_posy-2)
            << color (255,255,255)
            << box (_length+4,_height+4)
            << move_to (_posx,_posy)
            << color (64,64,64)
            << box (_length,_height);
    }
    else
    {
        gout << move_to (_posx-2,_posy-2)
            << color (0,0,0)
            << box (_length+4,_height+4)
            << move_to (_posx,_posy)
            << color (0,0,0)
            << box (_length,_height);
    }

    if (_state == 1)
    {
        gout << move_to (_posx + 5, _posy + 5)
             << color (255,0,0)
             << line_to (_posx + _length - 5, _posy+_height-5)
             << move_to (_posx + 5, _posy + _height -5)
             << line_to (_posx + _length - 5, _posy + 5);
    }

    if (_state == 2)
    {
        int r = _length/2 - 5;
        int rb = _length/2 - 8;

        for (int dx = -r ; dx <= r; dx++)
        {
            for (int dy = -r; dy <= r ; dy++)
            {
               if (_posx + dx >= 0 && _posy + dy >= 0 && dx*dx+dy*dy<r*r)
               {
                  gout << color (0,0,255) << move_to(_posx+dx+_length/2, _posy+dy+ _height/2) << dot;
               }
            }
        }

        for (int dx = -rb ; dx <= rb; dx++)
        {
            for (int dy = -r; dy <= r ; dy++)
            {
               if (_posx + dx >= 0 && _posy + dy >= 0 && dx*dx+dy*dy<rb*rb)
               {
                  gout << color (0,0,0) << move_to(_posx+dx+_length/2, _posy+dy+ _height/2) << dot;
               }
            }
        }
    }

}

void Mezo :: click(bool jatekos)
{
    if (jatekos)
        _state = 1;
    else
        _state = 2;

    _free = 0;
}

void Mezo :: use(event ev)
{
    if (ev.button == btn_left && over(ev.pos_x,ev.pos_y) && _usable)
    {
        _win->mezo_press(this);
        _free = 0;
    }
}

bool Mezo::is_free()
{
    return _free;
}

void Mezo::make_usable(bool u)
{
    if (u)
        _usable = 1;
    else
    {
        _usable = 0;
    }
}