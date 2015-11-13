#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include "prerequisites.h"
#include <functional>

#include "Shapes.h"

#include "Utils/Utils.h"
#include "Utils/Rect.h"

namespace UI
{
	enum Type {PIXEL, PERCENT};

	enum MouseState{MOUSE_UP, MOUSE_DOWN};

	enum MouseButton{BUTTON_LEFT, BUTTON_MIDDLE, BUTTON_RIGHT};

	struct RefValue
	{
		float value;
		Type ref;

		RefValue(float _value, Type _ref)
			: value(_value),
			ref(_ref)
		{}
	};

    class Element
    {
    public:
        Element(float x, float y, float width, float height, Type _ref = PIXEL);
		Element(const Rect<RefValue>& localRect);		

        virtual bool Element::setStyle(std::string style);		// non const because of clean up the string
        void computePosition(float w, float h);					// TODO: change when we will have context for OpenGL App
		virtual void computeState();

		void setNeedUpdate(bool update);
        void setParent(Element* element);
        void addElement(Element* element);
		const Element* getParent() const;
		Element* getParent();
		const std::vector<Element*>& getChildren() const;
		std::vector<Element*>& getChildren();

		void setVisible(bool visible);
        bool isVisible() const;

        void render();
        virtual void draw() = 0;

        const Rect<float>& getViewportBounds() const;

        /**
         * Mouse Graphic event
         */
        virtual void onMouseClick(MouseButton button, MouseState state, const Vector2& mousePosition){ tools::unusedArg(button, state, mousePosition); };
        virtual void onMouseEnter(const Vector2& mousePosition){ tools::unusedArg(mousePosition); };
        virtual void onMouseExit(const Vector2& mousePosition){ tools::unusedArg(mousePosition); };
		virtual void onMouseDrag(const Vector2& mousePosition){ tools::unusedArg(mousePosition); };
		virtual void keyPressed(const char c) { tools::unusedArg(c); };
		virtual void keyReleased(const char c) { tools::unusedArg(c); };
		virtual void specialPressed(const char c) { tools::unusedArg(c); };
		virtual void specialReleased(const char c) { tools::unusedArg(c); };

	protected:

		Rect<RefValue> mLocalRect;					// Rect local

		Rect<float> mViewportRect;					// Rect in the viewport

		Element* mParent;							// Parent of the element
		std::vector<Element*> mChildren;			// List of element children of this

		bool mNeedUpdate;							// Have to recompute viewport rect
		bool mVisible;								// Draw or not this element and children 

		// List of style
		Color mBackgroundColor;
	};

}

#endif
