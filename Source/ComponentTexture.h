#pragma once
#ifndef __ComponentTexture_H__
#define __ComponentTexture_H__

#include "Component.h"

struct TextureInfo;

class Component_Texture :public Component {

public:

	TextureInfo* Texture = nullptr;

	int PositionInListCmp;

	void Enable()override;
	void Disable()override;
	void Update()override;
	void CleanUp()override;

	TextureInfo* GetTexture() { return Texture; };

	Component_Texture(Game_Object* parent); //DEFAULTS TO 0,0
	Component_Texture(Game_Object* parent, const char* texturePath, unsigned int id);
	Component_Texture(Game_Object* parent, TextureInfo* material);
	Component_Texture(Game_Object* parent, int Position);

	int Texture_ListPos;

	bool is_Textured;
};

#endif