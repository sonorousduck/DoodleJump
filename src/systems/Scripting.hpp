#pragma once

#include "System.hpp"

namespace systems
{
	class Scripting : public System
    {
      public:
        Scripting() :
            System({})
        {
        }


        void update(std::chrono::milliseconds elapsedTime);

	};
	
}
