#include "skybox.h"
#include "../pgr-portable.h"

namespace copakond {
    Skybox::Skybox(const std::string &fileRight, const std::string &fileLeft, const std::string &fileTop, const std::string &fileBottom, const std::string &fileFront,
        const std::string &fileBack, const std::string &fileSkyboxVertexShader, const std::string &fileSkyboxFragmentShader) {
        Skybox::Mesh();

        glGenTextures(1, &_skyboxTextureUID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTextureUID);

        pgr::loadTexImage2D(fileRight,  GL_TEXTURE_CUBE_MAP_POSITIVE_X);
        pgr::loadTexImage2D(fileLeft, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
        pgr::loadTexImage2D(fileTop, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
        pgr::loadTexImage2D(fileBottom, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
        pgr::loadTexImage2D(fileFront, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
        pgr::loadTexImage2D(fileBack, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        const GLuint shaders[] = {
            pgr::createShaderFromFile(GL_VERTEX_SHADER, fileSkyboxVertexShader),
            pgr::createShaderFromFile(GL_FRAGMENT_SHADER, fileSkyboxFragmentShader),
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

    void Skybox::update(Camera &camera, const int winWidth, const int winHeight, const float deltaTime) {
        glUseProgram(_shaderProgram);
        glm::mat4 projectionM = camera.getProjectionMatrix((float)winWidth, (float)winHeight);
        glm::mat4 viewM = camera.getViewMatrix();
        viewM = glm::mat4(glm::mat3(viewM)); // removing position

        glUniformMatrix4fv(_viewUID, 1, GL_FALSE, glm::value_ptr(viewM));
        glUniformMatrix4fv(_projectionUID, 1, GL_FALSE, glm::value_ptr(projectionM));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTextureUID);
        glUniform1i(glGetUniformLocation(_shaderProgram, "skybox"), 0);

        Mesh::draw(deltaTime);
    }

    void Skybox::draw(float deltaTime) {
        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, _numVertices);
        glBindVertexArray(0);
    }

}