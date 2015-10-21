#ifndef _SLIDER_H_
#define _SLIDER_H_

#include <functional>

#include "Element.h"

namespace UI
{
	class Slider : public Element	// A templater pour gérer les int, les float et les double
	{
	public:

		Slider(float* float_flag, float _x, float _y, float _width, float _height = 15, float _minValue = 0, float _maxValue = 10, Type _ref = PIXEL);

		void setMinMax(float min, float max);
		void setValue(float value);
		void setValue(float* value);

		float getMin() const;
		float getMax() const;
		float getValue() const;		// Voir référence pour modifier directement

		void draw();

		void onMouseClick(MouseButton button, MouseState state, int x, int y);
		void onMouseDrag(int x, int y);

	private:
		
		float currentValue;
		float minValue;
		float maxValue;

		float* float_flag;

		Color bgColor;
		Color handlerColor;
	};


}

#endif