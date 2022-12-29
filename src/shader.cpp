#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(){}; //empty constructor

ShaderProgram::ShaderProgram(std::string shaderPath, ShaderType shaderType){
    ID = glCreateProgram();
    if (!ID){
        std::cout<<"Error creating shader program"<<std::endl;
        return;
    }

    switch (shaderType)
    {
    case ShaderType::VERTEX:
        AddShader(shaderPath, GL_VERTEX_SHADER);
        break;
    
    case ShaderType::FRAGMENT:
        AddShader(shaderPath, GL_FRAGMENT_SHADER);
        break;
    
    case ShaderType::COMPUTE:
        AddShader(shaderPath, GL_COMPUTE_SHADER);
        break;
    default:
        break;
    }

    CompileShaders();
}

ShaderProgram::ShaderProgram(std::string vertexPath, std::string fragmentPath){

    ID = glCreateProgram();
    
    if (!ID){
        std::cout<<"Error creating shader program"<<std::endl;
        return;
    }

    AddShader(vertexPath, GL_VERTEX_SHADER);
    AddShader(fragmentPath, GL_FRAGMENT_SHADER);

    CompileShaders();

}

void ShaderProgram::AddShader(std::string shaderPath, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);

    // Get code from shaderPath
    std::string shaderCode;
    std::ifstream shaderFile;
    std::stringstream fileBuffer;


    // TODO error checking here
    //
    shaderFile.open(shaderPath);
    fileBuffer << shaderFile.rdbuf();
    shaderCode = fileBuffer.str();

    shaderFile.close();

    // Create an array of strings with a single entry
    const GLchar* theCode[1];
    theCode[0] = shaderCode.c_str();

    // Create an array of string lengths with a single entry
    GLint codeLength[1];
    codeLength[0] = shaderCode.length();

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    /* docstring for glShaderSource
    void glShaderSource( GLuint shader,	GLsizei count,	const GLchar **string, 	const GLint *length);
    
    Parameters
            shader: Specifies the handle of the shader object whose source code is to be replaced.
            count:  Specifies the number of elements in the string and length arrays.
            string: Specifies an array of pointers to strings containing the source code to be loaded into the shader.
            length: Specifies an array of string lengths.
    */

    // Getting detailed error logs
    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    // Compile the shaders
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        std::cout<<"Error compiling the "<<shaderType<<" shader:\n"<<eLog<<std::endl;
        return;
    }

    glAttachShader(ID,theShader);

    return;
}

void ShaderProgram::CompileShaders()
{

    // Getting detailed error logs
    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    // Compile the shaders
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(ID, sizeof(eLog), NULL, eLog);
        std::cerr<<"Error linking program:\n"<<eLog<<"\n";
        return;
    }

    glValidateProgram(ID);
    glGetProgramiv(ID, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(ID, sizeof(eLog), NULL, eLog);
        std::cerr<<"Error validating program:\n"<<eLog<<std::endl;
        return;
    }
}

void ShaderProgram::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()) , (int)value);
}

void ShaderProgram::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
}

void ShaderProgram::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID,name.c_str()),value);
}

void ShaderProgram::setVec2(const std::string &name, glm::vec2 value) const
{
    glUniform2fv(glGetUniformLocation(ID,name.c_str()),1,glm::value_ptr(value));
}


void ShaderProgram::setVec3(const std::string &name, glm::vec3 value) const
{
    glUniform3fv(glGetUniformLocation(ID,name.c_str()),1,glm::value_ptr(value));
}

void ShaderProgram::setMat4(const std::string &name, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID,name.c_str()),1,GL_FALSE,glm::value_ptr(value));
}