#ifndef _PANEL_H_
#define _PANEL_H_

#include "Layout.h"

namespace UI
{
	class Panel : public Layout
	{
	public:

		Panel(float _x, float _y, float _width, float _height, Type _ref = PIXEL);

		void draw();

        virtual void onMouseEnter(const Vector2& mousePosition){ tools::unusedArg(mousePosition); };
        virtual void onMouseExit(const Vector2& mousePosition){ tools::unusedArg(mousePosition); };
	};
}

#endif