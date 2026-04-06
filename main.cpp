#include <iostream>
#include "pgr.h"
#include "mesh.h"
#include "camera.h"

namespace copakond {
    const int WIN_WIDTH = 512;
    const int WIN_HEIGHT = 512;
    const char* WIN_TITLE = "Hello World";

    uint64_t time = 0;
    std::vector<Mesh> meshes = {};
    GLuint shader = -1;
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

        GLuint shaders[] = {
            pgr::createShaderFromFile(GL_VERTEX_SHADER, "shaders/vertexShader.vert"),
            pgr::createShaderFromFile(GL_FRAGMENT_SHADER, "shaders/fragmentShader.frag"),
            0
        };

        shader = pgr::createProgram(shaders);

        Mesh triangleMesh;
        meshes.push_back(triangleMesh);

        for (Mesh& mesh: meshes) {
            mesh.init(shader);
        }


    }

    void draw() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (Mesh& mesh: meshes) {
            mesh.draw(WIN_WIDTH, WIN_HEIGHT);
        }

        glutSwapBuffers(); // swap front and back screen buffer
    }

    void keyboardInputEvent(unsigned char key, int x, int y) {
        float deltaTime = glutGet(GLUT_ELAPSED_TIME);

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

    void specKeyboardInputEvent(unsigned char key, int x, int y) {
        float deltaTime = glutGet(GLUT_ELAPSED_TIME);

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
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(copakond::WIN_WIDTH, copakond::WIN_HEIGHT);
    glutCreateWindow(copakond::WIN_TITLE);

    glutKeyboardFunc(copakond::keyboardInputEvent);
    //glutSpecialFunc(copakond::specKeyboardInputEvent);
    glutDisplayFunc(copakond::draw);

    if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
        pgr::dieWithError("pgr init failed, required OpenGL not supported?");

    copakond::init();

    std::cout << "Hello triangle!" << std::endl;

    glutMainLoop();
    return 0;
}
