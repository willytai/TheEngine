#ifndef __HIERARCHY_PANEL_H__
#define __HIERARCHY_PANEL_H__

#include "core/core.h"
#include "core/scene/scene.h"
#include "core/scene/entity.h"

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

    private:
        void drawEntity(const Entity& entity);
        void drawProperties(Entity& entity);

    private:
        Ref<Scene>  _context;
        Entity      _selectedEntity;
    };
}

#endif /* __HIERARCHY_PANEL_H__ */
