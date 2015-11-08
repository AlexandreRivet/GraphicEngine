#include "UI/InputText.h"

namespace UI
{
	InputText::InputText(float _x, float _y, float _width, float _height, Type _ref)
		: Element(_x, _y, _width, _height, _ref),
		lblColor({ 1.0f, 0.0f, 0.0f, 1.0f }),
		mPosCursor(0),
		mSelection(0, 0),
		mSelected(false),
		mText("Test pour le cursor")
	{

	}

	void InputText::computeState()
	{

	}

	void InputText::draw()
	{
		// auto thickeness = 2.0f;
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

				drawLine(Vector2(static_cast<float>(cursorX), mViewportRect.y + 2), Vector2(cursorX, mViewportRect.y + mViewportRect.h - 4), lblColor, 1.0);
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
				mSelection = Vector2(otherPos, mPosCursor);
			else
				mSelection = Vector2(mPosCursor, otherPos);
		}
	}

}