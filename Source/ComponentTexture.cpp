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

Component_Texture::Component_Texture(Game_Object* ComponentOwner, TextureInfo* rMaterial):Component(ComponentOwner)
{
}
