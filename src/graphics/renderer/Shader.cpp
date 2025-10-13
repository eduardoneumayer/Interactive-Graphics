#include "Shader.hpp"
#include <iostream>


std::string loadFile(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::cout << "Shader called" << std::endl;

    //enquanto estamos fazendo tudo na main, armazenaremos o conteudo do vertex shader aqui.

    std::string vertexcode = loadFile(vertexPath);
    const char* vertexShaderSource = vertexcode.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);    // cria um shader com o nome dado

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);     // coloca o conteudo do shader dentro do source criado
    glCompileShader(vertexShader);    // compilar

    // verificando se a instalacao obteve sucesso ou nao
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    std::cout << "Vertex Shader compilled" << std::endl;


    // mesmo esquema de inicializacao para o fragment shader
    std::string fragmentcode = loadFile(fragmentPath);
    const char* fragmentShaderSource = fragmentcode.c_str();

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetProgramiv(fragmentShader, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    std::cout << "Fragment Shader compilled" << std::endl;

    // Shader program, linkando os dois shaders 
    ID = glCreateProgram();

    // anexa (attach) os dois shaders e linka no ID
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    std::cout << "Shader Program compilled" << std::endl;

}

Shader::~Shader()
{
    std::cout << "Shader Destructor called " << '\n';
}

void Shader::Activate()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}
