#ifndef PGR_SEM_COPAKOND_SKYBOX_H
#define PGR_SEM_COPAKOND_SKYBOX_H

#include "../../pgr-portable.h"
#include "../mesh.h"
#include "../../geometry/camera.h"

namespace copakond {

class Skybox : public Mesh {
private:
    GLuint _shaderProgram = 0;
    GLuint _skyboxDayTextureUID = 0;
    GLuint _skyboxNightTextureUID = 0;

    GLuint _viewUID = 0;
    GLuint _projectionUID = 0;
    GLuint _blendingCoeffUID = 0;

public:
    Skybox(const std::string &dRight, const std::string &dLeft, const std::string &dTop, const std::string &dBottom, const  std::string &dFront, const std::string &dBack,
        const std::string &nRight, const std::string &nLeft, const std::string &nTop, const std::string &nBottom, const  std::string  &nFront, const std::string &nBack,
        const std::string &fileSkyboxVertexShader, const std::string &fileSkyboxFragmentShader);
    void draw(float deltaTime) override;
    void update(Camera &camera, int winWidth, int winHeight, float deltaTime, float blendingCoeff);
};

}

#endif //PGR_SEM_COPAKOND_SKYBOX_H
