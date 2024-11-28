#include"VAO.h"

// Constructor that generates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO Attribute such as a position or color to the VAO
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Binds the VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::init(VBO& VBO)
{
	this->Bind();
	this->LinkAttrib(VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    this->LinkAttrib(VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3*sizeof(float)));
    this->LinkAttrib(VBO, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(6*sizeof(float)));
	this->Unbind();
}
// Deletes the VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}