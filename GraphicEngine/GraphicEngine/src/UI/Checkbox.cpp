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

	void Checkbox::computeState()
	{
		// Background
		mFirstRect = Rect<float>(mViewportRect.x, mViewportRect.y, mViewportRect.w, mViewportRect.h);

		// Tick
		mTickPolys.clear();

		mTickPolys.push_back(std::vector<Vector2>());
		mTickPolys.back().push_back(Vector2(mViewportRect.x + 1.0f, mViewportRect.y + 2.0f * mViewportRect.h / 3.0f));
		mTickPolys.back().push_back(Vector2(mViewportRect.x + 1.0f * mViewportRect.w / 3.0f, mViewportRect.y + mViewportRect.h - 1.0f));
		mTickPolys.back().push_back(Vector2(mViewportRect.x + 1.0f * mViewportRect.w / 3.0f + 3.0f, mViewportRect.y + mViewportRect.h - 4.0f));
		mTickPolys.back().push_back(Vector2(mViewportRect.x + 4.0f, mViewportRect.y + 2.0f * mViewportRect.h / 3.0f - 3.0f));

		mTickPolys.push_back(std::vector<Vector2>());
		mTickPolys.back().push_back(Vector2(mViewportRect.x + 1.0f * mViewportRect.w / 3.0f, mViewportRect.y + mViewportRect.h - 1.0f));
		mTickPolys.back().push_back(Vector2(mViewportRect.x + mViewportRect.w - 1.0f, mViewportRect.y + 1.0f * mViewportRect.w / 3.0f));
		mTickPolys.back().push_back(Vector2(mViewportRect.x + mViewportRect.w - 4.0f, mViewportRect.y + 1.0f * mViewportRect.w / 3.0f - 3.0f));
		mTickPolys.back().push_back(Vector2(mViewportRect.x + 1.0f * mViewportRect.w / 3.0f - 3.0f, mViewportRect.y + mViewportRect.h - 4.0f));
	}

	void Checkbox::draw()
	{
		// Background
		drawSquare(Vector2(mFirstRect.x, mFirstRect.y), static_cast<int>(mFirstRect.w), static_cast<int>(mFirstRect.h), mBackgroundColor, { 0.0f, 0.0f, 0.0f, 1.0f });

		// Tick
		Color checked(0.8f, 0.8f, 0.8f, 1.0f);
		if (mIsChecked)
			checked = { 0.0f, 0.0f, 0.0f, 1.0f };
		
		drawPolygon(mTickPolys[0], checked, { 0.0f, 0.0f, 0.0f, 1.0f });
		drawPolygon(mTickPolys[1], checked, { 0.0f, 0.0f, 0.0f, 1.0f });
		
	}

    void Checkbox::setToggleFlag(bool* tf)
    {
        mToggleflag = tf;

        if (mToggleflag != nullptr)
            mIsChecked = *mToggleflag;
    }

    void Checkbox::onMouseClick(MouseButton button, MouseState state, const Vector2& mousePosition)
    {
        if (button == BUTTON_LEFT && state == MOUSE_DOWN)
        {
            mIsChecked = !mIsChecked;

			computeState();

            if (mToggleflag != nullptr)
            {
                *mToggleflag = !(*mToggleflag);
            }
        }

        tools::unusedArg(mousePosition);
    }

}