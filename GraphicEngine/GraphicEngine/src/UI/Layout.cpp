#include "UI/Layout.h"

#include "Utils/utils.h"

namespace UI
{
    Layout::Layout(float _x, float _y, float _width, float _height, Type _ref)
        : Element(_x, _y, _width, _height, _ref)
    {}

    void Layout::draw()
    {
        //Do nothing because is just a layout
    }

    void Layout::onMouseClick(int button, int state, int x, int y)
    {
        std::for_each(children.begin(), children.end(), [button, state, x, y](Element* e)
        {
            e->onMouseClick(button, state, x, y);
        });
    }
}