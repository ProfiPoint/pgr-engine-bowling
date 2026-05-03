#include "skybox.h"
#include "../pgr-portable.h"

namespace copakond {
    Skybox::Skybox() {
        Skybox::Mesh();

        glGenTextures(1, &_skyboxTextureUID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTextureUID);

        pgr::loadTexImage2D("assets/skybox/right.jpg",  GL_TEXTURE_CUBE_MAP_POSITIVE_X);
        pgr::loadTexImage2D("assets/skybox/left.jpg", GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
        pgr::loadTexImage2D("assets/skybox/top.jpg", GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
        pgr::loadTexImage2D("assets/skybox/bottom.jpg", GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
        pgr::loadTexImage2D("assets/skybox/front.jpg", GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
        pgr::loadTexImage2D("assets/skybox/back.jpg", GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        GLuint shaders[] = {
            pgr::createShaderFromFile(GL_VERTEX_SHADER, "shaders/shaders/skybox.vert"),
            pgr::createShaderFromFile(GL_FRAGMENT_SHADER, "shaders/shaders/skybox.frag"),
            0
        };

        _shaderProgram = pgr::createProgram(shaders);

        std::vector<float> vertices = {
            // back
            1.0f,  1.0f, -1.0f,
           -1.0f,  1.0f, -1.0f,
           -1.0f, -1.0f, -1.0f,

           -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,

           // front
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
           -1.0f, -1.0f,  1.0f,

           -1.0f, -1.0f,  1.0f,
           -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,

           // left
           -1.0f, -1.0f, -1.0f,
           -1.0f,  1.0f, -1.0f,
           -1.0f,  1.0f,  1.0f,

           -1.0f,  1.0f,  1.0f,
           -1.0f, -1.0f,  1.0f,
           -1.0f, -1.0f, -1.0f,

           // right
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,

            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,

           // bottom
            1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
           -1.0f, -1.0f, -1.0f,

           -1.0f, -1.0f, -1.0f,
           -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,

           // top
            1.0f,  1.0f,  1.0f,
           -1.0f,  1.0f,  1.0f,
           -1.0f,  1.0f, -1.0f,

           -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f
       };

        setVertices(vertices);
        init(_shaderProgram);

        _viewUID = glGetUniformLocation(_shaderProgram, "view");
        _projectionUID = glGetUniformLocation(_shaderProgram, "projection");
    }

    void Skybox::update(Camera &camera, int winWidth, int winHeight) {
        glUseProgram(_shaderProgram);
        glm::mat4 projectionM = camera.getProjectionMatrix((float)winWidth, (float)winHeight);
        glm::mat4 viewM = camera.getViewMatrix();
        viewM = glm::mat4(glm::mat3(viewM)); // removing position

        glUniformMatrix4fv(_viewUID, 1, GL_FALSE, glm::value_ptr(viewM));
        glUniformMatrix4fv(_projectionUID, 1, GL_FALSE, glm::value_ptr(projectionM));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTextureUID);
        glUniform1i(glGetUniformLocation(_shaderProgram, "skybox"), 0);

        Mesh::draw();
    }

    void Skybox::draw() {
        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, _numVertices);
        glBindVertexArray(0);
    }

}