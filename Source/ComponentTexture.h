#pragma once
#ifndef __ComponentTexture_H__
#define __ComponentTexture_H__

#include "Component.h"

struct TextureInfo;

class Component_Texture :public Component {


public:

	TextureInfo* Texture = nullptr;
	//Color color;


	void Enable()override;
	void Disable()override;
	void Update()override;
	void CleanUp()override;

	TextureInfo* GetTexture() { return Texture; };
	//Color GetColour() { return color; };

	Component_Texture(Game_Object* parent); //DEFAULTS TO 0,0
	Component_Texture(Game_Object* parent, const char* texturePath, unsigned int id);
	Component_Texture(Game_Object* parent, TextureInfo* material);



	bool is_Textured;
	 //MOVE TO MESH COMPONENT
};





#endif