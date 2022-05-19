#include "window.hpp"

#include <iostream>

using namespace genv;
using namespace std;

Window::Window (int X, int Y) : _X(X), _Y(Y)
{
    gout.open (_X,_Y);
    selected = 0;
}

void Window::add_widget(Widget *widget_to_add)
{
    _widgets.push_back(widget_to_add);
}

void Window::event_loop()
{
    for (auto w : _widgets)
    {
        w->draw();
    }
    gout << refresh;
    
    while (gin >> _ev && _ev.keycode != key_escape)
    {
        if (_ev.button == btn_left)
        {
            for (auto w : _widgets)
            {
                if (w->over(_ev.pos_x, _ev.pos_y))
                {
                    selected = w;
                }
            }
        }

        if (selected)
        {
            selected->use(_ev);
            selected->draw();
        }

        if (_ev.keycode == -key_space)
        {
            logging ();
        }
        
        gout << refresh;
    }
}