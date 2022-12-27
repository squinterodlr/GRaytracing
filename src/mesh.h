#ifndef MESH_H
#define MESH_H

#include <string>
#include <GL/glew.h>

class Mesh{

    public:
        Mesh();
        
        void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numofVertices, unsigned int numofIndices);
        void RenderMesh();
        void ClearMesh();

        // Destructor
        ~Mesh();

    private:
        GLuint VAO, VBO, EBO;
        GLsizei indexCount;

};

#endif