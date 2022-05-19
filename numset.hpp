#ifndef NUMSET_HPP
#define NUMSET_HPP

#include "ans_widget.hpp"
#include <vector>

class Numset : public Widget
{
protected:
    size_t _actnum;
    std::vector<int> _range;
    bool is_over_plus (int x, int y);
    bool is_over_minus (int x, int y);
    
public:
    Numset (int x, int y, int l, int h, int start, int end, int step);
    virtual void draw () override;
    virtual void use (genv::event ev) override;
    size_t logging ();
};

#endif