#ifndef _UI_UIMANAGER_H_
#define _UI_UIMANAGER_H_

#include <stack>

#include "Layout.h"

namespace UI
{
    class UIManager
    {
    public:
        UIManager();

        Element* getRoot();
		Element* getLastMouseOverElement();

        void render();
        void computePosition(float w, float h);

        void onMouseClick(int button, int state, int x, int y);
        /**
         * Need mouse button pushed
         */
        void onMouseDrag(int x, int y);
        void onMouseMove(int x, int y);
		void keyPressed(char c, bool special);
		void keyReleased(char c, bool special);

    private:
        Layout m_root;

        std::map<MouseButton, std::vector<Element*>> m_lastOnClickElems;
        Element* m_lastMouseOverElement;
		Element* m_onFocusElement;

        Element* findPreciseUIElementInChild(Element* current, const Vector2& mousePosition, bool onEnter = true);
        Element* findPreciseUIElementInParent(Element* current, const Vector2& mousePosition, bool onExit = true);
    };
}
#endif