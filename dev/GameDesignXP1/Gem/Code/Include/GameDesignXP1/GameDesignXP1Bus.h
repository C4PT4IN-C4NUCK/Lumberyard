
#pragma once

#include <AzCore/EBus/EBus.h>

namespace GameDesignXP1
{
    class GameDesignXP1Requests
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////

        // Put your public methods here
    };
    using GameDesignXP1RequestBus = AZ::EBus<GameDesignXP1Requests>;
} // namespace GameDesignXP1
