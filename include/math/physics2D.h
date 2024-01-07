#pragma once

#include "struct.h"
#include "../math/vector.h"

namespace Base::Math::Physics2D
{
    RigidBody2D CreateBody(const Vec2 position, const Float32 rotation, const Float32 mass, const Float32 inhertia, const Float32 restitution)
    {
        RigidBody2D body = { 0 };
        body.position = position;
        body.rotation = rotation;
        body.mass = mass;
        body.inhertia = inhertia;
        body.restitution = restitution;

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
        if(body.inhertia == 0)
            return body;

        body.rotationalAcceleration += torque / body.inhertia;
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

    CollisionResolution2D ResolveCollision(const CollisionManifold2D manifold, RigidBody2D a, RigidBody2D b)
    {
        const Vec2 resolutionVector = manifold.normal * manifold.depth / 2;
        a.position += resolutionVector;
        b.position -= resolutionVector;

        return { a, b };
    }

    CollisionResolution2D ResolveImpulseLinear(const CollisionManifold2D manifold, RigidBody2D a, RigidBody2D b)
    {
        const Vec2 relativeVelocity = b.velocity - a.velocity;
        const Float32 aInverseMass = 1 / a.mass;
        const Float32 bInverseMass = 1 / b.mass;
        const Float32 e = F32::Minimum(a.restitution, b.restitution);
        const Float32 j = (-(1 + e) * Vector2F::DotProduct(relativeVelocity, manifold.normal)) / ( aInverseMass + bInverseMass );
        const Vec2 impulse = manifold.normal * j;

        a.velocity -= impulse * aInverseMass;
        b.velocity += impulse * bInverseMass;

        return { a, b };
    }

    CollisionResolution2D ResolveImpulse(const CollisionManifold2D manifold, RigidBody2D a, RigidBody2D b)
    {
        const Float32 aInverseMass = 1 / a.mass;
        const Float32 bInverseMass = 1 / b.mass;
        const Float32 aInverseInhertia = 1 / a.inhertia;
        const Float32 bInverseInhertia = 1 / b.inhertia;

        const Float32 aRotationalVelocityRadians = F32::Radians(a.rotationalVelocity);
        const Float32 bRotationalVelocityRadians = F32::Radians(b.rotationalVelocity);

        const Float32 e = F32::Minimum(a.restitution, b.restitution);

        Vec2 raArray[2];
        Vec2 rbArray[2];
        Vec2 impulses[2];

        Float32 jSum = 0;

        for(Int32 i = 0; i < manifold.contactPoints.count; i++)
        {
            raArray[i] = manifold.contactPoints[i] - a.position;
            rbArray[i] = manifold.contactPoints[i] - b.position;

            const Vec2 raPerp = {-raArray[i][1], raArray[i][0]};
            const Vec2 rbPerp = {-rbArray[i][1], rbArray[i][0]};

            const Vec2 relativeVelocity = 
                (b.velocity + rbPerp * bRotationalVelocityRadians) - 
                (a.velocity + raPerp * aRotationalVelocityRadians);

            const Float32 raPerpDotN = Vector2F::DotProduct(raPerp, manifold.normal);
            const Float32 rbPerpDotN = Vector2F::DotProduct(rbPerp, manifold.normal);

            Float32 j = (-(1 + e) * Vector2F::DotProduct(relativeVelocity, manifold.normal)) 
            /  (aInverseMass + bInverseMass + (raPerpDotN * raPerpDotN) * aInverseInhertia + (rbPerpDotN * rbPerpDotN) * bInverseInhertia);
            j /= manifold.contactPoints.count;

            impulses[i] = manifold.normal * j;

            jSum+=j;
        }

        for(Int32 i = 0; i < manifold.contactPoints.count; i++)
        {
            a.velocity -= impulses[i] * aInverseMass;
            b.velocity += impulses[i] * bInverseMass;

            a.rotationalVelocity -= F32::Degrees(Vector2F::CrossProduct(raArray[i], impulses[i]) * aInverseInhertia);
            b.rotationalVelocity += F32::Degrees(Vector2F::CrossProduct(rbArray[i], impulses[i]) * bInverseInhertia);
        }

        return { a, b };
    }


}