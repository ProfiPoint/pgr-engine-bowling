#ifndef PGR_SEM_COPAKOND_CONTROLLER_H
#define PGR_SEM_COPAKOND_CONTROLLER_H

namespace copakond {
    class Controller {
    public:
        Controller() = default;
        virtual ~Controller() = default;

        virtual void update(float deltaTime) = 0;

        virtual void onMouseButtonEvent(int button, int state, int x, int y) {}
        virtual void onMouseMoveEvent(int x, int y) {}
        virtual void onSpecialKeyEvent(int key, int x, int y, bool isDown) {}
        virtual void onKeyboardEvent(unsigned char key, int x, int y, bool isDown) {}
    };
}

#endif //PGR_SEM_COPAKOND_CONTROLLER_H
