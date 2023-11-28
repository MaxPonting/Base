#include <math/vector.h>

#include <stdio.h>

int main()
{
    Mat4 matrix;
    matrix[0][0] = 2;
    matrix[0][1] = 4;
    matrix[1][0] = 7;
    matrix[1][1] = 1;
    matrix[3][0] = 6;
    matrix[3][1] = 8;
    matrix[2][2] = 1;
    matrix[3][3] = 1;

    Vec2 vector = { 20, 30 };

    Vec2 result = Base::Math::Vector2F::TransformMat4(matrix, vector);

    printf("%f, %f\n", result[0], result[1]);

    return 0;
}