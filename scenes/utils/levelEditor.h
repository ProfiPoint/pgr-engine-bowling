#ifndef PGR_SEM_COPAKOND_LEVELEDITOR_H
#define PGR_SEM_COPAKOND_LEVELEDITOR_H

#include <map>

#include "../scene.h"

namespace copakond {
    enum class EditMode { NONE, TRANSLATE, ROTATE, SCALE };
    enum class EditAxe { NONE, X, Y, Z };

    struct StateSaved { glm::vec3 position; glm::vec3 rotation; glm::vec3 scale; };

    class LevelEditor {
    private:
        Scene* _scene;
        Mesh* _selectedMesh = nullptr;
        EditMode _currentMode = EditMode::NONE;
        EditAxe _currentAxe = EditAxe::NONE;

        std::map<Mesh*, StateSaved> _modifiedMeshes;

        static std::string floatToString(float value);
        static std::string vec3ToString(const glm::vec3& v);

    public:
        LevelEditor(Scene* scene) : _scene(scene) {}

        void onObjectClickedEvent(int id);
        void onKeyboardEvent(unsigned char key, int x, int y, bool isDown);
        void onMouseWheelEvent(int wheel, int direction, int x, int y);
        void saveSnapshot(std::string filename = "meshes.txt");
        void undo();

        EditMode getEditMode() const { return _currentMode; }
        EditAxe getEditAxe() const { return _currentAxe; }
    };
}

#endif //PGR_SEM_COPAKOND_LEVELEDITOR_H
