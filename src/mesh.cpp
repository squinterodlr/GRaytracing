#include "mesh.h"


Mesh::Mesh(){

    VAO = 0;
    VBO = 0;
    EBO = 0;
    indexCount = 0;

}

void Mesh::CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numofVertices, unsigned int numofIndices)
{
    /* Create a mesh with the given vertices and indices. We are
    assuming that the vertices are in the following format:
    x, y, z, u, v
    where x, y, z are the position coordinates, and u, v are the
    texture coordinates.

     * Input:
     * - vertices: array of type GLfloat that contains the vertices in the format
     *            x, y, z, u, v
     * - indices: array of type unsigned int that define the triangles
     * - numofVertices: length of vertices array
     * - numofIndices: length of indices array
     * Output:
     * - None  
    */
    indexCount = numofIndices;

    // Create and bind VAO
    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create and bind VBO
    glCreateBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*numofVertices, vertices, GL_STATIC_DRAW);

    // Create and bind EBO
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0])*numofIndices, indices, GL_STATIC_DRAW);

    // Attribute 0 is position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(vertices[0]), 0);
    glEnableVertexAttribArray(0);

    // Attribute 1 is texture coordinates. The offset is 3
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(vertices[0]), (void*)(3*sizeof(vertices[0])));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    glBindVertexArray(0);
}

void Mesh::RenderMesh()
{
    /* Render the mesh. The VAO is bound and the EBO is used to draw the triangles.
     * The VAO and EBO are unbound.
    */
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

void Mesh::ClearMesh()
{
    if (EBO != 0)
    {
        glDeleteBuffers(1,&EBO);
        EBO = 0;
    }

    if (VBO != 0)
    {
        glDeleteBuffers(1,&VBO);
        VBO = 0;
    }

    if (VAO != 0)
    {
        glDeleteVertexArrays(1,&VAO);
        VAO = 0;
    }

    indexCount = 0;
}

Mesh::~Mesh()
{
    ClearMesh();
}