#include "allocator/allocator.h"
#include "array/array.h"
#include "array/smart_array.h"
#include "array/dynamic_array.h"
#include "string/string.h"
#include "vector/vector2.h"

#include <time.h>
#include <stdlib.h>

void test_array(Allocator* const allocator)
{
    Array array;
    array_create(&array, allocator, sizeof(Vector2), 20);

    *((Vector2*)array_index(&array, 0)) = (Vector2){2, 7};
    *((Vector2*)array_index(&array, 1)) = (Vector2){7, 12};

    for (size_t i = 0; i < 20; i++)   
    {
       printf("(x: %f, y: %f)\n", ((Vector2*)array_index(&array, i))->x, ((Vector2*)array_index(&array, i))->y);
    } 
}

void test_smart_array(Allocator* const allocator)
{
    SmartArray array;
    smart_array_create(&array, allocator, sizeof(Vector2), 20);

    smart_array_push(&array, &(Vector2){4, 7});
    smart_array_push(&array, &(Vector2){3, 13});
    smart_array_push(&array, &(Vector2){-78, 56});
    smart_array_push(&array, &(Vector2){23, -5});

    smart_array_insert(&array, &(Vector2){455, -342}, 0);

    for (size_t i = 0; i < array.size; i++)   
    {
        printf("(x: %f, y: %f)\n", ((Vector2*)smart_array_index(&array, i))->x, ((Vector2*)smart_array_index(&array, i))->y);
    } 
    printf("Size:%I64d", array.size);
}

void test_dynamic_array()
{
    DynamicArray array;
    dynamic_array_create(&array, sizeof(Vector2), 4);

    dynamic_array_push(&array, &(Vector2){4, 7});
    dynamic_array_push(&array, &(Vector2){3, 13});
    dynamic_array_push(&array, &(Vector2){-78, 56});
    dynamic_array_push(&array, &(Vector2){23, -5});

    dynamic_array_insert(&array, &(Vector2){-32, 89}, 3);

    for (size_t i = 0; i < array.size; i++)   
    {
        printf("(x: %f, y: %f)\n", ((Vector2*)dynamic_array_index(&array, i))->x, ((Vector2*)dynamic_array_index(&array, i))->y);
    } 
    printf("Size:%I64d\n", array.size);
    printf("Capacity:%I64d\n", array.capacity);
    printf("\n");

    dynamic_array_destroy(&array);
}