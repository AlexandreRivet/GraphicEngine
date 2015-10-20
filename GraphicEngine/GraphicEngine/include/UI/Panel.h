#ifndef _PANEL_H_
#define _PANEL_H_

#include "Element.h"

namespace UI
{
	class Panel : public Element
	{
	public:

		Panel(float _x, float _y, float _width, float _height, Type _ref = PIXEL);

		void draw();
	};
}

#endif