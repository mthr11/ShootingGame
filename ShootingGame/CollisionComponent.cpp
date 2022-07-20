// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "CollisionComponent.h"
#include "Actor.h"
#include "Game.h"

CollisionComponent::CollisionComponent(class Actor* owner)
	:Component(owner)
	, mRadius(0.0f)
{

}

const Vector2& CollisionComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

float CollisionComponent::GetRadius() const
{
	return mOwner->GetScale() * mRadius;
}

bool Intersect(const CollisionComponent& a, const CollisionComponent& b)
{
	// Calculate distance squared
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();

	// Calculate sum of radii squared
	float radiiSq = a.GetRadius() + b.GetRadius();
	radiiSq *= radiiSq;

	return distSq <= radiiSq;
}
