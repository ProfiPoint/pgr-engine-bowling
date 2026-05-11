#ifndef PGR_SEM_COPAKOND_IMAGEMOVING_H
#define PGR_SEM_COPAKOND_IMAGEMOVING_H
#include "../mesh.h"

namespace copakond {
    /** @brief 2D plane with an animated (scrolling) texture map */
    class ImageMoving : public Mesh {
    private:
        glm::vec2 _imageRepeated; /**< How many times the texture repeats across the plane */
        glm::vec2 _movingSpeed; /**< Texture scrolling speed in U and V directions */
        glm::vec2 _curOffset; /**< Current UV offset */

        bool _paused = false;

        std::vector<float> _uvs;
        std::vector<float> _normals;
        GLuint _vboUvs = 0;

        /** @brief Recalculates UV coordinates based on current offset and repetition */
        void _generateGeometry();
    public:
        ImageMoving(const std::string& imagePath, glm::vec2 movingSpeed, glm::vec2 imageRepeated);
        ImageMoving(const std::string& imagePath, glm::vec2 movingSpeed, glm::vec2 imageRepeated, std::shared_ptr<Material> material);
        ~ImageMoving() override;

        void init(GLuint shader) override;

        /** @brief Updates scrolling offset and triggers geometry regeneration if needed */
        void draw(float deltaTime) override;

        void pause() { _paused = true; }
        void unpause() { _paused = false; }
    };
}

#endif //PGR_SEM_COPAKOND_IMAGEMOVING_H
