#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

Texture::Texture(std::vector<std::string> faces)
{
    std::cout << "Texture constructor called!" << std::endl;

    glGenTextures(1,&ID);      //   gero a textura
    Bind();             // bind para alterações
    setParameters();    // setar parametros da textura


    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &imageWidth, &imageHeight, &nrChannels, 0);
        if (data)
        {

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );

            glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

            std::cout << "Cubemap skybox: " << faces[i] << " loaded!" << std::endl;

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }

}

// DESTRUTOR, BIND E UNBIND PADROES

Texture::~Texture()
{
    std::cout << "Texture destructor called!" << std::endl;
    glDeleteTextures(1, &ID);
}  

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unBind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setParameters()
{
    // WRAP IN S AND T DIRECTION IF TEXTURE IS OUTSIDE OF THE st-texture (0-1)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      
    // setando todos os parametros dos filtros de textura padroes do opengl (min filter, mag filter, warp s e wrap t)
    // Minification filter: Quando está distante da superficie
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Magnificagtion filter: Quando está proximo a superficie e os texels se tornam grandes as vezes maiores que o pixel
    // nesse caso será usado Bi-linear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}   

void Texture::sendImageData()
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