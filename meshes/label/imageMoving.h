#ifndef PGR_SEM_COPAKOND_IMAGEMOVING_H
#define PGR_SEM_COPAKOND_IMAGEMOVING_H
#include "../mesh.h"

namespace copakond {
    class ImageMoving : public Mesh {
    private:
        glm::vec2 _imageRepeated;
        glm::vec2 _movingSpeed;
        glm::vec2 _curOffset;

        bool _paused = false;

        std::vector<float> _uvs;
        std::vector<float> _normals;
        GLuint _vboUvs = 0;

        void _generateGeometry();
    public:
        ImageMoving(const std::string& imagePath, glm::vec2 movingSpeed, glm::vec2 imageRepeated);
        ImageMoving(const std::string& imagePath, glm::vec2 movingSpeed, glm::vec2 imageRepeated, std::shared_ptr<Material> material);
        ~ImageMoving() override;

        void init(GLuint shader) override;
        void draw(float deltaTime) override;

        void pause() { _paused = true; }
        void unpause() { _paused = false; }
    };
}

#endif //PGR_SEM_COPAKOND_IMAGEMOVING_H
