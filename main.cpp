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

    class TriangleMesh {
    public:
        GLuint shaderProgram = 0;
        GLuint arrayBuffer = 0;
        GLuint vao = 0;
        GLsizei numVertices = 0;

        GLint Mid = -1; // model matrix uniform index;
        GLint Vid = -1; // view matrix uniform index;
        GLint Pid = -1; // projection matrix uniform index;
    };

    TriangleMesh triangleMeshData;

    void init() {
        glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

        GLuint shaders[] = {
            pgr::createShaderFromFile(GL_VERTEX_SHADER, "shaders/vertexShader.vert"),
            pgr::createShaderFromFile(GL_FRAGMENT_SHADER, "shaders/fragmentShader.frag"),
            0
        };

        triangleMeshData.shaderProgram = pgr::createProgram(shaders);

        static const float vertices[] = {
            1.0f, 1.0f/2, 0.0f,
            1.0f, -1.0f, 0.0f,
            -1.0f/2, -1.0f, 0.0f,

            -1.0f, 1.0f, 0.0f,
            1.0f/2, 1.0f, 0.0f,
            -1.0f, -1.0f/2, 0.0f,
        };

        triangleMeshData.numVertices = sizeof(vertices) / (3 * sizeof(float));

		// VBO
        glGenBuffers(1, &triangleMeshData.arrayBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, triangleMeshData.arrayBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// VAO
        glGenVertexArrays(1, &triangleMeshData.vao);
        glBindVertexArray(triangleMeshData.vao);
        GLint positionLoc = glGetAttribLocation(triangleMeshData.shaderProgram, "position");
        glEnableVertexAttribArray(positionLoc);
        glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // UNIFORM BINDING
        triangleMeshData.Mid = glGetUniformLocation(triangleMeshData.shaderProgram, "model");
        triangleMeshData.Vid = glGetUniformLocation(triangleMeshData.shaderProgram, "view");
        triangleMeshData.Pid = glGetUniformLocation(triangleMeshData.shaderProgram, "projection");
    }

    void draw() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(triangleMeshData.shaderProgram);
        glBindVertexArray(triangleMeshData.vao);

        // MODEL MATRIX
        static const float modelM[] = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        // VIEW MATRIX
        glm::vec3 eye = glm::vec3(0.0f, 0.0f, 10.0f);
        glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 up  = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::mat4 viewM = glm::lookAt(eye, center, up);

        // PROJECTION MATRIX
        float fovy = glm::radians(45.0f);
        float aspect = static_cast<float>(WIN_WIDTH) / static_cast<float>(WIN_HEIGHT);
        float nearZ = 0.1f;
        float farZ = 100.0f;
        glm::mat4 projectionM = glm::perspective(fovy, aspect, nearZ, farZ);

        // UNIFORM APPLY
        glUniformMatrix4fv(triangleMeshData.Mid, 1, GL_TRUE, modelM); // TRUE will transpose the matrix, opengl accepts it by rows and not by columns.
        glUniformMatrix4fv(triangleMeshData.Vid, 1, GL_FALSE, glm::value_ptr(viewM));
        glUniformMatrix4fv(triangleMeshData.Pid, 1, GL_FALSE, glm::value_ptr(projectionM));



        // DRAW ALL OBJECTS TO THE SCREEN
        glDrawArrays(GL_TRIANGLES, 0, triangleMeshData.numVertices);
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
