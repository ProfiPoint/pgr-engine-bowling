/**
 * Code based off of template:
 * \file hello-world.cpp
 * \brief Your first OpenGL application.
 * \author Tomas Barak
 */

#include <iostream>
#include "pgr.h"

namespace copakond {
    const int WIN_WIDTH = 512;
    const int WIN_HEIGHT = 512;
    const char* WIN_TITLE = "Hello World";

    GLuint shaderProgram = 0;
    GLuint arrayBuffer = 0;
    GLuint vao = 0;

    void init() {
        glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

        GLuint shaders[] = {
          pgr::createShaderFromFile(GL_VERTEX_SHADER, "shaders/vertexShader.vert"),
          pgr::createShaderFromFile(GL_FRAGMENT_SHADER, "shaders/fragmentShader.frag"),
          0
        };
        shaderProgram = pgr::createProgram(shaders);

        static const float vertices[] = {
          0.0f,  0.5f,
          -0.5f, -0.5f,
          0.5f, -0.5f,
        };

		// VBO
        glGenBuffers(1, &arrayBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// VAO
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        GLint positionLoc = glGetAttribLocation(shaderProgram, "position");
        glEnableVertexAttribArray(positionLoc);
        glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    void draw() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

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
