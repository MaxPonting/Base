#include <stdio.h>
#include <math/vector.h>
#include <math/rect.h>

int main()
{
    Rect rect = {10, 0, 20, 20, 270};
    Vec2 vertices[4];
    Base::Math::Rectangle::Vertices(vertices, rect);

    printf("%f, %f\n", vertices[0][0], vertices[0][1]);

    return 0;
}