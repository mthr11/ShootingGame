// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
	, mass(0.1f)
	, velocity(Vector2::Zero)
	, sumOfForces(Vector2::Zero)
	, accel(Vector2::Zero)
{

}

void MoveComponent::Update(float deltaTime)
{
	Vector2 pos = mOwner->GetPosition();

	if (!Math::NearZero(sumOfForces.Length()))
	{
		accel = sumOfForces * (1.0f / mass);	// 加速度 = 力の合計 / 質量
		sumOfForces = Vector2::Zero;

		velocity += accel * deltaTime;	// オイラー積分で加速度から速度を計算
	}

	/* 速度が大きくなりすぎたら正規化して大きさを調節する */
	if (velocity.Length() > 1000.0f) {
		velocity.Normalize();
		velocity *= 1000.0f;
	}

	pos += velocity * deltaTime;

	mOwner->SetPosition(pos);
}

void MoveComponent::AddForce(const Vector2& force) {
	sumOfForces += force;
}
