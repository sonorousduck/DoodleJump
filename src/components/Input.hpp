#pragma once

#include "Component.hpp"

#include <cstdint>
#include <initializer_list>
#include <unordered_set>

namespace components
{
    class Input : public PolymorphicComparable<Component, Input>
  {
    public:
      enum class Type : std::uint8_t
      {
        Up,
        Down,
        Jump
      };

      

      Input(std::initializer_list<Type> inputs) :
        m_inputs(inputs)
      {
      }

      const auto& getInputs() { return m_inputs; }

    private:
      std::unordered_set<Type> m_inputs;
  };
}