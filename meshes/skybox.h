#ifndef PGR_SEM_COPAKOND_SKYBOX_H
#define PGR_SEM_COPAKOND_SKYBOX_H

#include "../pgr-portable.h"
#include "mesh.h"
#include "../geometry/camera.h"

namespace copakond {

class Skybox : public Mesh {
private:
    GLuint _shaderProgram = 0;
    GLuint _skyboxTextureUID = 0;

    GLuint _viewUID = 0;
    GLuint _projectionUID = 0;

public:
    Skybox(const std::string &fileRight, const std::string &fileLeft, const std::string &fileTop, const std::string &fileBottom, const std::string &fileFront,
        const std::string &fileBack, const std::string &fileSkyboxVertexShader, const std::string &fileSkyboxFragmentShader);
    void draw(float deltaTime) override;
    void update(Camera &camera, int winWidth, int winHeight, float deltaTime);
};

}

#endif //PGR_SEM_COPAKOND_SKYBOX_H
