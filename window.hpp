#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "ans_widget.hpp"
#include "graphics.hpp"
#include "static_text.hpp"
#include "numset.hpp"
#include "menu.hpp"
#include "button.hpp"
#include "mezo.hpp"
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
    bool _running;
public:
    Window (int X, int Y);
    void add_widget (Widget *widget_to_add);
    virtual void event_loop ();
    virtual void logging ();
    virtual void clean ();
    virtual void button_press (Button *melyik);
    virtual void mezo_press (Mezo *melyik);
};

#endif