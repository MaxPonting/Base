#include <math/vector.h>

#include <stdio.h>

int main()
{
    using namespace Base;

    Vec2 a = {5, 11};
    Vec2 b = {19, 4};
    Vec2 c = {12, -6};

    Vec2 tripleCrossProduct = Math::Vector2F::TripleCrossProduct(a, b, c);

    printf("%f, %f\n", tripleCrossProduct[0], tripleCrossProduct[1]);

    return 0;
}