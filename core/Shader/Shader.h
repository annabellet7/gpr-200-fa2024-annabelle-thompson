#ifndef SHADER_H
#define SHADER_H

#include "..\ew\external\glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

	class Shader
	{
	public:
		unsigned int mId;

		Shader(const char* vertexPath, const char* fragmentPath);

		void use();

		void setBool(const std::string &name, bool value) const;
		void setFloat(const std::string &name, float value) const;
		void setInt(const std::string &name, int value) const;

	};

#endif