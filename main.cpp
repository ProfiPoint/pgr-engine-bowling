#include <iostream>
#include "pgr.h"
#include "meshes/mesh.h"
#include "meshes/objMesh.h"
#include "geometry/camera.h"
#include "utils/input.h"
#include "renderer/shader.h"
#include "utils/input.h"

namespace copakond {
    const char *WIN_TITLE = "PGR Semestral Work Copakond";
    int winWidth = 1280;
    int winHeight = 720;

    // shared variables
    uint64_t time = 0;
    std::vector<Mesh *> meshes = {};
    Shader shader = Shader();
    Camera camera(
        glm::vec3(0.0f, 0.0f, 5.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        100.0f
    );
    Input input = Input(camera, winWidth, winHeight);

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

        //Mesh* triangleMesh = new Mesh();
        //meshes.push_back(triangleMesh);
        Mesh *teddyMesh = new ObjMesh("meshes/models/teddy.obj", true);
        meshes.push_back(teddyMesh);

        Mesh *teddyMesh2 = new ObjMesh("meshes/models/teddy.obj", true, glm::vec3(-8.0f, 0.0f, 0.0f),
                                       glm::vec3(glm::pi<float>(), 0.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f));
        meshes.push_back(teddyMesh2);

        for (Mesh *mesh: meshes) {
            mesh->init(shaderPrg);
        }

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //glCullFace( GL_BACK);
        //glEnable(GL_CULL_FACE);
    }

    void draw() {
        float deltaTime = updateTime(); // calculate delta time
        input.keyInput(deltaTime); // process input

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.update(camera, winWidth, winHeight);

        for (Mesh *mesh: meshes) {
            mesh->rotation().x += deltaTime * 0.01f;
            shader.draw(*mesh);
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

    void screenResizeEvent(int width, int height) {
        if (width == 0) width = 1; // sadly it can be 0 for some reason.
        if (height == 0) height = 1;

        winWidth = width;
        winHeight = height;

        glViewport(0, 0, width, height);
        input.update(winWidth, winHeight);
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(copakond::winWidth, copakond::winHeight);
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
