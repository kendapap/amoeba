#include "static_text.hpp"

using namespace genv;
using namespace std;

Static_text::Static_text (int x, int y, int l, int h, string t) :
    Widget (x,y,l,h), _text(t)
{}

void Static_text::draw ()
{
    gout.load_font("LiberationMono-Regular.ttf", _height/1.5);
    gout << move_to (_posx-2,_posy-2)
         << color (255,255,255)
         << box (_length+4,_height+4)
         << move_to (_posx,_posy)
         << color (64,64,64)
         << box (_length,_height)
         << move_to (_posx + _length/2 - gout.twidth(_text) / 2, _posy + _height / 2 - (gout.cascent() + gout.cdescent()) / 2)
         << color (255,255,255)
         << text (_text);
}

void Static_text::use (event ev)
{}

void Static_text::change (string t)
{
    _text = t;
}
