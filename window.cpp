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

void Window::logging()
{}

void Window::button_press (Button *melyik){}
void Window::mezo_press (Mezo *melyik){}

void Window::clean()
{
    gout << move_to (0,0)
             << color (0,0,0)
             << box (_X,_Y);
}