#include "numset.hpp"
#include "static_text.hpp"

using namespace std;
using namespace genv;

Numset::Numset (int x, int y, int l, int h, int start, int end, int step) :
    Widget (x,y,l,h)
{
    for (int i = start; i <= end; i = i + step)
    {
        _range.push_back(i);
    }
    
    _actnum = 0;
}

void Numset::draw ()
{

    Static_text counter (_posx, _posy, _length/2,_height, to_string(_range[_actnum]));
    counter.draw();

    Static_text minusz (_posx+_length/2+2, _posy, _length/4, _height, "<");
    Static_text plusz (_posx+3*_length/4+4, _posy, _length/4, _height, ">");
    minusz.draw();
    plusz.draw();
}

bool Numset::is_over_minus(int x, int y)
{
    return x >= _posx+_length/2+2 && x <=  _posx+3*_length/4 + 2 &&
           y >= _posy && y <= _posy + _height;
}

bool Numset::is_over_plus (int x, int y)
{
    return x >= _posx+3*_length/4+4 && x <=  _posx+_length &&
           y >= _posy && y <= _posy + _height;
}

void Numset::use (event ev)
{
    if (ev.keycode == key_right && _actnum != _range.size()-1)
    {
        _actnum += 1;
    }

    if (ev.keycode == key_left && _actnum != 0)
    {
        _actnum -= 1;
    }

    if (ev.keycode == key_pgup && _actnum <= _range.size()-11)
    {
        _actnum += 10;
    }
    
    if (ev.keycode == key_pgdn && _actnum >= 10)
    {
        _actnum -= 10;
    }

    if (ev.button == btn_left)
    {    
        if (this->is_over_plus(ev.pos_x,ev.pos_y) && _actnum != _range.size()-1)
        {
            _actnum += 1;
        }

        if (this->is_over_minus(ev.pos_x,ev.pos_y) && _actnum != 0)
        {
            _actnum -= 1;
        }
    }
}

size_t Numset::logging()
{
    return _range[_actnum];
}

