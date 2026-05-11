#ifndef PGR_SEM_COPAKOND_SKYBOX_H
#define PGR_SEM_COPAKOND_SKYBOX_H

#include "../../pgr-portable.h"
#include "../mesh.h"
#include "../../geometry/camera.h"

namespace copakond {
    /** @brief Environmental background cube map with day/night cycle blending */
    class Skybox : public Mesh {
    private:
        GLuint _shaderProgram = 0;
        GLuint _skyboxDayTextureUID = 0;
        GLuint _skyboxNightTextureUID = 0;

        GLuint _viewUID = 0;
        GLuint _projectionUID = 0;
        GLuint _blendingCoeffUID = 0;

    public:
        /**
         * @brief Initializes a skybox with two separate cubemaps for day and night.
         * @param dRight,dLeft... Day texture paths.
         * @param nRight,nLeft... Night texture paths.
         * @param fileSkyboxVertexShader Path to skybox specific vertex shader.
         * @param fileSkyboxFragmentShader Path to skybox specific fragment shader.
         */
        Skybox(const std::string &dRight, const std::string &dLeft, const std::string &dTop, const std::string &dBottom, const  std::string &dFront, const std::string &dBack,
            const std::string &nRight, const std::string &nLeft, const std::string &nTop, const std::string &nBottom, const  std::string  &nFront, const std::string &nBack,
            const std::string &fileSkyboxVertexShader, const std::string &fileSkyboxFragmentShader);
        void draw(float deltaTime) override;

        /**
         * @brief Updates shader matrices (removing translation) and binds textures for blending.
         * @param blendingCoeff Factor between 0.0 (full day) and 1.0 (full night).
         */
        void update(Camera &camera, int winWidth, int winHeight, float deltaTime, float blendingCoeff);
    };

}

#endif //PGR_SEM_COPAKOND_SKYBOX_H
