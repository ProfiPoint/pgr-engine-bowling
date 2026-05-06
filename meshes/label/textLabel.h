#ifndef PGR_SEM_COPAKOND_TextLabel_H
#define PGR_SEM_COPAKOND_TextLabel_H

#include "../mesh.h"
#include "../../geometry/material.h"

namespace copakond {
    class TextLabel : public Mesh {
    private:
        static std::string _alphabet;

        std::string _text;
        int _numCharacters;

        std::vector<float> _uvs;
        std::vector<float> _normals;

        GLuint _vboUvs = 0;

        void _generateGeometry();

    public:
        TextLabel(const std::string& fontImagePath);
        TextLabel(const std::string& fontImagePath, std::shared_ptr<Material> material);
        ~TextLabel() override;

        void setText(const std::string& text);
        void setColor(const glm::vec3 &color) const;

        void init(GLuint shader) override;
        void draw(float deltaTime) override;
    };
}

#endif //PGR_SEM_COPAKOND_TextLabel_H
