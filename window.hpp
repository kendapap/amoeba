#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "ans_widget.hpp"
#include "graphics.hpp"
#include "static_text.hpp"
#include "numset.hpp"
#include "menu.hpp"
#include "button.hpp"
#include  <vector>
#include <string>
#include <fstream>

class Window
{
protected:
    int _X, _Y;
    std::vector<Widget *> _widgets;
    Widget *selected;
    genv::event _ev;

public:
    Window (int X, int Y);
    void add_widget (Widget *widget_to_add);
    void event_loop ();
    virtual void logging () = 0;
    virtual void button_press (Button *melyik) = 0;
};

#endif