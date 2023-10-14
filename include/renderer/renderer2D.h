#pragma once

#include "../allocator/allocator.h"
#include "../opengl/opengl.h"
#include "../opengl/shader.h"
#include "../opengl/program.h"

namespace Base::Renderer2D
{
    const Float32 VERTICES[] = {

    };

    struct Global
    {
        UInt32 vertexArrayObject, vertexBufferObject, indexBufferObject;

    };

    static Global global;

    struct Vertex
    {
        Vec2 position;
    };

    Int32 Create(const Int32 maxQuadsPerScene)
    {
        glGenVertexArrays(1, &global.vertexArrayObject);
        glBindVertexArray(global.vertexArrayObject);

        glGenBuffers(1, &global.vertexBufferObject);
        glBindBuffer(GL_ARRAY_BUFFER, global.vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4 * maxQuadsPerScene, 0, GL_DYNAMIC_DRAW);

        UInt32* indices = (UInt32*)Allocator::Allocate(sizeof(UInt32) * 6 * maxQuadsPerScene);
        if(!indices)
        {
            Log::Print("Not enough memory allocated", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        for(Int32 i = 0, j = 0; i < maxQuadsPerScene * 6; i+=6, j+=4)
        {
            indices[i + 0] = j + 0;
            indices[i + 1] = j + 1;
            indices[i + 2] = j + 2;
            indices[i + 3] = j + 1;
            indices[i + 4] = j + 2;
            indices[i + 5] = j + 3;
        }

        glGenBuffers(1, &global.indexBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, global.indexBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UInt32) * 6 * maxQuadsPerScene, indices, GL_STATIC_DRAW);

        return 1;
        
    }
}