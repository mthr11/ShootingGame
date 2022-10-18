// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	bool Load(const std::string& fileName, struct SDL_Renderer* renderer);

	struct SDL_Texture* GetTexture() { return mTexture; }
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
private:
	// �`�悷��e�N�X�`��
	struct SDL_Texture* mTexture;
	// �e�N�X�`���̕��ƍ���
	int mWidth;
	int mHeight;
};
