// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Explosion.h"
#include "Game.h"
#include "AnimSpriteComponent.h"
#include "Texture.h"

Explosion::Explosion(Game* game)
	:Actor(game)
{
	/* AnimSpriteComponentÇê∂ê¨ */
	asc = new AnimSpriteComponent(this);
	std::vector<Texture*> anim = {
		game->GetTexture("Assets/Explosion/Explosion01.png"),
		game->GetTexture("Assets/Explosion/Explosion02.png"),
		game->GetTexture("Assets/Explosion/Explosion03.png"),
		game->GetTexture("Assets/Explosion/Explosion04.png"),
		game->GetTexture("Assets/Explosion/Explosion05.png"),
		game->GetTexture("Assets/Explosion/Explosion06.png"),
		game->GetTexture("Assets/Explosion/Explosion07.png"),
		game->GetTexture("Assets/Explosion/Explosion08.png"),
		game->GetTexture("Assets/Explosion/Explosion09.png")
	};
	asc->SetAnimTextures(anim, false);
}

Explosion::~Explosion() {
	GetGame()->RemoveActor(this);
}

void Explosion::UpdateActor(float deltaTime) {
	if (!asc->GetPlaying()) {
		SetState(EDead);
	}
}
