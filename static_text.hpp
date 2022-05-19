#ifndef STATIC_TEXT_HPP
#define STATIC_TEXT_HPP

#include "ans_widget.hpp"

class Static_text : public Widget
{
protected:
    std::string _text;
public:
    Static_text (int x, int y, int l, int h, std::string t);
    void draw () override;
    void change (std::string t);
    virtual void use (genv::event ev) override;
};

#endif