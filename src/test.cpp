#include <stdio.h>
#include <math/vector.h>
#include <math/rect.h>
#include <math/collision.h>


int main()
{
    using namespace Base::Math;

    Rect rect1 = {0, 0, 20, 20, 0};
    Rect rect2 = {30, 0, 20, 20, 0};

 //   printf("%d\n", Base::Math::Collision::RectRectAxisUnaligned(rect1, rect2));
 //   printf("%d\n", Base::Math::Collision::RectRect(rect1, rect2));

    Vec2 a = { -4, 8 };
    Vec2 b = { 6, 7 };
    Vec2 x = { 0, 4};

    return 0;
}