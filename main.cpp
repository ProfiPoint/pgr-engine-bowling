#include <iostream>
#include "pgr.h"
#include "mesh.h"
#include "camera.h"
#include "input.h"
#include "shader.h"
#include "input.h"

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
    Input input = Input(camera, WIN_WIDTH, WIN_HEIGHT);

    float updateTime() {
        int currentFrameTime = glutGet(GLUT_ELAPSED_TIME);
        uint64_t prevTime = time;
        time = currentFrameTime;
        return (currentFrameTime - prevTime) / 1000.0f; // delta time
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

        for (Mesh &mesh: meshes) {
            mesh.init(shaderPrg);
        }
    }

    void draw() {
        float deltaTime = updateTime(); // calculate delta time
        input.keyInput(deltaTime); // process input

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.draw(camera, WIN_WIDTH, WIN_HEIGHT);

        for (Mesh &mesh: meshes) {
            mesh.draw(WIN_WIDTH, WIN_HEIGHT);
        }

        glutSwapBuffers(); // swap front and back screen buffer
        glutPostRedisplay(); // !!!!!!!!! schedules display, doesnt stack!!!
    }

    void keyboardInputEvent(unsigned char key, int x, int y) {
        input.keyboardInputEvent(key, x, y);
    }
    void specKeyboardInputEvent(int key, int x, int y) {
        input.specKeyboardInputEvent(key, x, y);
    }
    void keyboardUpInputEvent(unsigned char key, int x, int y) {
        input.keyboardUpInputEvent(key, x, y);
    }
    void specKeyboardUpInputEvent(int key, int x, int y) {
        input.specKeyboardUpInputEvent(key, x, y);
    }

    void mouseMoveEvent(int x, int y) {
        input.mouseMoveEvent(x, y);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(copakond::WIN_WIDTH, copakond::WIN_HEIGHT);
    glutCreateWindow(copakond::WIN_TITLE);

    // INPUT - keyboard and mouse event callbacks
    glutKeyboardFunc(copakond::keyboardInputEvent);
    glutSpecialFunc(copakond::specKeyboardInputEvent);
    glutKeyboardUpFunc(copakond::keyboardUpInputEvent);
    glutSpecialUpFunc(copakond::specKeyboardUpInputEvent);

    glutPassiveMotionFunc(copakond::mouseMoveEvent);
    glutSetCursor(GLUT_CURSOR_NONE); // hide cursor

    // SET DRAW CALLBACK
    glutDisplayFunc(copakond::draw);

    if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR)) {
        pgr::dieWithError("pgr init failed, required OpenGL not supported?");
    }

    copakond::init();

    glutMainLoop();
    return 0;
}
