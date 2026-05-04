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
    Skybox(std::string fileRight, std::string fileLeft, std::string fileTop, std::string fileBottom, std::string fileFront,
        std::string fileBack, std::string fileSkyboxVertexShader, std::string fileSkyboxFragmentShader);
    void draw(float deltaTime) override;
    void update(Camera &camera, int winWidth, int winHeight, float deltaTime);
};

}

#endif //PGR_SEM_COPAKOND_SKYBOX_H
