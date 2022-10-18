// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "AnimSpriteComponent.h"
#include "Math.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mCurrFrame(0.0f)
	, mAnimFPS(24.0f)
	, mLoop(true)
	, mPlaying(false)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.size() > 0)
	{
		/* フレームレートとデルタタイムに基づいてカレントフレームを更新する */
		mCurrFrame += mAnimFPS * deltaTime;

		/* カレントフレームがテクスチャの枚数を超えた時 */
		while (mCurrFrame >= mAnimTextures.size())
		{
			if (!mLoop) {	// ループしない
				mPlaying = false;
				return;
			}
			else {
				mCurrFrame -= mAnimTextures.size();
			}
		}

		/* 現時点のテクスチャを設定する */
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<Texture*>& textures, bool loop)
{
	mAnimTextures = textures;
	mLoop = loop;
	mPlaying = true;
	if (mAnimTextures.size() > 0)
	{
		// Set the active texture to first frame
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}
