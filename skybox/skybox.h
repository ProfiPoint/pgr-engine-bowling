#ifndef PGR_SEM_COPAKOND_SKYBOX_H
#define PGR_SEM_COPAKOND_SKYBOX_H
#include <gl_core_4_4.h>

namespace copakond {

class Skybox {
private:
    GLuint _shaderProgram;
    GLuint _skyboxTextureUID;

public:
    Skybox();
};

}

#endif //PGR_SEM_COPAKOND_SKYBOX_H
