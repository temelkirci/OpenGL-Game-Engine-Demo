#include "Texture.h"

Texture :: Texture()
{
	
}

Texture ::~Texture()
{

}

Texture :: Texture(const char* pTexturePath1 , int width , int height)
{	
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int nrChannels;
	
    // Load, create texture and generate mipmaps
    unsigned char* image = SOIL_load_image(pTexturePath1, &width, &height, &nrChannels, 0);
	
	if(image != nullptr)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

		std::cout << "Texture ID: " << texture << std::endl;
		std::cout << "Width : " << width << " - Height : " << height << std::endl;
	}
	else
	{
		std::cout << "Texture couldn't load" << std::endl;
	}
}