#ifndef PGR_SEM_COPAKOND_IMAGESEQUENCELABEL_H
#define PGR_SEM_COPAKOND_IMAGESEQUENCELABEL_H

#include "../mesh.h"

namespace copakond {
    /** @brief 2D plane that plays an animation by cycling through a sprite sheet texture */
    class ImageSequenceLabel : public Mesh {
    protected:
        int _frame = 0; /**< Current animation frame index */
        float _frameTime = 0.0f; /**< Accumulated time since the last frame change */
        bool _paused = false;

        int _fps;
        int _totalFrames;
        int _imagesPerWidth; /**< Columns in the sprite sheet */
        int _imagesPerHeight; /**< Rows in the sprite sheet */

        std::vector<float> _uvs;
        std::vector<float> _normals;
        GLuint _vboUvs = 0;

        /** @brief Recalculates UV mapping to display the current frame from the sprite sheet */
        void _generateGeometry();

    public:
        ImageSequenceLabel(const std::string& imageSequencePath, int fps, int totalFrames, int imagesPerWidth, int imagesPerHeight);
        ImageSequenceLabel(const std::string& imageSequencePath, int fps, int totalFrames, int imagesPerWidth, int imagesPerHeight, std::shared_ptr<Material> material);
        ~ImageSequenceLabel() override;

        void init(GLuint shader) override;

        /** @brief Advances animation timer and triggers geometry regeneration if frame changes */
        void draw(float deltaTime) override;

        void pause() { _paused = true; }
        void unpause() { _paused = false; }
        void setFrame(int frame) { _frame = frame; }
    };
}

#endif //PGR_SEM_COPAKOND_IMAGESEQUENCELABEL_H
