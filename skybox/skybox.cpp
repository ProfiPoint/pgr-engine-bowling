#include "skybox.h"
#include "../pgr-portable.h"

namespace copakond {
    Skybox::Skybox() {
        glGenTextures(1, &_skyboxTextureUID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTextureUID);

        pgr::loadTexImage2D("skybox/right.jpg",  GL_TEXTURE_CUBE_MAP_POSITIVE_X);
        pgr::loadTexImage2D("skybox/left.jpg", GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
        pgr::loadTexImage2D("skybox/top.jpg", GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
        pgr::loadTexImage2D("skybox/bottom.jpg", GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
        pgr::loadTexImage2D("skybox/front.jpg", GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
        pgr::loadTexImage2D("skybox/back.jpg", GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

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
    }
}