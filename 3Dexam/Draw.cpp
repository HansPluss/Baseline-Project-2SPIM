#include "Draw.h"
#include "glm/glm.hpp"
#include "Resources/Shaders/shaderClass.h"
#include "glm/gtc/type_ptr.hpp"

Draw::Draw()
{
}

std::vector<Vertex> Draw::DrawCube(glm::vec3 Color, glm::vec3 pos, glm::vec3 size)
{
    
    position = pos; 
    objSize = size; 

    std::vector<Vertex> vertices;
    vertices.resize(8);
    glm::vec3 sizeXYZ = glm::vec3(1.f, 1.f, 1.f);

    // Front face vertices
    Vertex v0{ -sizeXYZ.x, -sizeXYZ.y, sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v1{ sizeXYZ.x, -sizeXYZ.y, sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v2{ sizeXYZ.x, sizeXYZ.y, sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v3{ -sizeXYZ.x, sizeXYZ.y, sizeXYZ.z ,  Color.x, Color.y, Color.z, 0.0f, 0.0f };

    // Right face vertices
    Vertex v4{ -sizeXYZ.x, -sizeXYZ.y, sizeXYZ.z, Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v5{ sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v6{ sizeXYZ.x, sizeXYZ.y, sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v7{ -sizeXYZ.x, sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 0.0f };

   

    // Assign vertices to CubeArray
    vertices = {
        v0, // Front bottom left
        v1, // Front bottom right
        v2, // Front top right
        v3, // Front top left
        v4, // Back bottom left
        v5, // Back bottom right
        v6, // Back top right
        v7  // Back top left
    };
    indices = {
    // Front face
    0, 1, 2,   0, 2, 3,
    // Back face
    4, 6, 5,   4, 7, 6,
    // Left face
    0, 3, 7,   0, 7, 4,
    // Right face
    1, 6, 5,   1, 2, 6,
    // Top face
    3, 2, 6,   3, 6, 7,
    // Bottom face
    0, 5, 4,   0, 1, 5
    };

    return vertices;
    
}

std::vector<Vertex> Draw::DrawSphere(glm::vec3 Color, glm::vec3 pos, glm::vec3 size)
{
    position = pos;
    objSize = size;
    
    
    return std::vector<Vertex>();
}

void Draw::Initalize()
{
    //bind the VAO And VBO
    VAO.Bind();
    VBO.Bind();
    EBO.Bind();

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);


    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    //link vertex position, color, textrue coordinates
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    //unbind
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

void Draw::Render(Shader Shader, glm::mat4 viewproj)
{


    glm::mat4 model2 = glm::mat4(1.0f);
    model2 = glm::translate(model2, position);
    model2 = glm::scale(model2, objSize);
    glUniformMatrix4fv(glGetUniformLocation(Shader.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewproj * model2));
    VAO.Bind();
    VBO.Bind();
    EBO.Bind();
   
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);



    //unbind
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();

}

void Draw::Delete()
{
    VAO.Delete();
    VBO.Delete();
    EBO.Delete();
}
