#include "UI/Checkbox.h"

#include "Utils/utils.h"

namespace UI
{
	Checkbox::Checkbox(bool* toggleFlag, float _x, float _y, float _width, float _height, Type _ref)
		: Element(_x, _y, _width, _height, _ref),
		mIsChecked(false),
        mToggleflag(toggleFlag)
	{
        if (mToggleflag != nullptr)
			mIsChecked = *mToggleflag;
    }

	void Checkbox::draw()
	{
		auto thickeness = 3;
		// Contour
        drawSquare(Vector2(mViewportRect.x, mViewportRect.y), static_cast<int>(mViewportRect.w), static_cast<int>(mViewportRect.h), { 0.3f, 0.3f, 0.3f, 1.0f }, { 0.0f, 0.0f, 0.0f, 1.0f });

		// Background
		drawSquare(Vector2(mViewportRect.x + 3.0f, mViewportRect.y + 3.0f), static_cast<int>(mViewportRect.w - 2.0f * thickeness), static_cast<int>(mViewportRect.h - 2.0f * thickeness), mBackgroundColor, { 0.0, 0.0, 0.0, 1.0 });

		Color checked(0.8f, 0.8f, 0.8f, 1.0f);
		if (mIsChecked)
			checked = { 0.0f, 0.0f, 0.0f, 1.0f };

		// Tick
		std::vector<Vector2> firstpoly;
		firstpoly.push_back(Vector2(mViewportRect.x + thickeness + 1.0f, mViewportRect.y + 2.0f * mViewportRect.h / 3.0f));
		firstpoly.push_back(Vector2(mViewportRect.x + 1.0f * mViewportRect.w / 3.0f, mViewportRect.y + mViewportRect.h - thickeness - 1.0f));
		firstpoly.push_back(Vector2(mViewportRect.x + 1.0f * mViewportRect.w / 3.0f + 3.0f, mViewportRect.y + mViewportRect.h - thickeness - 4.0f));
		firstpoly.push_back(Vector2(mViewportRect.x + thickeness + 4.0f, mViewportRect.y + 2.0f * mViewportRect.h / 3.0f - 3.0f));
		drawPolygon(firstpoly, checked, { 0.0, 0.0, 0.0, 1.0 });

		std::vector<Vector2> secondPoly;
		secondPoly.push_back(Vector2(mViewportRect.x + 1.0f * mViewportRect.w / 3.0f, mViewportRect.y + mViewportRect.h - thickeness - 1.0f));
		secondPoly.push_back(Vector2(mViewportRect.x + mViewportRect.w - thickeness - 1.0f, mViewportRect.y + 1.0f * mViewportRect.w / 3.0f));
		secondPoly.push_back(Vector2(mViewportRect.x + mViewportRect.w - thickeness - 4.0f, mViewportRect.y + 1.0f * mViewportRect.w / 3.0f - 3.0f));
		secondPoly.push_back(Vector2(mViewportRect.x + 1.0f * mViewportRect.w / 3.0f - 3.0f, mViewportRect.y + mViewportRect.h - thickeness - 4.0f));
		drawPolygon(secondPoly, checked, { 0.0, 0.0, 0.0, 1.0 });
		
	}

    void Checkbox::setToggleFlag(bool* tf)
    {
        mToggleflag = tf;

        if (mToggleflag != nullptr)
            mIsChecked = *mToggleflag;
    }

    void Checkbox::onMouseClick(MouseButton button, MouseState state, int x, int y)
    {
        if (button == BUTTON_LEFT && state == MOUSE_DOWN)
        {
            mIsChecked = !mIsChecked;

            if (mToggleflag != nullptr)
            {
                *mToggleflag = !(*mToggleflag);
            }
        }

        tools::unusedArg(x, y);
    }

}