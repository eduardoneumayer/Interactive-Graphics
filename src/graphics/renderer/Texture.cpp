#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

Texture::Texture(const std::string &textureFile)
{
    std::cout << "Texture constructor called!" << std::endl;

    glGenTextures(1,&_ID);      //   gero a textura
    Bind();             // bind para alterações
    setParameters();    // setar parametros da textura

    // carregar texture file
    imageData = stbi_load(textureFilePath.c_str(), &imageWidth, &imageHeight, &nrChannels, 0);

    if(imageData)
    {
        std::cout << "Texture: " << textureFilePath << "loaded" << std::endl;
        sendImageData();        // chama a função que manda os dados da textura

        glGenerateMipmap( GL_TEXTURE_2D );      

        stbi_image_free(imageData);     // free na memória depois de usar
    }
    else
    {
        std::cout << "failed loading texture" << std::endl;
    }
}

// DESTRUTOR, BIND E UNBIND PADROES

Texture::~Texture()
{
    std::cout << "Texture destructor called!" << std::endl;
    glDeleteTextures(1, &ID);
}

Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);
}

Texture::unBind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::setParameters()
{
    // setando todos os parametros dos filtros de textura padroes do opengl (min filter, mag filter, warp s e wrap t)
    // Minification filter: Quando está distante da superficie
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MIPMAPPING);

    // Magnificagtion filter: Quando está proximo a superficie e os texels se tornam grandes as vezes maiores que o pixel
    // nesse caso será usado Bi-linear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // WRAP IN S AND T DIRECTION IF TEXTURE IS OUTSIDE OF THE st-texture (0-1)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Texture::sendImageData()
{
    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

    // funcao pronta do opengl que, com todos esses parametros, manda os dados da textura
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        imageWidth,
        imageHeight,
        0,
        format,
        GL_UNSIGNED_BYTE,
        imageData
    );
}