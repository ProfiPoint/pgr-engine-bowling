#ifndef PGR_SEM_COPAKOND_SKYBOX_H
#define PGR_SEM_COPAKOND_SKYBOX_H

#include "../pgr-portable.h"
#include "../meshes/mesh.h"
#include "../geometry/camera.h"

namespace copakond {

class Skybox : public Mesh {
private:
    GLuint _shaderProgram;
    GLuint _skyboxTextureUID;

    GLuint _viewUID;
    GLuint _projectionUID;

public:
    Skybox();
    void draw() override;
    void update(Camera &camera, int winWidth, int winHeight);
};

}

#endif //PGR_SEM_COPAKOND_SKYBOX_H
