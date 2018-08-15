
#include "GameDesignXP1_precompiled.h"
#include <platform_impl.h>

#include <AzCore/Memory/SystemAllocator.h>

#include "GameDesignXP1SystemComponent.h"

#include <IGem.h>

namespace GameDesignXP1
{
    class GameDesignXP1Module
        : public CryHooksModule
    {
    public:
        AZ_RTTI(GameDesignXP1Module, "{01D0108D-E814-47A8-8FF9-AC84E549FFB3}", CryHooksModule);
        AZ_CLASS_ALLOCATOR(GameDesignXP1Module, AZ::SystemAllocator, 0);

        GameDesignXP1Module()
            : CryHooksModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                GameDesignXP1SystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<GameDesignXP1SystemComponent>(),
            };
        }
    };
}

// DO NOT MODIFY THIS LINE UNLESS YOU RENAME THE GEM
// The first parameter should be GemName_GemIdLower
// The second should be the fully qualified name of the class above
AZ_DECLARE_MODULE_CLASS(GameDesignXP1_54ffd5c827f14508a1893e7e0a07e1eb, GameDesignXP1::GameDesignXP1Module)
