#ifndef MEZO_HPP
#define MEZO_HPP

#include "ans_widget.hpp"

class Window;

class Mezo : public Widget
{
protected:
    Window *_win;
    bool _free, _usable;
    int _state; // 0 - üres,1 - X, 2 - O
public:
    Mezo (int x, int y, int l, int h, Window *win);
    void draw () override;
    virtual void use (genv::event ev) override;
    void click (bool jatekos);
    bool is_free ();
    void make_usable (bool u);
};

#endif