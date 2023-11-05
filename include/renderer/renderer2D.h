#pragma once

#include "../type/type.h"
#include "../allocator/allocator.h"
#include "../array/array.h"
#include "../math/math.h"
#include "../io/file.h"
#include "../opengl/opengl.h"
#include "../opengl/shader.h"
#include "../opengl/program.h"
#include "../opengl/texture.h"

namespace Base::Renderer2D
{
    struct Quad
    {
        Vec2 position;
        Vec2 size;
        Float32 rotation;
        Vec4 colour;
    };

    struct Vertex
    {
        Vec2 position;
        Vec2 textureCoordinates;
        Vec4 colour;
    };

    struct Global
    {
        UInt32 vertexArray, vertexBuffer, indexBuffer, program, whiteTexture;
        Int32 largestBatchSize;
        Mat4 view, projection;
    };

    const static Float32 VERTICES[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 1.0f,
         0.5f,  0.5f, 1.0f, 1.0f
    };

    static Global global = { 0 };

    Int32 Create(const Int32 estimatedMaxBatchSize)
    {
        glGenVertexArrays(1, &global.vertexArray);
        glBindVertexArray(global.vertexArray);

        glGenBuffers(1, &global.vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, global.vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4 * estimatedMaxBatchSize, NULL, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, 0, sizeof(Vertex), (void*)(0));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, 0, sizeof(Vertex), (void*)(sizeof(Float32) * 2));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, 0, sizeof(Vertex), (void*)(sizeof(Float32) * 4));

        glGenBuffers(1, &global.indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, global.indexBuffer);

        UInt32* indices = (UInt32*)Allocator::Allocate(sizeof(UInt32) * estimatedMaxBatchSize * 6);

        for(Int32 i = 0, j = 0; i < estimatedMaxBatchSize * 6; i+=6, j+=4)
        {
            indices[i + 0] = j + 0;
            indices[i + 1] = j + 1;
            indices[i + 2] = j + 2;
            indices[i + 3] = j + 1;
            indices[i + 4] = j + 3;
            indices[i + 5] = j + 2;
        }

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UInt32) * estimatedMaxBatchSize * 6, indices, GL_STATIC_DRAW);

        Allocator::Deallocate(sizeof(UInt32) * estimatedMaxBatchSize * 6);

        Char VERTEX_SOURCE[512] = {0}; 
        Char FRAGMENT_SOURCE[512] = {0};

        IO::File::Read("res/shader/colour.vert", VERTEX_SOURCE, 512, false, true);
        IO::File::Read("res/shader/colour.frag", FRAGMENT_SOURCE, 512, false, true);

        UInt32 shaders[2] = { 0 };
        shaders[0] = OpenGL::Shader::Create(VERTEX_SOURCE, OpenGL::Shader::Type::Vertex);
        shaders[1] = OpenGL::Shader::Create(FRAGMENT_SOURCE, OpenGL::Shader::Type::Fragment);

        if(shaders[0] == 0 || shaders[1] == 0)
        {
            Log::Print("Shader failed to compile", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        global.program = OpenGL::Program::Create(shaders, 2);

        OpenGL::Shader::Destroy(shaders[0]);
        OpenGL::Shader::Destroy(shaders[1]);

        const Byte WHITE_PIXEL[] = {255, 255, 255, 255};
        global.whiteTexture = OpenGL::Texture::CreateWithData(WHITE_PIXEL, 1, 1);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        global.largestBatchSize = estimatedMaxBatchSize;

        return 1;
    }

    Int32 Destroy()
    {
        glDeleteVertexArrays(1, &global.vertexArray);
        glDeleteBuffers(1, &global.vertexBuffer);
        glDeleteBuffers(1, &global.indexBuffer);
        OpenGL::Program::Destroy(global.program);
        OpenGL::Texture::Destroy(global.whiteTexture);

        return 1;
    }

    Int32 BeginScene(const Int32 width, const Int32 height)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        Math::Orthographic(global.projection, -width / 2, width / 2, -height / 2, height / 2, -1, 1);
        Math::Mat4Identity(global.view);        

        return 1;
    }

    Int32 EndScene()
    {
        return 1;
    }

    Int32 DrawBatch(const Quad* const quads, const Int32 size)
    {
        Vertex* vertices = (Vertex*)Allocator::Allocate(sizeof(Vertex) * 4 * size);

        for(Int32 i = 0; i < size * 4; i+=4)
        {
            Quad quad = quads[i / 4];

            Vertex v[4] = 
            {
                {VERTICES[0] * quad.size[0], VERTICES[1] * quad.size[1], VERTICES[2], VERTICES[3], quad.colour[0], quad.colour[1], quad.colour[2], quad.colour[3]},
                {VERTICES[4] * quad.size[0], VERTICES[5] * quad.size[1], VERTICES[6], VERTICES[7], quad.colour[0], quad.colour[1], quad.colour[2], quad.colour[3]},
                {VERTICES[8] * quad.size[0], VERTICES[9] * quad.size[1], VERTICES[10], VERTICES[11], quad.colour[0], quad.colour[1], quad.colour[2], quad.colour[3]},
                {VERTICES[12] * quad.size[0], VERTICES[13] * quad.size[1], VERTICES[14], VERTICES[15], quad.colour[0], quad.colour[1], quad.colour[2], quad.colour[3]}
            };

            vertices[i + 0] = v[0];
            vertices[i + 1] = v[1];
            vertices[i + 2] = v[2];
            vertices[i + 3] = v[3];

        }

        glBindVertexArray(global.vertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, global.vertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, global.indexBuffer);

        if(size > global.largestBatchSize)
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4 * size, vertices, GL_DYNAMIC_DRAW);

            UInt32* indices = (UInt32*)Allocator::Allocate(sizeof(UInt32) * size * 6);

            for(Int32 i = 0, j = 0; i < size * 6; i+=6, j+=4)
            {
                indices[i + 0] = j + 0;
                indices[i + 1] = j + 1;
                indices[i + 2] = j + 2;
                indices[i + 3] = j + 1;
                indices[i + 4] = j + 3;
                indices[i + 5] = j + 2;
            }

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UInt32) * size * 6, indices, GL_STATIC_DRAW);

            Allocator::Deallocate(sizeof(UInt32) * size * 6);           
        }
        else
        {
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * 4 * size, vertices);
        }

        OpenGL::Program::Bind(global.program);
        OpenGL::Program::SetUniformMatrix4FV(global.program, "uView", global.view);
        OpenGL::Program::SetUniformMatrix4FV(global.program, "uProjection", global.projection);

        OpenGL::Texture::Bind(global.whiteTexture, 0);

        glDrawElements(GL_TRIANGLES, 6 * size, GL_UNSIGNED_INT, 0);

        Allocator::Deallocate(sizeof(Vertex) * 4 * size);

        return 1;
    }
}