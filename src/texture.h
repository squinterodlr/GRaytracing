#include <GL/glew.h>
#include "stb_image.h"

class Texture{

    public:
        Texture();

        Texture(char* filename);

        void LoadTexture(); 
        void UseTexture(); // actually set texture at current object
        void ClearTexture();

        ~Texture();

    private:

        GLuint textureID;
        int width, height, bitDepth;

        char* fileLocation;



};