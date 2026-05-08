#include <iostream>
#include <algorithm>
#include "pgr-portable.h"
#include "meshes/mesh.h"
#include "meshes/model/objMesh.h"
#include "meshes/label/textLabel.h"
#include "meshes/label/imageSequenceLabel.h"
#include "geometry/camera.h"
#include "light/light.h"
#include "parser/input.h"
#include "shaders/shader.h"
#include "animation/spline.h"
#include "animation/catmullroll.h"
#include "animation/bezier.h"
#include "meshes/collision/collisionBox.h"
#include "meshes/collision/collisionSphere.h"
#include "meshes/collision/rigidBody.h"
#include "meshes/collision/rigidSphere.h"
#include "meshes/label/imageLabel.h"
#include "meshes/label/imageMoving.h"
#include "meshes/model/skybox.h"
#include "scenes/sampleScene.h"
#include "scenes/scene.h"

namespace copakond {
    void menuCallback(int option);

    int winWidth = 1280;
    int winHeight = 720;

    Shader* shader;
    Input* input;
    Scene* currentScene;

    void init() {
        glutCreateMenu(menuCallback);
        glutAddMenuEntry("Player Cam", 1);
        glutAddMenuEntry("Catmull Roll Cam", 2);
        glutAddMenuEntry("Static Cam 1", 3);
        glutAddMenuEntry("Static Cam 2", 4);
        glutAddMenuEntry("Full Screen", 5);
        glutAddMenuEntry("Exit Game", 6);
        glutAttachMenu(GLUT_RIGHT_BUTTON);

        Camera *camera = new Camera(
            glm::vec3(0.0f, 0.0f, 5.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            1000.0f
        );

        input = new Input(*camera, winWidth, winHeight);
        shader = new Shader();
        currentScene = new SampleScene("Sample Scene", input, shader, winWidth, winHeight);

        GLuint shaderUID = shader->init(
            "shaders/shaders/shader.vert",
            "shaders/shaders/shader.frag"
        );

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

        currentScene->init();

        for (Mesh *mesh: currentScene->getMeshes()) {
            mesh->init(shaderUID);
        }

        std::vector<Light*> lights = currentScene->getLights();
        for (size_t i = 0; i < lights.size(); i++) {
            shader->setLight(lights[i], i);
        }

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glCullFace( GL_BACK);
        glEnable(GL_CULL_FACE);

        // enable stencil test for mouse clicking
        glEnable(GL_STENCIL_TEST);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    }

    void draw() {
        Camera camera = currentScene->getCamera();
        float deltaTime = currentScene->updateTime(); // calculate delta time

        // update spline animations
        for (Spline *spline: currentScene->getSplines()) {
            spline->update(deltaTime);
        }

        // update lights
        for (Light *light: currentScene->getLights()) {
            shader->updateLight(light);
        }

        // process physics
        std::vector<CollisionShape*> colliders = currentScene->getColliders();
        for (CollisionShape *collider: colliders) {
            auto *rigBody = dynamic_cast<RigidBody*>(collider);
            auto *rigSphere = dynamic_cast<RigidSphere*>(collider);
            if (rigBody != nullptr) { rigBody->physics_process(deltaTime, colliders); }
            if (rigSphere != nullptr) { rigSphere->physics_process(deltaTime, colliders); }
        }

        currentScene->physics_update(deltaTime);
        currentScene->update(deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // sort all meshes, from the furthest to the nearest (for transparent meshes), all meshes, could be optimized more...
        std::vector<Mesh*> meshes = currentScene->getMeshes();
        glm::vec3 camPos = camera.getPosition();
        std::sort(meshes.begin(), meshes.end(), [&camPos](Mesh* a, Mesh* b) {
                glm::vec3 pos1 = glm::vec3(a->getModelMatrix()[3]); // position
                glm::vec3 pos2 = glm::vec3(b->getModelMatrix()[3]); // position

                return glm::distance(camPos, pos1) > glm::distance(camPos, pos2);
        });

        // draw Non-transparent Meshes
        shader->update(camera, winWidth, winHeight, deltaTime); // use main shader
        for (Mesh *mesh: meshes) {
            if (mesh->getMaterial()->getAlpha() <= 0.999f) { continue; }
            if (dynamic_cast<const TextLabel*>(mesh) != nullptr) { continue; }
            glStencilFunc(GL_ALWAYS, mesh->getId(), 0);
            shader->draw(*mesh, false, deltaTime); // drawing non-transparent objects
        }

        // draw skybox
        Skybox *skybox = currentScene->getSkybox();
        float skyboxBlending = currentScene->getSkyboxBlendingCoeff();

        if (skybox) {
            glStencilFunc(GL_ALWAYS, 1, 0); // id = 1 is for skybox
            skybox->update(camera, winWidth, winHeight, deltaTime, skyboxBlending); // use skybox shader
            skybox->draw(deltaTime);
        }

        // draw Transparent Meshes
        glEnable(GL_BLEND);
        glDepthMask(GL_FALSE); // if the front triangle would render before the back it would fail

        shader->update(camera, winWidth, winHeight, 0.0f); // use main shader
        for (Mesh *mesh: meshes) {
            if (mesh->getMaterial()->getAlpha() > 0.9999f) { continue; }
            glStencilFunc(GL_ALWAYS, mesh->getId(), 0);
            shader->draw(*mesh, true, deltaTime); // drawing transparent objects
        }

        glDepthMask(GL_TRUE); // restore
        glDisable(GL_BLEND);

        glutSwapBuffers(); // swap front and back screen buffer
        glutPostRedisplay(); // !!!!!!!!! schedules display, doesnt stack!!!
    }

    void menuCallback(int option) {
        if (option == 6) {
            exit(0);
        }

        if (currentScene) { currentScene->onMenuEvent(option); }
    }

    void keyboardInputEvent(unsigned char key, int x, int y) {
        input->keyboardInputEvent(key, x, y);
    }

    void specKeyboardInputEvent(int key, int x, int y) {
        input->specKeyboardInputEvent(key, x, y);
    }

    void keyboardUpInputEvent(unsigned char key, int x, int y) {
        input->keyboardUpInputEvent(key, x, y);
    }

    void specKeyboardUpInputEvent(int key, int x, int y) {
        input->specKeyboardUpInputEvent(key, x, y);
    }

    void mouseButtonEvent(int button, int state, int x, int y) {
        input->mouseButtonEvent(button, state, x, y);
        if (currentScene) { currentScene->onMouseButtonEvent(button, state, x, y); }
    }

    void mouseMoveEvent(int x, int y) {
        input->mouseMoveEvent(x, y);
        if (currentScene) { currentScene->onMouseMoveEvent(x, y); }
    }

    void mouseWheelEvent(int wheel, int direction, int x, int y) {
        input->mouseWheelEvent(wheel, direction, x, y);
        if (currentScene) { currentScene->onMouseWheelEvent(wheel, direction, x, y); }
    }

    void screenResizeEvent(int width, int height) {
        if (width == 0) width = 1; // sadly it can be 0 for some reason.
        if (height == 0) height = 1;

        winWidth = width;
        winHeight = height;

        glViewport(0, 0, width, height);
        input->update(winWidth, winHeight);
        if (currentScene) { currentScene->onScreenResizeEvent(width, height); }
    }
}

using namespace copakond;

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize( winWidth,  winHeight);
    glutCreateWindow( "PGR Semestral Work Copakond");

    // INPUT - keyboard and mouse event callbacks
    glutKeyboardFunc( keyboardInputEvent);
    glutSpecialFunc( specKeyboardInputEvent);
    glutKeyboardUpFunc( keyboardUpInputEvent);
    glutSpecialUpFunc( specKeyboardUpInputEvent);

    glutMouseFunc( mouseButtonEvent);
    glutPassiveMotionFunc( mouseMoveEvent);
    glutMotionFunc( mouseMoveEvent);
    glutMouseWheelFunc( mouseWheelEvent);
    glutSetCursor(GLUT_CURSOR_NONE); // hide cursor

    // SET DRAW CALLBACK
    glutDisplayFunc(draw);

    if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR)) {
        pgr::dieWithError("pgr init failed, required OpenGL not supported?");
    }

    init();

    glutMainLoop();
    return 0;
}
