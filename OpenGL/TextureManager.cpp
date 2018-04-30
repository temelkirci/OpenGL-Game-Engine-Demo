#include "TextureManager.h"

TextureManager::TextureManager()
{
	
}

TextureManager ::~TextureManager()
{

}

TextureManager::TextureManager(const char* pTexturePath , int width , int height)
{	
    // Load, create texture and generate mipmaps

	SDL_Surface* Surface = IMG_Load(pTexturePath);

	if (Surface == NULL)
	{
		cerr << "IMG_Load: " << SDL_GetError() << endl;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	int Mode = GL_RGB;

	if (Surface->format->BytesPerPixel == 4) 
	{
		Mode = GL_RGBA;
	}

	if(Surface != NULL)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, Mode, Surface->w, Surface->h, 0, Mode, GL_UNSIGNED_BYTE, Surface->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		SDL_FreeSurface(Surface);
	}
	else
	{
		std::cout << "Texture couldn't load" << std::endl;
	}
}