
#include "GameDesignXP1_precompiled.h"

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>

#include "GameDesignXP1SystemComponent.h"

namespace GameDesignXP1
{
    void GameDesignXP1SystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<GameDesignXP1SystemComponent, AZ::Component>()
                ->Version(0)
                ->SerializerForEmptyClass();

            if (AZ::EditContext* ec = serialize->GetEditContext())
            {
                ec->Class<GameDesignXP1SystemComponent>("GameDesignXP1", "[Description of functionality provided by this System Component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("System"))
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ;
            }
        }
    }

    void GameDesignXP1SystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC("GameDesignXP1Service"));
    }

    void GameDesignXP1SystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC("GameDesignXP1Service"));
    }

    void GameDesignXP1SystemComponent::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        (void)required;
    }

    void GameDesignXP1SystemComponent::GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        (void)dependent;
    }

    void GameDesignXP1SystemComponent::Init()
    {
    }

    void GameDesignXP1SystemComponent::Activate()
    {
        GameDesignXP1RequestBus::Handler::BusConnect();
    }

    void GameDesignXP1SystemComponent::Deactivate()
    {
        GameDesignXP1RequestBus::Handler::BusDisconnect();
    }
}
