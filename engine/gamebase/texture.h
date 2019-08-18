#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>


class Texture2D
{
public:
	// Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
	GLuint ID;
	// Texture image dimensions
	GLuint width, height; // Width and height of loaded image in pixels
	// Texture Format
	GLuint internal_Format; // Format of texture object
	GLuint image_Format; // Format of loaded image
	// Texture configuration
	GLuint wrap_S; // Wrapping mode on S axis
	GLuint wrap_T; // Wrapping mode on T axis
	GLuint filter_Min; // Filtering mode if texture pixels < screen pixels
	GLuint filter_Max; // Filtering mode if texture pixels > screen pixels
	// Constructor (sets default texture modes)
	Texture2D();
	// Generates texture from image data
	void generate(GLuint width, GLuint height, unsigned char* data);
	// Binds the texture as the current active GL_TEXTURE_2D texture object
	void bind() const;

protected:

private:
};

#endif // TEXTURE_H
