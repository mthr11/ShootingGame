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
		accel = sumOfForces * (1.0f / mass);	// �����x = �͂̍��v / ����
		sumOfForces = Vector2::Zero;

		velocity += accel * deltaTime;	// �I�C���[�ϕ��ŉ����x���瑬�x���v�Z
	}

	/* ���x���傫���Ȃ肷�����琳�K�����đ傫���𒲐߂��� */
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
