#include "ComponentTexture.h"

void Component_Texture::Enable()
{
}

void Component_Texture::Disable()
{
}

void Component_Texture::Update()
{
}

void Component_Texture::CleanUp()
{
}

Component_Texture::Component_Texture(Game_Object* ComponentOwner): Component(ComponentOwner)
{
}

Component_Texture::Component_Texture(Game_Object* ComponentOwner, const char* texturePath, unsigned int id):Component(ComponentOwner)
{
}

Component_Texture::Component_Texture(Game_Object* ComponentOwner, TextureInfo* material):Component(ComponentOwner)
{
	Texture = material;
	type = Component_Types::Texture;
}

Component_Texture::Component_Texture(Game_Object* ComponentOwner,int Position) :Component(ComponentOwner)
{
	PositionInListCmp = Position;
	type = Component_Types::Texture;
}
