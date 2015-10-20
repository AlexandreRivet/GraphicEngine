#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <functional>

#include "Element.h"

namespace UI
{
	class Button : public Element
	{
	public:

		Button(const std::string& _label, const std::function<void(char, char, int, int)>& f, float _x, float _y, float _width, float _height, Type _ref = PIXEL);

		void draw();

		bool isPressed;
        
        const std::string& getLabel() const;
        void setCallBack(const std::function<void(char, char, int, int)>& c);

        virtual void onMouseClick(int button, int state, int x, int y);
	private:
		std::string label;
		bool isHightlighted;
		// bool isPressed;
        std::function<void(int, int, int, int)> m_callBack;

		Color bgColor;
		Color lblColor;
	};


}

#endif