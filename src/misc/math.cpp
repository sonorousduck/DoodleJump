#include "math.hpp"

namespace math
{
    Vector2f vector(Point2f a, Point2f b)
    {
        return {a.x - b.x, a.y - b.y};
    }

}