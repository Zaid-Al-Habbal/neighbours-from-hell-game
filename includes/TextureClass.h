#ifndef TEXTURECLASS_CLASS_H
#define TEXTURECLASS_CLASS_H

#include<glad/glad.h>
#include<stb_image.h>

#include"shader.h"

class TextureClass
{
public:
	GLuint ID;
	GLenum type;
    GLenum texSlot;
	TextureClass(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
	TextureClass();
	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();
	//enable material:
	static void enable(Shader mainShader, TextureClass diffuseTex, TextureClass specularTex);
};
#endif