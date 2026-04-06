#include <iostream>
#include "pgr.h"
#include "mesh.h"

namespace copakond {
    const int WIN_WIDTH = 512;
    const int WIN_HEIGHT = 512;
    const char* WIN_TITLE = "Hello World";

    std::vector<Mesh> meshes = {};
    GLuint shader = -1;

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
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(copakond::WIN_WIDTH, copakond::WIN_HEIGHT);
    glutCreateWindow(copakond::WIN_TITLE);

    glutDisplayFunc(copakond::draw);

    if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
        pgr::dieWithError("pgr init failed, required OpenGL not supported?");

    copakond::init();

    std::cout << "Hello triangle!" << std::endl;

    glutMainLoop();
    return 0;
}
