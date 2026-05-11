#ifndef PGR_SEM_COPAKOND_TextLabel_H
#define PGR_SEM_COPAKOND_TextLabel_H

#include "../mesh.h"
#include "../../geometry/material.h"

namespace copakond {
    /** @brief Dynamically generates 2D geometry to render text using a bitmap font atlas */
    class TextLabel : public Mesh {
    private:
        static std::string _alphabet; /**< The exact character order present in the font texture atlas */

        std::string _text;
        int _numCharacters;

        std::vector<float> _uvs;
        std::vector<float> _normals;

        GLuint _vboUvs = 0;

        /** @brief Dynamically builds quads and maps UVs for each character in the current text string */
        void _generateGeometry();

    public:
        TextLabel(const std::string& fontImagePath);
        TextLabel(const std::string& fontImagePath, std::shared_ptr<Material> material);
        ~TextLabel() override;

        /**
         * @brief Updates the displayed text string and regenerates mesh geometry.
         * @param text The new string to render.
         */
        void setText(const std::string& text);
        void setColor(const glm::vec3 &color) const;

        /** @brief Initializes buffers with GL_DYNAMIC_DRAW flag for frequent text updates */
        void init(GLuint shader) override;
        void draw(float deltaTime) override;
    };
}

#endif //PGR_SEM_COPAKOND_TextLabel_H
