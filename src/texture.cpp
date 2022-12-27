#include "texture.h"
#include <iostream>

Texture::Texture(){

    textureID = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    fileLocation = "";
}

Texture::Texture(char* filename){

    textureID = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    fileLocation = filename;

}

void Texture::LoadTexture(){

    // an array of chars is just a bitstring
    unsigned char *texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);

    // check it's loaded
    if (!texData){
        std::cerr<<"Failed to find: "<<fileLocation<<std::endl;
    }

    // generate and bind to texture buffer
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);


    // TODO write method to change parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,0);

    stbi_image_free(texData);
}

void Texture::UseTexture(){

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

}

void Texture::ClearTexture(){

    glDeleteTextures(1, &textureID);
    textureID = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    fileLocation = "";

}

Texture::~Texture(){

    ClearTexture();
}
