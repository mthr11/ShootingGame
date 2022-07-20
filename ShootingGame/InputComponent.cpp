// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor* owner)
	:MoveComponent(owner)
	, mMaxSpeed(0.0f)
	, mForwardKey(0)
	, mBackKey(0)
	, mRightKey(0)
	, mLeftKey(0)
{

}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	// Calculate forward speed for MoveComponent
	float forwardSpeed = 0.0f;
	float rightSpeed = 0.0f;
	if (keyState[mForwardKey])
	{
		forwardSpeed += mMaxSpeed;
	}
	if (keyState[mBackKey])
	{
		forwardSpeed -= mMaxSpeed;
	}
	if (keyState[mRightKey])
	{
		rightSpeed += mMaxSpeed;
	}
	if (keyState[mLeftKey])
	{
		rightSpeed -= mMaxSpeed;
	}

	AddForce(mOwner->GetForward() * forwardSpeed);
	AddForce(mOwner->GetRight() * rightSpeed);
}
