#include "UI/Button.h"

namespace UI
{
    Button::Button(const std::string& label, const std::function<void(char, char, const Vector2& mousePosition)>& f, float x, float y, float width, float height, Type ref)
		: Element(x, y, width, height, ref),
		mLabel(label),
		mCallBack(f),
		mIsPressed(false),
		mIsHightlighted(false),
		mLabelColor(1.0, 1.0, 1.0, 1.0),
		mIs3D(true)
	{
		mBackgroundColor = ColorStruct(0.204f, 0.596f, 0.859f, 1.0f);
	}

    Button::Button(const std::string& label, const std::function<void(char, char, const Vector2& mousePosition)>& f, const Rect<RefValue>& localRect)
		: Element(localRect),
		mLabel(label),
		mCallBack(f),
		mIsPressed(false),
		mIsHightlighted(false),
		mLabelColor(1.0f, 1.0f, 1.0f, 1.0f),
		mIs3D(true)
	{
		mBackgroundColor = ColorStruct(0.204f, 0.596f, 0.859f, 1.0f);
	}

	void Button::computeState()
	{
		float percent = 1.0f;
		if (mIs3D)
			percent = 0.8f;
		float other_percent = 1.0f - percent;

		mFirstRect = Rect<float>(mViewportRect.x, mViewportRect.y, mViewportRect.w, mViewportRect.h * percent);
		mSecondRect = Rect<float>(mViewportRect.x, mViewportRect.y + mFirstRect.h, mViewportRect.w, mViewportRect.h * other_percent);

		if (mIsPressed && mIs3D) 
		{
			other_percent /= 2.0f;

			mFirstRect.y += mViewportRect.h * (1.0f - percent - other_percent);

			mSecondRect.y += mViewportRect.h * (1.0f - percent - other_percent);
			mSecondRect.h = mViewportRect.h * other_percent;
		}

	}

	void Button::draw()
	{
		// Rect principal bouton
		drawSquare(Vector2(mFirstRect.x, mFirstRect.y), static_cast<int>(mFirstRect.w), static_cast<int>(mFirstRect.h), mBackgroundColor, { 1.0f, 0.0f, 0.0f, 0.0f });

		// Effet 3D
		ColorStruct secondSquare(mBackgroundColor.r - 0.2f, mBackgroundColor.g - 0.2f, mBackgroundColor.b - 0.2f, mBackgroundColor.a);
		drawSquare(Vector2(mSecondRect.x, mSecondRect.y), static_cast<int>(mSecondRect.w), static_cast<int>(mSecondRect.h), secondSquare, { 1.0f, 0.0f, 0.0f, 0.0f });
		
		// Survol => ombre
		if (mIsHightlighted)
			drawStringCentered(mLabel, Vector2(mFirstRect.x + 1, mFirstRect.y + 1), Vector2(mFirstRect.w, mFirstRect.h), { 0.0f, 0.0f, 0.0f, 0.0f }, true, true);

		// Label du texte
		drawStringCentered(mLabel, Vector2(mFirstRect.x, mFirstRect.y), Vector2(mFirstRect.w, mFirstRect.h), mLabelColor, true, true);
	}

    const std::string& Button::getLabel() const
    {
        return mLabel;
    }

	void Button::setLabel(const std::string& label)
	{
		mLabel = label;
	}

	void Button::set3D(bool is3D)
	{
		mIs3D = is3D;
	}

    void Button::setCallBack(const std::function<void(MouseButton, MouseState, const Vector2& mousePosition)>& c)
    {
        mCallBack = c;
    }

    void Button::onMouseClick(MouseButton button, MouseState state, const Vector2& mousePosition)
    {
        if (button == BUTTON_LEFT)
        {
            mIsPressed = !mIsPressed;

			computeState();

            if (state == MOUSE_DOWN)
                mCallBack(button, state, mousePosition);
        }
    }

	void Button::onMouseEnter(const Vector2& mousePosition)
	{
		mIsHightlighted = true;
	}

	void Button::onMouseExit(const Vector2& mousePosition)
	{
		mIsHightlighted = false;
	}

}
