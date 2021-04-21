#ifndef __SCRIPTABLE_H__
#define __SCRIPTABLE_H__

#include "core/scene/entity.h"
#include "core/util/timeStep.h"

namespace Engine7414
{
    class Scriptable
    {
        friend class Scene;
    public:
        virtual ~Scriptable() = default;

    protected:
        template<typename T>
        T& get() { return _entity.get<T>(); }

        virtual void onConstruct() {}
        virtual void onUpdate(const TimeStep& deltaTime) {}
        virtual void onDestroy() {}

    private:
        Entity _entity;
    };
}

#endif /* __SCRIPTABLE_H__ */
