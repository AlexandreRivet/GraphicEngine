#include "UI/Layout.h"

namespace UI
{
    Layout::Layout(float _x, float _y, float _width, float _height, Type _ref)
        : Element(_x, _y, _width, _height, _ref)
    {}

    void Layout::draw()
    {
        //Do nothing because is just a layout
    }

}