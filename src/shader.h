#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

enum class ShaderType{
    VERTEX,
    FRAGMENT,
    COMPUTE
};

class ShaderProgram{
/*

*/
    public:    

        //constructor reads and builds the shader
        ShaderProgram();
        ShaderProgram(std::string shaderPath, ShaderType shaderType);
        ShaderProgram(std::string vertexPath, std::string fragmentPath);

        void use(){ glUseProgram(ID);}
        GLuint getID(){ return ID;}

        //Uniform tools
        //Can I make this a template? (const at the end ensures that function can't change member attrs)
        void setBool (const std::string &name, bool value) const;
        void setInt  (const std::string &name, int  value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec3 (const std::string &name, glm::vec3 value) const;
        void setVec2 (const std::string &name, glm::vec2 value) const;
        void setMat4 (const std::string &name, glm::mat4 value) const;

    private:

        GLuint ID;        

        void AddShader(std::string shaderCode, GLenum shaderType);
        void CompileShaders();

};

#endif 