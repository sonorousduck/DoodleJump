#pragma once
#include "System.hpp"
#include "components/Position.hpp"
#include "components/Text.hpp"


namespace systems
{
	class FontRenderer : public System
    {
      public:
        FontRenderer() :
            System({ctti::unnamed_type_id<components::Text>(),
                    ctti::unnamed_type_id<components::Position>()})
        {
        }
	
        void update(std::chrono::milliseconds elapsedTime);

	};
	

}
