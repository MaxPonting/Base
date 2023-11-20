#pragma once

#include "../type/type.h"
#include "../array/array.h"
#include "../math/math.h"
#include "../allocator/allocator.h"
#include "../opengl/opengl.h"
#include "../opengl/shader.h"
#include "../opengl/program.h"
#include "../opengl/texture.h"

namespace Base::Renderer2D
{
    enum class CoordinateSpace
    {
        World, Screen
    };

    struct SubTexture
    {
        Vec2 bottom;
        Vec2 top;
    };

    struct Quad
    {
        Vec2 position;
        Vec2 size;
        Float32 rotation;
        Vec4 colour;
        SubTexture subTexture;
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
        Int32 batchSize;
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

        const Char* VERTEX_SOURCE = "#version 330 core\nlayout(location = 0) in vec4 aPosition;layout(location = 1) in vec2 aTextureCoordinates;layout(location = 2) in vec4 aColour;uniform mat4 uView;uniform mat4 uProjection;out vec2 vTextureCoordinates;out vec4 vColour;void main(){gl_Position = uProjection * uView * aPosition;vTextureCoordinates = aTextureCoordinates;vColour = aColour;};";
        const Char* FRAGMENT_SOURCE = "#version 330 core\nin vec2 vTextureCoordinates;in vec4 vColour;uniform sampler2D uTexture;out vec4 oColour;void main(){oColour = texture2D(uTexture, vTextureCoordinates) * vColour;};";

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

        global.batchSize = estimatedMaxBatchSize;

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

    Int32 BeginScene(const Int32 width, const Int32 height, const Vec2 cameraPosition, const Vec2 cameraScale, const Float32 cameraRotation)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        Math::Orthographic(global.projection, -width / 2, width / 2, -height / 2, height / 2, -1, 1);
        Math::Mat4Identity(global.view);        

        const Vec2 position = {-cameraPosition[0], -cameraPosition[1] };
        const Vec2 scale = { 1 / cameraScale[0], 1 / cameraScale[1] };
        Math::Mat4Transform2D(global.view, position, scale, -cameraRotation);

        return 1;
    }

    Int32 EndScene()
    {
        return 1;
    }

    Int32 DrawQuads(const Quad* const quads, const Int32 count, const UInt32 texture, const CoordinateSpace space)
    {
        Vertex* vertices = (Vertex*)Allocator::Allocate(sizeof(Vertex) * 4 * count);

        for(Int32 i = 0; i < count * 4; i+=4)
        {
            Quad quad = quads[i / 4];

            Vertex v[4] = 
            {
                {
                    VERTICES[0] * quad.size[0], VERTICES[1] * quad.size[1],
                    quad.subTexture.bottom[0], quad.subTexture.bottom[1], 
                    quad.colour[0], quad.colour[1], quad.colour[2], quad.colour[3],
                },

                {
                    VERTICES[4] * quad.size[0], VERTICES[5] * quad.size[1], 
                    quad.subTexture.top[0], quad.subTexture.bottom[1], 
                    quad.colour[0], quad.colour[1], quad.colour[2], quad.colour[3],
                },
                {
                    VERTICES[8] * quad.size[0], VERTICES[9] * quad.size[1], 
                    quad.subTexture.bottom[0], quad.subTexture.top[1], 
                    quad.colour[0], quad.colour[1], quad.colour[2], quad.colour[3],
                },
                {
                    VERTICES[12] * quad.size[0], VERTICES[13] * quad.size[1], 
                    quad.subTexture.top[0], quad.subTexture.top[1], 
                    quad.colour[0], quad.colour[1], quad.colour[2], quad.colour[3],
                }
            };

            const Float32 sin = sinf(Math::Radians(quad.rotation));
            const Float32 cos = cosf(Math::Radians(quad.rotation));

            for(Int32 j = 0; j < 4; j++)
            {
                const Float32 x = v[j].position[0];
                const Float32 y = v[j].position[1];

                v[j].position[0] = cos * x - sin * y;
                v[j].position[1] = sin * x + cos * y;

                v[j].position[0] += quad.position[0];
                v[j].position[1] += quad.position[1];
            }

            vertices[i + 0] = v[0];
            vertices[i + 1] = v[1];
            vertices[i + 2] = v[2];
            vertices[i + 3] = v[3];
        }

        glBindVertexArray(global.vertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, global.vertexBuffer);

        if(count > global.batchSize)
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4 * count, vertices, GL_DYNAMIC_DRAW);

            UInt32* indices = (UInt32*)Allocator::Allocate(sizeof(UInt32) * count * 6);

            for(Int32 i = 0, j = 0; i < count * 6; i+=6, j+=4)
            {
                indices[i + 0] = j + 0;
                indices[i + 1] = j + 1;
                indices[i + 2] = j + 2;
                indices[i + 3] = j + 1;
                indices[i + 4] = j + 3;
                indices[i + 5] = j + 2;
            }

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UInt32) * count * 6, indices, GL_STATIC_DRAW);

            Log::Print("Increased batch size from %d to %d", Log::Type::Message, __LINE__, __FILE__, global.batchSize, count);

            global.batchSize = count;

            Allocator::Deallocate(sizeof(UInt32) * count * 6);           
        }
        else
        {
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * 4 * count, vertices);
        }

        OpenGL::Program::Bind(global.program);
        
        if(space == CoordinateSpace::World)
            OpenGL::Program::SetUniformMatrix4FV(global.program, "uView", global.view);
        else if(space == CoordinateSpace::Screen)
        {
            Mat4 view;
            Math::Mat4Identity(view);
            OpenGL::Program::SetUniformMatrix4FV(global.program, "uView", view);
        }
        OpenGL::Program::SetUniformMatrix4FV(global.program, "uProjection", global.projection);
        OpenGL::Program::SetUniform1I(global.program, "uTexture", 0);
        
        OpenGL::Texture::Bind(texture ? texture : global.whiteTexture, 0);

        glDrawElements(GL_TRIANGLES, 6 * count, GL_UNSIGNED_INT, 0);

        OpenGL::Texture::Bind(0, 0);
        OpenGL::Program::Bind(0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        Allocator::Deallocate(sizeof(Vertex) * 4 * count);

        return 1;
    }

    SubTexture CreateSubTexture(const IVec2 parentTextureSize, const IVec2 position, const IVec2 size)
    {
        SubTexture subTexture;

        subTexture.bottom[0] = (Float32)position[0] / (Float32)parentTextureSize[0];
        subTexture.bottom[1] = (Float32)position[1] / (Float32)parentTextureSize[1];
        subTexture.top[0] = (Float32)(position[0] + size[0]) / (Float32)parentTextureSize[0];
        subTexture.top[1] = (Float32)(position[1] + size[1]) / (Float32)parentTextureSize[1];

        return subTexture;
    }
}
