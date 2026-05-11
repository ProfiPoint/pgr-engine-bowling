#ifndef PGR_SEM_COPAKOND_IMAGESEQUENCELABEL_H
#define PGR_SEM_COPAKOND_IMAGESEQUENCELABEL_H

#include "../mesh.h"

namespace copakond {
    class ImageSequenceLabel : public Mesh {
    protected:
        int _frame = 0;
        float _frameTime = 0.0f;
        bool _paused = false;

        int _fps;
        int _totalFrames;
        int _imagesPerWidth;
        int _imagesPerHeight;

        std::vector<float> _uvs;
        std::vector<float> _normals;
        GLuint _vboUvs = 0;

        void _generateGeometry();

    public:
        ImageSequenceLabel(const std::string& imageSequencePath, int fps, int totalFrames, int imagesPerWidth, int imagesPerHeight);
        ImageSequenceLabel(const std::string& imageSequencePath, int fps, int totalFrames, int imagesPerWidth, int imagesPerHeight, std::shared_ptr<Material> material);
        ~ImageSequenceLabel() override;

        void init(GLuint shader) override;
        void draw(float deltaTime) override;

        void pause() { _paused = true; }
        void unpause() { _paused = false; }
        void setFrame(int frame) { _frame = frame; }
    };
}

#endif //PGR_SEM_COPAKOND_IMAGESEQUENCELABEL_H
