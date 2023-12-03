#pragma once

#include "struct.h"
#include "../math/vector.h"

namespace Base::Math::Physics2D
{
    RigidBody2D Create(const Vec2 position, const Float32 mass, const Float32 elasticity)
    {
        RigidBody2D body;
        body.position = position;
        body.mass = mass;
        body.elasticity = elasticity;

        return body;
    }

    RigidBody2D Step(RigidBody2D body, const Float32 friction)
    {
        body.velocity += body.acceleration - body.velocity * friction;
        body.position += body.velocity;
        body.acceleration = { 0, 0 };

        body.rotationalVelocity += body.rotationalAcceleration - body.rotationalVelocity * friction;
        body.rotation += body.rotationalVelocity;
        body.rotationalAcceleration = 0;

        return body;
    }

    RigidBody2D AddForce(RigidBody2D body, const Vec2 force)
    {
        if(body.mass == 0)
            return body;

        body.acceleration += force / body.mass;
        return body;
    }

    RigidBody2D AddTorque(RigidBody2D body, const Float32 torque)
    {
        if(body.mass == 0)
            return body;

        body.rotationalAcceleration += torque / body.mass;
        return body;
    }

    RigidBody2D MoveToPositionGracefull(RigidBody2D body, const Vec2 target, const Vec2 force, const Float32 friction)
    {
        if(body.mass == 0)
            return body;

        const Vec2 direction = Math::Vector2F::Normalize(target - body.position);
        const Vec2 translation = body.velocity + ((direction * force) / body.mass) - body.velocity * friction;

        body.velocity[0] = abs(translation[0]) < abs(target[0] - body.position[0]) ? translation[0] : target[0] - body.position[0];
        body.velocity[1] = abs(translation[1]) < abs(target[1] - body.position[1]) ? translation[1] : target[1] - body.position[1];

        return body;
    }

    RigidBody2D MoveToPosition(RigidBody2D body, const Vec2 target, const Vec2 force)
    {
        if(body.mass == 0)
            return body;

        body = AddForce(body, Math::Vector2F::Normalize(target - body.position) * force);

        return body;
    }

    void ResolveImpulse(RigidBody2D& a, RigidBody2D& b)
    {
        const Float32 coefficientOfRestitution = Math::F32::Minimum(a.elasticity, b.elasticity);
        const Vec2 normal = Math::Vector2F::Normalize(a.position - b.position);
        const Vec2 relativeVelocity = a.velocity - b.velocity;

        const Float32 impulseMagnitude = -(1 + coefficientOfRestitution) * Math::Vector2F::DotProduct(relativeVelocity, normal) / (1 / a.mass + 1 / b.mass);
        const Vec2 impulse = normal * impulseMagnitude / 2;

        a.velocity += impulse;
        b.velocity -= impulse;
    }


}