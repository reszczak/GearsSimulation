#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class ShaderClass
{
public:
	GLuint ID;
	ShaderClass(const char* vertexFile, const char* fragmentFile);
	void Activate();
	void Delete();
private:
	void compileErrors(unsigned int shader, const char* type, std::string vertexCode);
};

#endif

