#ifndef _HISTOGRAM_H_
#define _HISTOGRAM_H_

#include <functional>

#include "Element.h"

namespace UI
{
	struct HistoBar
	{
		float value;
		ColorStruct color;

		HistoBar(float _value = 0.0f, ColorStruct _color = ColorStruct(0.0f, 0.0f, 0.0f, 1.0f))
			: value(_value),
			color(_color)
		{}
	};

	class Histogram : public Element
	{
	public:

		Histogram(const std::string& title, float x, float y, float width, float height, Type ref = PIXEL);
		Histogram(const std::string& title, const Rect<RefValue>& localRect);

		void addValue(const std::string& key, float value, ColorStruct c = ColorStruct(0.3f, 0.7f, 0.8f, 1.0f));
		void setAxis(const std::string& x, const std::string &y);
		void clear();

		void computeState();
		void draw();

		void onMouseClick(MouseButton button, MouseState state, int x, int y);

	private:
		std::string mTitle;

		// XAxis
		std::string mXAxisTitle;
		float mXAxisMin;
		float mXAxisMax;
		int mXAxisStep;

		// YAxis
		std::string mYAxisTitle;
		float mYAxisMin;
		float mYAxisMax;
		int mYAxisStep;

		std::map<std::string, HistoBar> mValues;

		ColorStruct mLabelColor;
		ColorStruct mBarColor;

		// Variable saved for calculations 
		std::vector<Vector2> mXAxis;
		std::vector<Vector2> mYAxis;
		std::map<std::string, Rect<float>> mBars;
		std::map<std::string, std::vector<Vector2>> mSeparationDashes;
		std::map<std::string, Rect<float>> mPanelsValue;
		std::map<std::string, std::vector<Vector2>> mTriangles;
		std::map<std::string, Rect<float>> mTexts;

	};

}

#endif