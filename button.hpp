#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "static_text.hpp"

class Window;

class Button : public Static_text
{
protected:
    Window *_win;
public:
    Button (int x, int y, int l, int h, std::string text, Window * win);
    virtual void use (genv::event ev) override;
};

#endif