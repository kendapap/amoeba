#include "graphics.hpp"
#include "window.hpp"
#include <iostream>

using namespace std;
using namespace genv;

class Game : public Window
{
private:
    vector<vector<Mezo *>> _palya;
    int _size;
    bool _jatekos;
public:
    Game (int x, int y) : Window (x,y)
    {
        _jatekos = 0;
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
        gout << refresh;
    }

    void mezo_press (Mezo *melyik) 
    {
        melyik->click(_jatekos);
        _jatekos = !_jatekos;

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
    }
};

int main ()
{
    Game g (958,958);
    g.event_loop();
    return 0;
}