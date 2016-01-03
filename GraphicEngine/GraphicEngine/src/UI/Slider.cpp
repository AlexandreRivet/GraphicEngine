#include "UI/Slider.h"

namespace UI
{
	Slider::Slider(float* _float_flag, float _x, float _y, float _width, float _height, float _minValue, float _maxValue, Type _ref)
		: Element(_x, _y, _width, _height, _ref),
		float_flag(_float_flag),
		minValue(_minValue),
		maxValue(_maxValue),
		bgColor({ 0.204f, 0.596f, 0.859f, 1.0f }),
		handlerColor({ 1.0f, 1.0f, 1.0f, 1.0f })
	{
		if (_float_flag != nullptr)
			currentValue = *_float_flag;
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

		mOnChange();
	}

	void Slider::onChangeValue(std::function<void()> onChange)
	{
		mOnChange = onChange;
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
		float current_height = percent * mViewportRect.h;
		float offset = ((1.0f - percent) * mViewportRect.h) / 2.0f;

		// Slider bar
		drawSquare(Vector2(mViewportRect.x, mViewportRect.y + offset), mViewportRect.w, current_height, bgColor, { 0.0f, 0.0f, 0.0f, 1.0f });

		// Slider handler
		float distanceMax = maxValue - minValue;
		float distanceCurr = currentValue - minValue;
		float posInSlider = (distanceCurr / distanceMax) * mViewportRect.w - mViewportRect.h / 2.0f;

		drawSquare(Vector2(mViewportRect.x + posInSlider, mViewportRect.y), mViewportRect.h, mViewportRect.h, handlerColor, { 0.0f, 0.0f, 0.0f, 1.0f });

	}

    void Slider::onMouseClick(MouseButton button, MouseState state, const Vector2& mousePosition)
	{
		if (button == BUTTON_LEFT && state == MOUSE_DOWN)
		{
			float distance = (float) mousePosition.x - mViewportRect.x;
			float value = distance * (maxValue - minValue) / mViewportRect.w + minValue;
			setValue(value);
		}
	}

    void Slider::onMouseDrag(const Vector2& mousePosition)
	{
		float distance = (float)mousePosition.x - mViewportRect.x;
		float value = distance * (maxValue - minValue) / mViewportRect.w + minValue;
		setValue(value);
	}

}
