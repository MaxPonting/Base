#include "../include/allocator.h"
#include "../include/array.h"
#include "../include/smart_array.h"
#include "../include/dynamic_array.h"
#include "../include/string.h"
#include "../include/vector2.h"

#include <time.h>
#include <stdlib.h>

const size_t ARRAY_STANDARD_SIZE = 1000000; // 1 MB
const size_t ARRAY_PERFORMANCE_SIZE = 700000000; // 700 MB


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

void performance_smart_array(Allocator* const allocator)
{
    SmartArray array;
    smart_array_create(&array, allocator, sizeof(char), ARRAY_PERFORMANCE_SIZE);

    for (size_t i = 0; i < array.capacity - 1; i++)   
    {
        smart_array_push(&array, &(Vector2){rand(), rand()});
    } 

    clock_t start, end;
    start = clock();

    smart_array_insert(&array, &(Vector2){rand(), rand()}, 0);

    end = clock();

    printf("Time Taken Seconds: %f", ((double)(end - start)) / CLOCKS_PER_SEC);
}

int main()
{
    Allocator allocator;
    allocator_create(&allocator, ARRAY_STANDARD_SIZE * sizeof(char));

    //test_array(&allocator);
    //test_smart_array(&allocator);
    //test_dynamic_array();

    //performance_smart_array(&allocator);

    String string;
    string_create(&string, &allocator, "Hello and welcome to my home");

    printf("String: %s", string.ptr);

    allocator_destroy(&allocator);
}