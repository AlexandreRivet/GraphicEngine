#include "UI/Histogram.h"

namespace UI
{
	Histogram::Histogram(const std::string& title, float x, float y, float width, float height, Type ref)
		: Element(x, y, width, height, ref),
		mTitle(title),
		mXAxisTitle("X Axis"),
		mYAxisTitle("Y Axis"),
		mYAxisMin(0),
		mYAxisMax(50),
		mLabelColor(0.6f, 0.6f, 0.6f, 1.0f),
		mBarColor(0.133f, 0.192f, 0.247f, 1.0f)
	{
		mBackgroundColor = Color(0.992f, 0.890f, 0.655f, 1.0f);
	}

	Histogram::Histogram(const std::string& title, const Rect<RefValue>& localRect)
		: Element(localRect),
		mTitle(title),
		mXAxisTitle("X Axis"),
		mYAxisTitle("Y Axis"),
		mLabelColor(0.0f, 0.0f, 0.0f, 1.0f),
		mBarColor(0.3f, 0.5f, 0.4f, 1.0f)
	{

	}

	void Histogram::addValue(const std::string& key, float value, Color c)
	{
		if (value > mYAxisMax)
			mYAxisMax = value;
		mValues[key] = HistoBar(value, c);
		computeState();
	}

	void Histogram::clear()
	{
		mValues.clear();
		computeState();
	}

	void Histogram::computeState()
	{
		float offset_border = 25.0f;
		float height = mViewportRect.h - offset_border * 2.0f;
		float width = mViewportRect.w - offset_border * 2.0f;

		// Calc YAxis
		mYAxis.clear();
		mYAxis.push_back(Vector2(mViewportRect.x + offset_border, mViewportRect.y + offset_border));
		mYAxis.push_back(Vector2(mViewportRect.x + offset_border, mViewportRect.y + offset_border + height));

		// Calc YAxis
		mXAxis.clear();
		mXAxis.push_back(Vector2(mViewportRect.x + offset_border, mViewportRect.y + offset_border + height));
		mXAxis.push_back(Vector2(mViewportRect.x + offset_border + width, mViewportRect.y + offset_border + height));

		mBars.clear();
		int numberBars = mValues.size();
		if (numberBars > 0)
		{
			float bar_bg_width = width / numberBars;
			float bar_width = bar_bg_width * 0.4f;
			float remainder_width = bar_bg_width - bar_width;
			float max_distance = mYAxisMax - mYAxisMin;

			int i = 0;
			for (auto it = mValues.begin(); it != mValues.end(); ++it)
			{
				float current_distance = (*it).second.value;
				float size = (current_distance * height / max_distance);
				float current_y = mViewportRect.y + offset_border + (height - size);
				
				Rect<float> r(mViewportRect.x + offset_border + i * bar_bg_width + remainder_width, current_y, bar_width, size);

				// Bars
				mBars[(*it).first] = r;

				// Separation dashed
				std::vector<Vector2> dash;
				dash.push_back(Vector2(r.x + r.w, mViewportRect.y + offset_border));
				dash.push_back(Vector2(r.x + r.w, mViewportRect.y + offset_border + height));
				mSeparationDashes[(*it).first] = dash;

				// Panel (rect)
				float width_panel = getSizeBetweenTwoPosInString(tools::to_string_presision(current_distance, 3)) + 12.0f;

				mPanelsValue[(*it).first] = Rect<float>(r.x - ((width_panel - r.w) / 2.0f), r.y - 24, width_panel, 20);

				// Panel (tri)
				std::vector<Vector2> tri;
				float middle = r.x + r.w / 2.0f;
				tri.push_back(Vector2(middle - 3.0f, r.y - 4.0f));
				tri.push_back(Vector2(middle + 3.0f, r.y - 4.0f));
				tri.push_back(Vector2(middle, r.y));
				mTriangles[(*it).first] = tri;

				// Text
				std::string text = (*it).first;
				int sizeText = getSizeBetweenTwoPosInString(text);
				Rect<float> textRect(mViewportRect.x + i * bar_bg_width + offset_border + (bar_bg_width - sizeText) / 2.0f, mViewportRect.y + offset_border + height, sizeText, offset_border);
				mTexts[(*it).first] = textRect;

				i++;
			}
		}
		
	}

	void Histogram::draw()
	{
		// Background
		drawSquare(Vector2(mViewportRect.x, mViewportRect.y), mViewportRect.w, mViewportRect.h, mBackgroundColor, { 0.0f, 0.0f, 0.0f, 0.0f });

		// YAxis
		drawLine(mYAxis[0], mYAxis[1], mLabelColor, 1);

		// XAxis
		drawLine(mXAxis[0], mXAxis[1], mLabelColor, 1);

		// Bars
		Color barColor = mBarColor;
		for (auto it = mBars.begin(); it != mBars.end(); ++it)
		{
			Rect<float> r = (*it).second;
			Rect<float> panel = mPanelsValue[(*it).first];
			Rect<float> text = mTexts[(*it).first];
			std::vector<Vector2> tri = mTriangles[(*it).first];
			std::vector<Vector2> dash = mSeparationDashes[(*it).first];
			Color c = mValues[(*it).first].color;
			
			// Bar
			drawSquare(Vector2(r.x, r.y), r.w, r.h, c, { 0.0f, 0.0f, 0.0f, 0.0f });

			// Separation dashed
			drawLine(dash[1], dash[0], mLabelColor, 1, 4);

			// Panel
			drawSquare(Vector2(panel.x, panel.y), panel.w, panel.h, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f, 0.0f });
			drawPolygon(tri, { 1.0f, 1.0f, 1.0f, 1.0f, }, { 0.0f, 0.0f, 0.0f, 1.0f });

			// Key
			drawStringCentered((*it).first, Vector2(text.x, text.y), Vector2(text.w, text.h), mLabelColor, true, true);

			// Value
			drawStringCentered(tools::to_string_presision(mValues[(*it).first].value, 3), Vector2(panel.x, panel.y), Vector2(panel.w, panel.h), mLabelColor, true, true);
		}

		// draw Title
		// draw

	}

	void Histogram::onMouseClick(MouseButton button, MouseState state, int x, int y)
	{
		if (button == BUTTON_LEFT)
		{
			computeState();
		}
	}
}
