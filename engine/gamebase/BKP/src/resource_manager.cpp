#include <resource_manager.h>

#include <iostream>
#include <sstream>
#include <fstream>

#include <stb_image.h>

// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::textures;
std::map<std::string, Shader>       ResourceManager::shaders;


Shader ResourceManager::loadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
{
    shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return shaders[name];
}

Shader& ResourceManager::getShader(std::string name)
{
    return shaders[name];
}

Texture2D ResourceManager::loadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
    textures[name] = loadTextureFromFile(file, alpha);
    return textures[name];
}

Texture2D& ResourceManager::getTexture(std::string name)
{
    return textures[name];
}

void ResourceManager::clear()
{
    // (Properly) delete all shaders
    for (auto iter : shaders)
        glDeleteProgram(iter.second.ID);
    // (Properly) delete all textures
    for (auto iter : textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // If geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    const GLchar *gShaderCode = geometryCode.c_str();
    // 2. Now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
{
    // Create Texture object
    Texture2D texture;
    if (alpha)
    {
        texture.internal_Format = GL_RGBA;
        texture.image_Format = GL_RGBA;
    }
    // Load image
    int width, height, nrChannels;
    unsigned char* image = stbi_load(file, &width, &height, &nrChannels, texture.image_Format == GL_RGBA ? STBI_rgb_alpha : STBI_rgb);
    if (!image)
    {
        std::cout << "Failed to load texture file" << std::endl;
    }
    // Now generate texture
    texture.generate(width, height, image);
    // And finally free image data
    stbi_image_free(image);
    return texture;
}
