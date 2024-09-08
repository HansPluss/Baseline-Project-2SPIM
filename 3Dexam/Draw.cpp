#include "Draw.h"
#include "glm/glm.hpp"
#include "Resources/Shaders/shaderClass.h"
#include "glm/gtc/type_ptr.hpp"

Draw::Draw() : rotation(glm::quat(0.0, 0.0, 0.0, 0.0))
{
}

void Draw::DrawCube(glm::vec3 Color, glm::vec3 pos, glm::vec3 size)
{
    
    position = pos; 
    objSize = size; 

    vertices.resize(8);
    glm::vec3 sizeXYZ = glm::vec3(1.f, 1.f, 1.f);

    // Front face vertices
    Vertex v0{ -sizeXYZ.x, -sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v1{ sizeXYZ.x, -sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v2{ sizeXYZ.x,  sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v3{ -sizeXYZ.x,  sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 0.0f };

    Vertex v4{ -sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v5{ sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v6{ sizeXYZ.x,  sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v7{ -sizeXYZ.x,  sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 0.0f };

    
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

    

    // Corrected indices
         indices = {
             // Front face
             0, 1, 2, 2, 3, 0,
             // Back face
             4, 5, 6, 6, 7, 4,
             // Left face
             4, 0, 3, 3, 7, 4,
             // Right face
             1, 5, 6, 6, 2, 1,
             // Top face
             3, 2, 6, 6, 7, 3,
             // Bottom face
             4, 5, 1, 1, 0, 4
         };

    this->Initalize();
}

void Draw::DrawBoundingBox(glm::vec3 Color, glm::vec3 pos, glm::vec3 size)
{
    position = pos;
    objSize = size;

    vertices.resize(8);
    glm::vec3 sizeXYZ = glm::vec3(1.f, 1.f, 1.f);

    // Front face vertices
    Vertex v0{ -sizeXYZ.x, -sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v1{ sizeXYZ.x, -sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v2{ sizeXYZ.x,  sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v3{ -sizeXYZ.x,  sizeXYZ.y,  sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 0.0f };

    Vertex v4{ -sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v5{ sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v6{ sizeXYZ.x,  sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v7{ -sizeXYZ.x,  sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 0.0f };


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



    // Corrected indices
    indices = {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Back face
        4, 5, 6, 6, 7, 4,
        // Left face
        4, 0, 3, 3, 7, 4,
        // Right face
        1, 5, 6, 6, 2, 1
    };

    this->Initalize();
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
     // Bind the VAO
    VAO.Bind();

    // Bind the VBO and upload vertex data
    VBO.Bind();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Set vertex attributes pointers
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, x)); // Position
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, r)); // Color
    VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, u)); // TexCoords

    // Bind the EBO and upload index data
    EBO1.Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Unbind VAO, VBO, EBO
    VAO.Unbind();
    VBO.Unbind();
    EBO1.Unbind();
}

void Draw::Render(Shader Shader, glm::mat4 viewproj)
{

    //// Ensure VAO, VBO, EBO are generated
    ////if (VAO.ID == 0 || VBO.ID == 0 || EBO.ID == 0) {
    ////    std::cerr << "Error: VAO, VBO, or EBO not generated." << std::endl;
    ////    return;  // Exit early to avoid using uninitialized objects
    ////}
    //std::cout << "Indecies " << indices.size() << " |   Vertices " << vertices.size() << std::endl;
    //if (vertices.empty() || indices.empty()) {
    //    std::cerr << "Error: Vertices or indices are empty." << std::endl;
    //    return;
    //}
    //GLint success;
    //glGetProgramiv(Shader.ID, GL_LINK_STATUS, &success);
    //if (!success) {
    //    std::cerr << "Error: Shader program linking failed." << std::endl;
    //    return;
    //}




    glm::mat4 model2 = glm::mat4(1.0f);
    
    glm::quat quaterninon = glm::quat(0.0, 0.0, 0.0, 0.0);
    //glm::mat4 rotationMatrix = glm::mat4_cast(quaterninon);
    rotation = glm::mat4_cast(quaternion1);
    model2 *= rotation;
    model2 = glm::translate(model2, position);
    model2 = glm::scale(model2, objSize);
    glUniformMatrix4fv(glGetUniformLocation(Shader.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewproj * model2));
    VAO.Bind();
    VBO.Bind();
    EBO1.Bind();
   
   glDrawElements(GL_TRIANGLES,indices.size(), GL_UNSIGNED_INT, 0);
   // glDrawArrays(GL_POINT, 0, vertices.size());
    //unbind
    VAO.Unbind();
    VBO.Unbind();
    EBO1.Unbind();


}

glm::vec3 Draw::GetPosition()
{
    return position; 
}

glm::vec3 Draw::GetSize()
{
    return objSize; 
}

void Draw::SetPosition(glm::vec3 newPos)
{
    position = newPos; 
}

float Draw::GetMass()
{
    return mass;
}

void Draw::SetMass(float newMass)
{
    mass = newMass;
}

void Draw::SetVelocity(glm::vec3 newVelocity)
{
    velocity = newVelocity;
}

glm::vec3 Draw::GetVelocity()
{
    return velocity;
}

void Draw::ApplyForce(glm::vec3 force)
{
    // F = M * A
    Acceleration += force / mass;
}

void Draw::Update(float deltaTime)
{
    velocity += Acceleration * deltaTime;
    position += velocity * deltaTime;
    Acceleration = glm::vec3(0.00f, 0.0f, 0.0f);
}

void Draw::MoveXdir()
{
    position.x += speed;
}




void Draw::Delete()
{
    VAO.Delete();
    VBO.Delete();
    EBO1.Delete();
}

void Draw::SetNormalVector(glm::vec3 normal)
{
    normalvector = normal;
}

void Draw::SetAngularVelocity(glm::vec3 angularVelocity)
{
    AngularVelocity = angularVelocity;
}

glm::vec3 Draw::GetAngularVelocity()
{
    return AngularVelocity;
}

void Draw::RotateCube(float deltaTime)
{
    glm::vec3 velocityDirection;
    if (AngularVelocity.x != 0 || AngularVelocity.z != 0 ) {
        glm::vec3 velocityDirection = glm::normalize(AngularVelocity);
       // std::cout << "V Dir " << velocityDirection.x << ", " << velocityDirection.z << std::endl;
    }
    
    float speed = glm::length(AngularVelocity);

    glm::quat yRotation = glm::angleAxis(glm::radians(1.10f), glm::vec3(0.0f, speed, 0.0f));
    quaternion1 = yRotation * quaternion1 * deltaTime;  // Update rotation (quaternion math)
    quaternion1 = glm::normalize(quaternion1);

    glm::mat4 newRotationMatrix = glm::mat4_cast(quaternion1);
    rotation = newRotationMatrix;
    position += AngularVelocity * deltaTime;
}

glm::vec3 Draw::GetNormal()
{
    return normalvector;
}

