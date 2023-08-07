#pragma once

#include "../type/type.h"
#include "../vendor/cglm/struct.h"
#include "../graphics/camera.h"
#include "../graphics/shader.h"

int32 renderer_create();
int32 renderer_destroy();

int32 renderer_start(const Camera camera);
int32 renderer_draw_quad(vec2 position, vec2 size, float rotation, vec4 colour);
int32 renderer_draw_quad(vec2 position, vec2 size, float rotation, vec4 colour);
int32 renderer_end();