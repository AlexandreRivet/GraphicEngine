#ifndef _UI_UIMANAGER_H_
#define _UI_UIMANAGER_H_

#include "Layout.h"

namespace UI
{
    class UIManager
    {
    public:
        UIManager();

        Element* getRoot();

        void render();
        void computePosition(float w, float h);

        void onMouseClick(int button, int state, int x, int y);
        /**
         * Need mouse button pushed
         */
        void onMouseDrag(int x, int y);
        void onMouseMove(int x, int y);

    private:
        Layout m_root;

        std::map<MouseButton, Element*> m_lastOnClickElems;

        bool hasClicked(MouseButton button, MouseState state, const Vector2& mouse, Element* e);
    };
}
#endif