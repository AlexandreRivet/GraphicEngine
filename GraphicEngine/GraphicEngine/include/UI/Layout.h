#ifndef _UI_LAYOUT_H_
#define _UI_LAYOUT_H_

#include "Element.h"

namespace UI
{
    class Layout : public Element
    {
    public:

        Layout(float _x, float _y, float _width, float _height, Type _ref = PIXEL);

        void draw();

        virtual void onMouseEnter(const Vector2& mousePosition){ tools::unusedArg(mousePosition); };
        virtual void onMouseExit(const Vector2& mousePosition){ tools::unusedArg(mousePosition); };
    };
}

#endif