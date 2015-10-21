#include "UI/Slider.h"

namespace UI
{
	Slider::Slider(float* _float_flag, float _x, float _y, float _width, float _height, float _minValue, float _maxValue, Type _ref)
		: Element(_x, _y, _width, _height, _ref),
		float_flag(_float_flag),
		minValue(_minValue),
		maxValue(_maxValue),
		currentValue(_maxValue),
		bgColor({ 0.204, 0.596, 0.859, 1.0 }),
		handlerColor({ 1.0, 1.0, 1.0, 1.0 })
	{

	}

	void Slider::setMinMax(float min, float max)
	{
		minValue = min;
		maxValue = max;
	}

	void Slider::setValue(float* value)
	{
		float_flag = value;

		if (*value >= 0 && *value <= maxValue)
			currentValue = *value;
	}

	void Slider::setValue(float value)
	{
		if (value >= 0 && value <= maxValue)
			currentValue = value;

		if (float_flag != nullptr)
			*float_flag = currentValue;
	}

	float Slider::getMin() const
	{
		return minValue;
	}

	float Slider::getMax() const
	{
		return maxValue;
	}

	float Slider::getValue() const
	{
		return currentValue;
	}

	void Slider::draw()
	{
		float percent = 0.6f;
		float current_height = percent * height_final;
		float offset = ((1.0f - percent) * height_final) / 2.0f;

		// Slider bar
		drawSquare(Vector2(x_final, y_final + offset), width_final, current_height, bgColor, { 0.0, 0.0, 0.0, 1.0 });

		// Slider handler
		float distanceMax = maxValue - minValue;
		float distanceCurr = currentValue - minValue;
		float posInSlider = (distanceCurr / distanceMax) * width_final - height_final / 2.0f;

		drawSquare(Vector2(x_final + posInSlider, y_final), height_final, height_final, handlerColor, { 0.0, 0.0, 0.0, 1.0 });

	}

	void Slider::onMouseClick(MouseButton button, MouseState state, int x, int y)
	{
		if (button == BUTTON_LEFT && state == MOUSE_DOWN)
		{
			float distance = (float) x - x_final;
			float value = distance * (maxValue - minValue) / width_final + minValue;
			setValue(value);
		}
	}

	void Slider::onMouseDrag(int x, int y)
	{
		float distance = (float)x - x_final;
		float value = distance * (maxValue - minValue) / width_final + minValue;
		setValue(value);
	}

}
