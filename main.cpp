#include <iostream>
#include "pgr.h"
#include "mesh.h"
#include "camera.h"
#include "shader.h"

namespace copakond {
    const int WIN_WIDTH = 512;
    const int WIN_HEIGHT = 512;
    const char* WIN_TITLE = "Hello World";

    uint64_t time = 0;
    std::vector<Mesh> meshes = {};
    Shader shader = Shader();
    Camera camera(
        glm::vec3(0.0f, 0.0f, 5.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        100.0f
    );

    float updateTime() {
        int currentFrameTime = glutGet(GLUT_ELAPSED_TIME);
        time = currentFrameTime;
        return (currentFrameTime - time) / 1000.0f; // delta time
    }

    void init() {
        glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

        GLuint shaderPrg = shader.init(
            "shaders/vertexShader.vert",
            "shaders/fragmentShader.frag"
        );

        Mesh triangleMesh = Mesh();
        meshes.push_back(triangleMesh);

        for (Mesh& mesh: meshes) {
            mesh.init(shaderPrg);
        }
    }

    void draw() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.draw(camera, WIN_WIDTH, WIN_HEIGHT);

        for (Mesh& mesh: meshes) {
            mesh.draw(WIN_WIDTH, WIN_HEIGHT);
        }

        glutSwapBuffers(); // swap front and back screen buffer
    }

    void keyboardInputEvent(unsigned char key, int x, int y) {
        //float deltaTime = glutGet(GLUT_ELAPSED_TIME);
        float deltaTime = 0.1;

        switch (key) {
            case 'w': case 'W':
                camera.processKeyboard(FRONT, deltaTime); break;
            case 's': case 'S':
                camera.processKeyboard(BACK, deltaTime); break;
            case 'a': case 'A':
                camera.processKeyboard(LEFT, deltaTime); break;
            case 'd': case 'D':
                camera.processKeyboard(RIGHT, deltaTime); break;
            case 27: // ESC
                glutLeaveMainLoop(); break;
        }

        glutPostRedisplay();
    }

    void specKeyboardInputEvent(int key, int x, int y) {
        //float deltaTime = glutGet(GLUT_ELAPSED_TIME);
        float deltaTime = 0.1;

        switch (key) {
            case GLUT_KEY_UP:
                camera.processKeyboard(FRONT, deltaTime); break;
            case GLUT_KEY_DOWN:
                camera.processKeyboard(BACK, deltaTime); break;
            case GLUT_KEY_LEFT:
                camera.processKeyboard(LEFT, deltaTime); break;
            case GLUT_KEY_RIGHT:
                camera.processKeyboard(RIGHT, deltaTime); break;
        }

        glutPostRedisplay();
    }

    void mouseMoveEvent(int x, int y) {
        int centerX = WIN_WIDTH / 2;
        int centerY = WIN_HEIGHT / 2;

        if (x == centerX && y == centerY) return;

        float deltaX = (float)(x - centerX);
        float deltaY = (float)(centerY - y);

        camera.processMouseMovement(deltaX, deltaY);

        glutWarpPointer(centerX, centerY);
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(copakond::WIN_WIDTH, copakond::WIN_HEIGHT);
    glutCreateWindow(copakond::WIN_TITLE);

    glutKeyboardFunc(copakond::keyboardInputEvent);
    glutSpecialFunc(copakond::specKeyboardInputEvent);
    glutPassiveMotionFunc(copakond::mouseMoveEvent);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutDisplayFunc(copakond::draw);

    if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
        pgr::dieWithError("pgr init failed, required OpenGL not supported?");

    copakond::init();

    std::cout << "Hello triangle!" << std::endl;

    glutMainLoop();
    return 0;
}
