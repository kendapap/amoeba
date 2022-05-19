#include "button.hpp"
#include "window.hpp"

using namespace std;
using namespace genv;

Button::Button(int x, int y, int l, int h, string text, Window *win) :
    Static_text (x,y,l,h,text), _win(win)
{}

void Button::use (genv::event ev) 
{
    if (ev.button == btn_left && over(ev.pos_x,ev.pos_y))
    {
        _win->button_press(this);
    }
}