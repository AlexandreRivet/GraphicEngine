#include "UI/Element.h"

#include <algorithm>

namespace UI
{

	Element::Element(float x, float y, float width, float height, Type _ref)
		: mLocalRect(RefValue(x, _ref), RefValue(y, _ref), RefValue(width, _ref), RefValue(height, _ref)),
		mViewportRect(0, 0, 0, 0),
        mParent(nullptr),
		mBackgroundColor(1.0, 1.0, 1.0, 1.0),
		mNeedUpdate(true),
		mVisible(true)
    {}

	Element::Element(const Rect<RefValue>& localRect)
		: mLocalRect(localRect),
		mViewportRect(0, 0, 0, 0),
		mParent(nullptr),
		mBackgroundColor(1.0, 1.0, 1.0, 1.0),
		mVisible(true)
	{}

	bool Element::setStyle(std::string style)
	{
		std::transform(style.begin(), style.end(), style.begin(), ::tolower);		// pour sécuriser ce qu'envoit l'utilisateur
		style.erase(std::remove_if(style.begin(), style.end(), [](char c)
		{
			return c == ' ';
		}), style.end());

		std::vector<std::string> elements( Utils::split(style, ';') );	// split en fonction du ;

		for (auto element = elements.begin(); element != elements.end(); ++element)
		{
			std::vector<std::string> keyValue(Utils::split(*element, ':'));
			
			if (keyValue.size() != 2)
				return false;

			std::string& key = keyValue.front();
			std::string& value = keyValue.back();

			if (value.size() < 2)
				return false;

			auto lastLetter = value.substr(value.length() - 2, 2);

			float floatValue;
			Type type;

			if (lastLetter.back() == '%')
			{
				floatValue = static_cast<float>(::atof(value.substr(0, value.length() - 1).c_str()));
				type = PERCENT;
			}
			else if (lastLetter.front() == 'p' && lastLetter.back() == 'x')
			{
				if (value.size() < 3)
					return false;

				floatValue = static_cast<float>(::atof(value.substr(0, value.length() - 2).c_str()));
				type = PIXEL;
			}
			else
			{
				return false;
			}

			RefValue* valueToFill = nullptr;


			if (key == "x")
			{
				valueToFill = &mLocalRect.x;
			}
			else if (key == "y")
			{
				valueToFill = &mLocalRect.y;
			}
			else if (key == "width")
			{
				valueToFill = &mLocalRect.w;
			}
			else if (key == "height")
			{
				valueToFill = &mLocalRect.h;
			}

			if (valueToFill == nullptr)
				return false;

			valueToFill->value = floatValue;
			valueToFill->ref = type;			
		}

		return true;

	}

	void Element::setNeedUpdate(bool update)
	{
		mNeedUpdate = update;
	}


	void Element::computePosition(float w, float h)			// au cas où pour gérer
	{
		// Mise à jour de la position finale
		if (mNeedUpdate)
		{
			if (mParent == nullptr)
			{
				mViewportRect.x = ((mLocalRect.x.ref == PERCENT) ? w * mLocalRect.x.value / 100.0f : mLocalRect.x.value);
				mViewportRect.y = ((mLocalRect.y.ref == PERCENT) ? h * mLocalRect.y.value / 100.0f : mLocalRect.y.value);
				mViewportRect.w = ((mLocalRect.w.ref == PERCENT) ? w * mLocalRect.w.value / 100.0f : mLocalRect.w.value);
				mViewportRect.h = ((mLocalRect.h.ref == PERCENT) ? h * mLocalRect.h.value / 100.0f : mLocalRect.h.value);
			}
			else
			{
				float x_p = mParent->mViewportRect.x;
				float y_p = mParent->mViewportRect.y;
				float w_p = mParent->mViewportRect.w;
				float h_p = mParent->mViewportRect.h;

				mViewportRect.x = ((mLocalRect.x.ref == PERCENT) ? w_p * mLocalRect.x.value / 100.0f : mLocalRect.x.value) + x_p;
				mViewportRect.y = ((mLocalRect.y.ref == PERCENT) ? h_p * mLocalRect.y.value / 100.0f : mLocalRect.y.value) + y_p;
				mViewportRect.w = ((mLocalRect.w.ref == PERCENT) ? w_p * mLocalRect.w.value / 100.0f : mLocalRect.w.value);
				mViewportRect.h = ((mLocalRect.h.ref == PERCENT) ? h_p * mLocalRect.h.value / 100.0f : mLocalRect.h.value);
			}

			computeState();

			int numberChildren = mChildren.size();
			for (int i = 0; i < numberChildren; ++i)
			{
				mChildren[i]->setNeedUpdate(true);
			}

			mNeedUpdate = false;

		}
		
		// Mise à jour de la position des fils
		int numberChildren = mChildren.size();
		for (int i = 0; i < numberChildren; ++i)
		{
			mChildren[i]->computePosition(w, h);
		}

	}

	void Element::computeState()
	{

	}

	void Element::setParent(Element* element)
	{
		mParent = element;
	}

	void Element::addElement(Element* element)
	{
		element->setParent(this);
		mChildren.push_back(element);	
	}

	void Element::render()
	{
		if (!mVisible)
			return;

		draw();

		int numberChildren = mChildren.size();
		for (int i = 0; i < numberChildren; ++i)
		{
			mChildren[i]->render();
		}
	}

    const Element* Element::getParent() const
    {
        return mParent;
    }

    Element* Element::getParent()
    {
        return mParent;
    }

    const std::vector<Element*>& Element::getChildren() const
    {
        return mChildren;
    }

    std::vector<Element*>& Element::getChildren()
    {
        return mChildren;
    }

    const Rect<float>& Element::getViewportBounds() const
    {
        return mViewportRect;
    }
}