#include "menu.hpp"
#include "static_text.hpp"

using namespace std;
using namespace genv;

Menu::Menu (int x, int y, int l, int h, vector<string> records, int size) :
    Widget (x,y,l,h), _records(records), _size(size)
{
    _activ = 0;
    _clicked = 0;
    _from = 0;
}

void Menu::draw ()
{
    Static_text lathato (_posx, _posy, _length, _height, _records[_activ]);
    lathato.draw();

    if (_size < _records.size())
    {
        if (_from == 0)
        {
            Static_text arrow (_posx + _length -_height, _posy, _height, _height, "\u2193"); //lefele nyíl
            arrow.draw ();
        }
            
        if (_from > 0 && _from < _records.size() - _size)
        {
            Static_text arrow (_posx + _length -_height, _posy, _height, _height, "\u2195"); //kétirányú nyíl
            arrow.draw ();
        }

        if (_from == _records.size() - _size)
        {
            Static_text arrow (_posx + _length -_height, _posy, _height, _height, "\u2191"); //felfele nyíl
            arrow.draw ();
        }
    }
    else
    {
        if (_clicked)
        {
            Static_text arrow (_posx + _length -_height, _posy, _height, _height, "\u2191"); //felfele nyíl
            arrow.draw ();    
        }
        else
        {
            Static_text arrow (_posx + _length -_height, _posy, _height, _height, "\u2193"); //lefele nyíl
            arrow.draw ();
        }
    }
}

void Menu::draw_all ()
{
    if (_size <= _records.size())
    {
        for (size_t i = 1; i <= _size; i++)
        {
            Static_text s (_posx, _posy+i*_height, _length, _height, _records[_from + i-1]);
            s.draw();
        }
    }
    else
    {
        for (size_t i = 0; i < _records.size(); i++)
        {
            Static_text s (_posx, _posy+i*_height, _length, _height, _records[i]);
            s.draw();
        } 
    }
}

void Menu::clean_all ()
{
    gout << move_to (_posx-2, _posy + _height + 2)
         << color (0,0,0)
         << box (_length+4, (_height+2)*_size);
}

void Menu::use (event ev)
{
    if (ev.button == btn_left)
    {
        int xx = ev.pos_x; int yy = ev.pos_y;
        if (over(xx,yy))
            { 
            if (_clicked)
            {
                draw();
                clean_all ();
                _clicked = 0;
            }
            else
            {
                draw_all();
                draw();
                _clicked = 1;
            }
        }
        
        if (xx >= _posx && xx <= _posx + _length &&
            yy >= _posy + _height && yy <= _posy + int((_size+1)*(_height)) && _clicked)
        {
            for (size_t i = 1; i <= _size; i++)
            {
                if (yy >= _posy + int(_height*i) && yy <= _posy + int(_height*(i+1)))
                {
                    _activ = i-1+_from;
                    _from = 0;
                    draw();
                    clean_all ();
                    _clicked = 0;
                }
            }
            
        }    
    }

    if (_clicked)
    {
        if (ev.button == btn_wheeldown && _from < _records.size() - _size)
        {
            _from += 1;
            clean_all();
            draw_all();
        }

        if (ev.button == btn_wheelup && _from > 0)
        {
            _from -= 1;
            clean_all();
            draw_all();
        }
    }  
}

string Menu::logging()
{
    return _records[_activ];
}

string Menu::remove()
{
    string del = "0";
    if(_records.size()>0)
    {
    del = _records[_activ];
    _records.erase(_records.begin()+_activ);
    }
    return del;
}

void Menu::atad(string str)
{
    _records.push_back(str);
}