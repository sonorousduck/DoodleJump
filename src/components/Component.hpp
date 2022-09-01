#pragma once

namespace components
{
    //
    // Reference: https://stackoverflow.com/questions/24249327/how-to-see-if-two-polymorphic-objects-are-equal
    //
    // Using this technique to avoid having to use dynamic_cast, which is relatively slow
    template <typename Base, typename Derived>
    struct PolymorphicComparable : public Base
    {
        bool operator==(Base& rhs)
        {
            if (typeid(rhs) != typeid(Derived))
            {
                return false;
            }

            Derived& a = static_cast<Derived&>(*this);
            Derived& b = static_cast<Derived&>(rhs);

            // clang prefer to have this, instead of "a == b", it throws a warning otherwise
            return a.operator==(b);
        }
    };

    class Component
    {
      public:
        //virtual std::tuple<ctti::unnamed_type_id_t, std::unique_ptr<Component>> clone() = 0;
        virtual ~Component() {}
        virtual bool operator==([[maybe_unused]] Component& rhs) = 0;
    };

}
