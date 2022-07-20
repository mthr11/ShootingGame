// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Component.h"
#include "Math.h"

class MoveComponent : public Component
{
public:
	// Lower update order to update first
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	Vector2 GetVelocity() const { return velocity; }
	void SetVelocity(Vector2 vel) { velocity = vel; }

	void AddForce(const Vector2& force);
private:
	/* ニュートン物理学 */
	float mass;		// 質量
	Vector2 velocity;
	Vector2 sumOfForces;	// 力の合計
	Vector2 accel;	// 加速度
};
