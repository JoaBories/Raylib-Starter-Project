#include "Utilities.h"

Vector2 Util::Utilities::Normalized(Vector2 vector)
{
    float length = Lenght(vector);
    return { vector.x / length, vector.y / length };
}

float Util::Utilities::Lenght(Vector2 vector)
{
    return sqrtf(vector.x * vector.x + vector.y * vector.y);
}
