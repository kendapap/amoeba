#include "window.hpp"
#include <iostream>

using namespace std;
using namespace genv;

class Game : public Window
{
private:
    vector<vector<Mezo *>> _palya;
    Static_text *_winner;
    Static_text *_title;
    Static_text *_next_player;
    Button *_start;
    Button *_close;
    int _size;

    bool _jatekos;
public:
    Game (int x, int y) : Window (x,y)
    {
        _jatekos = 0;
        _next_player = new Static_text (20,20,200,30,"Kék következik");

        _size = 17;

        for(int y = 0; y < _size; y++)
        {
            vector<Mezo *> tmp (_size);
            for (int x = 0; x < _size; x++) 
            {
                tmp[x] = new Mezo (20 + x * 54, 20 + y * 54, 50,50, this);
                _widgets.push_back(tmp[x]);
            }
            _palya.push_back(tmp);
        }

        for (int y = 0; y < _size; y++)
        {
            for (int x = 0; x < _size; x++)
            {
                if (x == 0 || y == 0 ||
                    x == _size-1 || y ==_size-1)
                {
                    _palya[x][y]->make_usable(0);
                }
                _palya[x][y]->draw();
            }
        }
        _next_player->draw();

    }

    void friss ()
    {
        clean();

        for (int y = 0; y < _size; y++)
        {
            for (int x = 0; x < _size; x++)
            {
                _palya[x][y]->draw();
            }
        }
        _next_player->draw();
    }

    int win_check ()
    {
        int winner = 0;

        for (int y = 1; y < _size-1; y++)
        {
            for (int x = 1; x < _size-1; x++)
            {
                if (_palya[x][y]->is_X())
                {
                    int i = 1;
                    while (_palya[x][y+i]->is_X())
                    {
                        i++;
                    }

                    if (i == 5)
                        winner = 1;
                }

                if (_palya[x][y]->is_O())
                {
                    int i = 1;
                    while (_palya[x][y+i]->is_O())
                    {
                        i++;
                    }
                    if (i == 5)
                        winner = 2;
                }

                if (_palya[y][x]->is_X())
                {
                    int i = 1;
                    while (_palya[y+i][x]->is_X())
                    {
                        i++;
                    }
                    if (i == 5)
                        winner = 1;
                }

                if (_palya[y][x]->is_O())
                {
                    int i = 1;
                    while (_palya[y+i][x]->is_O())
                    {
                        i++;
                    }
                    if (i == 5)
                        winner = 2;
                }

                if (_palya[y][x]->is_X())
                {
                    int i = 1;
                    while (_palya[y+i][x+i]->is_X())
                    {
                        i++;
                    }
                    if (i == 5)
                        winner = 1;
                }

                if (_palya[y][x]->is_O())
                {
                    int i = 1;
                    while (_palya[y+i][x+i]->is_O())
                    {
                        i++;
                    }
                    if (i == 5)
                        winner = 2;
                }

                if (_palya[y][x]->is_X())
                {
                    int i = 1;
                    while (_palya[y+i][x-i]->is_X())
                    {
                        i++;
                    }
                    if (i == 5)
                        winner = 1;
                }

                if (_palya[y][x]->is_O())
                {
                    int i = 1;
                    while (_palya[y+i][x-i]->is_O())
                    {
                        i++;
                    }
                    if (i == 5)
                        winner = 2;
                }
            }
        }

        return winner;
    }

    void main_menu (int type)
    {
        
        if (type == 1 || type == 2)
        {
            clean();
            if (type == 1)
                _winner = new Static_text (_X/2-150,_Y/2-75, 300, 50, "Piros nyert");
            else
                _winner = new Static_text (_X/2-150,_Y/2-75, 300, 50, "Kék nyert");
            _winner->draw();
            _start = new Button (_X/2-150, _Y/2+25, 300,50,"Restart",this);
            _widgets.push_back(_start);
            _start->draw();
        }
        if (type == 0)
        {
            _title = new Static_text (_X/2-250,_Y-40, 500, 30, "A kezdéshez kattints bárhova!");
            _title->draw();
        }
    }

    void button_press (Button *melyik)
    {
        if (melyik == _start)
        {
            for (size_t i = 0; i < _widgets.size();i++)
            {
                if (_widgets[i] == _start)
                {   
                    _widgets.erase(_widgets.begin()+i);
                }
            }
            clean();
            
            for (int y = 0; y < _size; y++)
            {
                for (int x = 0; x < _size; x++)
                {
                    _palya[x][y]->reset();
                    
                    if (x == 0 || y == 0 ||
                    x == _size-1 || y ==_size-1)
                    {
                        _palya[x][y]->make_usable(0);
                    }

                    _palya[x][y]->draw();
                }
            }

            _jatekos = 0;
            _next_player->change("Kék következik");
            _next_player->draw();
        }
    }

    void mezo_press (Mezo *melyik) 
    {
        melyik->click(_jatekos);
        _jatekos = !_jatekos;
        if (_jatekos)
            _next_player->change("Piros következik");
        else
            _next_player->change("Kék következik");

        for (int y = 0; y < _size; y++)
        {
            for (int x = 0; x < _size; x++)
            {
                if (x == 0 || y == 0 ||
                    x == _size-1 || y ==_size-1)
                {
                    _palya[x][y]->make_usable(0);
                }
                else
                {
                    if (_palya[x][y]->is_free() &&
                        (!_palya[x+1][y]->is_free() ||
                        !_palya[x-1][y]->is_free() ||
                        !_palya[x][y+1]->is_free() ||
                        !_palya[x][y-1]->is_free() ||
                        !_palya[x+1][y+1]->is_free() ||
                        !_palya[x+1][y-1]->is_free() ||
                        !_palya[x-1][y+1]->is_free() ||
                        !_palya[x-1][y-1]->is_free() )) 
                    {
                        _palya[x][y]->make_usable(1);
                    }
                    else
                        _palya[x][y]->make_usable(0);
                }
            }
        }

        friss();

        if (win_check() == 1)
        {
            main_menu(1);
        }

        if (win_check() == 2)
        {
            main_menu(2);
        }
    }
};

int main ()
{
    Game g (958,958);
    g.main_menu(0);
    g.event_loop();
    return 0;
}