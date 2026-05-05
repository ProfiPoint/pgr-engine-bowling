#include "skybox.h"
#include "../pgr-portable.h"

namespace copakond {
    Skybox::Skybox(const std::string &dRight, const std::string &dLeft, const std::string &dTop, const std::string &dBottom, const  std::string &dFront, const std::string &dBack,
        const std::string &nRight, const std::string &nLeft, const std::string &nTop, const std::string &nBottom, const  std::string &nFront, const std::string &nBack,
        const std::string &fileSkyboxVertexShader, const std::string &fileSkyboxFragmentShader) {

        Skybox::Mesh();

        // DAY SKYBOX
        glGenTextures(1, &_skyboxDayTextureUID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxDayTextureUID);

        pgr::loadTexImage2D(dRight,  GL_TEXTURE_CUBE_MAP_POSITIVE_X);
        pgr::loadTexImage2D(dLeft, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
        pgr::loadTexImage2D(dTop, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
        pgr::loadTexImage2D(dBottom, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
        pgr::loadTexImage2D(dFront, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
        pgr::loadTexImage2D(dBack, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        // NIGHT SKYBOX
        glGenTextures(1, &_skyboxNightTextureUID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxNightTextureUID);
        pgr::loadTexImage2D(nRight, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
        pgr::loadTexImage2D(nLeft, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
        pgr::loadTexImage2D(nTop, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
        pgr::loadTexImage2D(nBottom, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
        pgr::loadTexImage2D(nFront, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
        pgr::loadTexImage2D(nBack, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

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
        _blendingCoeffUID = glGetUniformLocation(_shaderProgram, "blendCoeff");

        glUseProgram(_shaderProgram);

        glUniform1i(glGetUniformLocation(_shaderProgram, "skyboxDay"), 0); // texture 0
        glUniform1i(glGetUniformLocation(_shaderProgram, "skyboxNight"), 1); // texture 1
    }

    void Skybox::update(Camera &camera, const int winWidth, const int winHeight, const float deltaTime, float blendingCoeff) {
        glUseProgram(_shaderProgram);
        glm::mat4 projectionM = camera.getProjectionMatrix((float)winWidth, (float)winHeight);
        glm::mat4 viewM = camera.getViewMatrix();
        viewM = glm::mat4(glm::mat3(viewM)); // removing position

        glUniformMatrix4fv(_viewUID, 1, GL_FALSE, glm::value_ptr(viewM));
        glUniformMatrix4fv(_projectionUID, 1, GL_FALSE, glm::value_ptr(projectionM));

        glUniform1f(_blendingCoeffUID, blendingCoeff);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxDayTextureUID);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxNightTextureUID);

        Mesh::draw(deltaTime);

        glActiveTexture(GL_TEXTURE0);
    }

    void Skybox::draw(float deltaTime) {
        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, _numVertices);
        glBindVertexArray(0);
    }

}