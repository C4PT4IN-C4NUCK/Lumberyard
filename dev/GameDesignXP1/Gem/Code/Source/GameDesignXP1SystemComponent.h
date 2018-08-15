
#pragma once

#include <AzCore/Component/Component.h>

#include <GameDesignXP1/GameDesignXP1Bus.h>

namespace GameDesignXP1
{
    class GameDesignXP1SystemComponent
        : public AZ::Component
        , protected GameDesignXP1RequestBus::Handler
    {
    public:
        AZ_COMPONENT(GameDesignXP1SystemComponent, "{E594E8F6-4450-42F9-AC1D-23EF1FB7DC0B}");

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

    protected:
        ////////////////////////////////////////////////////////////////////////
        // GameDesignXP1RequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////
    };
}
