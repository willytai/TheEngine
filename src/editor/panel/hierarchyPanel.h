#ifndef __HIERARCHY_PANEL_H__
#define __HIERARCHY_PANEL_H__

#include "core/core.h"
#include "core/scene/scene.h"
#include "core/scene/entity.h"

#include <queue>

namespace Engine7414
{
    // friend of 'Scene'
    class HierarchyPanel
    {
    public:
        HierarchyPanel();
        HierarchyPanel(const Ref<Scene>& context);
        ~HierarchyPanel() = default;

        void setContext(const Ref<Scene>& context);
        void onImGui();

        Entity getSelectedEntity() const { return _selectedEntity; }

    private:
        void drawEntity(const Entity& entity);
        void onPropertyWindow();
        void drawProperties(Entity& entity);

    private:
        Ref<Scene>  _context;
        Entity      _selectedEntity;

        // for entity deletion
        std::queue<Entity> _removeEntity;
    };
}

#endif /* __HIERARCHY_PANEL_H__ */
