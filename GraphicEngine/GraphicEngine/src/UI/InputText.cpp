#include "UI/InputText.h"

namespace UI
{
	InputText::InputText(float _x, float _y, float _width, float _height, Type _ref)
		: Element(_x, _y, _width, _height, _ref),
		lblColor({ 0.0f, 0.0f, 0.0f, 1.0f }),
		mPosCursor(0),
		mSelection(0, 0),
		mSelected(false)
	{

	}

	void InputText::setText(const std::string& text)
	{
		mText = text;
	}

	const std::string& InputText::getText() const
	{
		return mText;
	}

	void InputText::computeState()
	{

	}

	void InputText::draw()
	{
		drawSquare(Vector2(mViewportRect.x, mViewportRect.y), static_cast<int>(mViewportRect.w), static_cast<int>(mViewportRect.h), mBackgroundColor, { 0.0f, 0.0f, 0.0f, 1.0f });

		if (mSelected) 
		{
			int start = static_cast<int>(mSelection.x);
			int end = static_cast<int>(mSelection.y);

			// First part
			drawStringCentered(mText.substr(0, start), Vector2(mViewportRect.x + 2, mViewportRect.y), Vector2(mViewportRect.w, mViewportRect.h), lblColor, false, true);

			// Selected
			int start_selected = getXCoordInString(mText, Vector2(mViewportRect.x + 2, mViewportRect.y), start);
			int end_selected = getXCoordInString(mText, Vector2(mViewportRect.x + 2, mViewportRect.y), end);

			drawSquare(Vector2(static_cast<float>(start_selected), mViewportRect.y + 2.0f), end_selected - start_selected, static_cast<int>(mViewportRect.h) - 4, { 1.0f - mBackgroundColor.r, 1.0f - mBackgroundColor.g, 1.0f - mBackgroundColor.b, mBackgroundColor.a }, { 0.0f, 0.0f, 0.0f, 1.0f });
			drawStringCentered(mText.substr(start, end - start), Vector2(static_cast<float>(start_selected), mViewportRect.y), Vector2(mViewportRect.w, mViewportRect.h), { 1.0f - lblColor.r, 1.0f - lblColor.g, 1.0f - lblColor.b, lblColor.a }, false, true);

			// Last part
			drawStringCentered(mText.substr(end), Vector2(static_cast<float>(end_selected), mViewportRect.y), Vector2(mViewportRect.w, mViewportRect.h), lblColor, false, true);

		}
		else
		{
			if (mText.size() == 0) 
			{
				drawStringCentered("Text here...", Vector2(mViewportRect.x + 2, mViewportRect.y), Vector2(mViewportRect.w, mViewportRect.h), { 0.7f, 0.7f, 0.7f, 1.0f }, false, true);
			}
			else 
			{
				drawStringCentered(mText, Vector2(mViewportRect.x + 2, mViewportRect.y), Vector2(mViewportRect.w, mViewportRect.h), lblColor, false, true);

				int cursorX = getXCoordInString(mText, Vector2(mViewportRect.x + 2, mViewportRect.y), mPosCursor);

				drawLine(Vector2(static_cast<float>(cursorX), mViewportRect.y + 2.f), Vector2((float)cursorX, mViewportRect.y + mViewportRect.h - 4.f), lblColor, 1.0f);
			}
			
		}
	}

    void InputText::onMouseClick(MouseButton button, MouseState state, const Vector2& mousePosition)
	{
		if (button == BUTTON_LEFT && state == MOUSE_DOWN)
		{
			// Calcul du curseur
            mPosCursor = getPosInString(mText, mViewportRect.x, mousePosition.x);

			if (mSelected)
				mSelected = false;
		}
	}

    void InputText::onMouseDrag(const Vector2& mousePosition)
	{
		int otherPos = getPosInString(mText, mViewportRect.x, mousePosition.x);

		if (otherPos < 0)
			otherPos = 0;
		if (mPosCursor < 0)
			mPosCursor = 0;

		if (otherPos != mPosCursor)
		{
			mSelected = true;
			if (otherPos < mPosCursor)
				mSelection = Vector2((float)otherPos, (float)mPosCursor);
			else
				mSelection = Vector2((float)mPosCursor, (float)otherPos);
		}
	}

	void InputText::keyPressed(const char c)
	{
		switch (c)
		{
		case 8:
			if (mSelected)
			{
				mText.erase(mText.begin() + mSelection.x, mText.begin() + mSelection.y);
				mPosCursor = mSelection.x;
				mSelected = false;
			}
			else
			{
				mPosCursor--;
				if (mPosCursor < 0)
					mPosCursor = 0;
				else
					mText.erase(mPosCursor, 1);
			}
			break;
		default:
			if (mSelected)
			{
				mText.erase(mText.begin() + mSelection.x, mText.begin() + mSelection.y);
				mPosCursor = mSelection.x;
				mSelected = false;
			}

			mText.insert(mPosCursor, 1, c);
			mPosCursor++;
			break;
		}		
	}

	void InputText::keyReleased(const char)
	{

	}

	void InputText::specialPressed(const char c)
	{
		switch (c)
		{
		case 100:
			mPosCursor--;
			break;
		case 102:
			mPosCursor++;
			break;
		case 106:
			mPosCursor = 0;
			break;
		case 107:
			mPosCursor = mText.size();
		}
		

		if (mPosCursor < 0)
			mPosCursor = 0;
		else if ((size_t)mPosCursor > mText.size())
			mPosCursor = (int)mText.size();
	}

	void InputText::specialReleased(const char)
	{

	}

}