#ifndef PGR_SEM_COPAKOND_SCENE_H
#define PGR_SEM_COPAKOND_SCENE_H

// all virtual methods that needs to be implemented
class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void init() {}
    virtual void update(float deltaTime) {}
    virtual void physics_update(float deltaTime) {}
    virtual void draw() {}

    virtual void onKeyboardEvent(unsigned char key, int x, int y, bool isDown) {}
    virtual void onSpecialKeyEvent(int key, int x, int y, bool isDown) {}
    virtual void onMouseButtonEvent(int button, int state, int x, int y) {}

    virtual void onScreenResize(int width, int height) {}
};


#endif //PGR_SEM_COPAKOND_SCENE_H
