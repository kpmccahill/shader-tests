#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public: 
	unsigned int ID;
	// constructor reads and builds shader.
	Shader(const char* vertexPath, const char* fragmentPath);
	// use/activate shader
	void use();
	// uniform functions
	void setBool(const std::string &name, bool value) const; 
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
};

#endif
