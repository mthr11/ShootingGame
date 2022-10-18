// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>

Texture::Texture()
	:mTexture(nullptr)
	, mWidth(0)
	, mHeight(0)
{

}

Texture::~Texture()
{

}

bool Texture::Load(const std::string& fileName, SDL_Renderer* renderer)
{
	// Load from file
	SDL_Surface* surf = IMG_Load(fileName.c_str());
	if (!surf)
	{
		SDL_Log("Failed to load texture file %s", fileName.c_str());
		return false;
	}

	// Create texture from surface
	mTexture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	if (!mTexture)
	{
		SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
		return false;
	}

	SDL_QueryTexture(mTexture, nullptr, nullptr, &mWidth, &mHeight);

	return true;
}
