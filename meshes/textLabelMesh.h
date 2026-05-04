#ifndef PGR_SEM_COPAKOND_TEXTLABELMESH_H
#define PGR_SEM_COPAKOND_TEXTLABELMESH_H

#include "mesh.h"
#include "../geometry/material.h"

namespace copakond {
    class TextLabelMesh : public Mesh {
    private:
        static std::string _alphabet;

        std::string _text;
        int _numCharacters;

        std::vector<float> _uvs;
        std::vector<float> _normals;

        GLuint _vboUvs = 0;

        void _generateGeometry();

    public:
        TextLabelMesh(const std::string& fontImagePath);
        TextLabelMesh(const std::string& fontImagePath, std::shared_ptr<Material> material);
        ~TextLabelMesh() override;

        void setText(const std::string& text);
        void setColor(const glm::vec3 &color) const;

        void init(GLuint shader) override;
        void draw() override;
    };
}

#endif //PGR_SEM_COPAKOND_TEXTLABELMESH_H
