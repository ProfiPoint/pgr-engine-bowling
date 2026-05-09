#ifndef PGR_SEM_COPAKOND_LEVELEDITOR_H
#define PGR_SEM_COPAKOND_LEVELEDITOR_H

#include "../scene.h"

namespace copakond {
    enum class EditMode { NONE, TRANSLATE, ROTATE, SCALE };
    enum class EditAxis { NONE, X, Y, Z };
    struct StateSaved { glm::vec3 pos; glm::vec3 rot; glm::vec3 scale; };

    class LevelEditor {
    private:
        Scene* _scene;
        Mesh* _selectedMesh = nullptr;
        StateSaved _originalState;
        EditMode _currentMode = EditMode::NONE;
        EditAxis _currentAxis = EditAxis::NONE;

    public:
        LevelEditor(Scene* scene) : _scene(scene) {}

        void onObjectClickedEvent(int id);
        void onKeyboardEvent(unsigned char key, int x, int y, bool isDown);
        void onMouseWheelEvent(int wheel, int direction, int x, int y);
        void saveSnapshot(std::string filename);

        EditMode getEditMode() const { return _currentMode; }
        EditAxis getEditAxis() const { return _currentAxis; }
    };
}

#endif //PGR_SEM_COPAKOND_LEVELEDITOR_H
