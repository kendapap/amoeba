#ifndef MENU_HPP
#define MENU_HPP

#include "ans_widget.hpp"
#include <vector>

class Menu : public Widget
{
protected:
    int _activ;
    std::vector<std::string> _records;
    size_t _size;
    bool _clicked;
    size_t _from;
public:
    Menu (int x, int y, int l, int h, std::vector<std::string> records, int size);
    virtual void draw () override;
    virtual void use (genv::event ev) override;
    std::string logging ();
    std::string remove ();
    void atad (std::string str);
    void draw_all ();
    void clean_all ();
};  

#endif