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

Component_Texture::Component_Texture(Game_Object* owner_): Component(owner_)
{
}

Component_Texture::Component_Texture(Game_Object* owner_, const char* texturePath, unsigned int id):Component(owner_)
{
}

Component_Texture::Component_Texture(Game_Object* owner_, TextureInfo* rMaterial):Component(owner_)
{
}
