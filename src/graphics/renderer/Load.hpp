#pragma once
#include<vector>
#include <glad/glad.h>
#include<fstream>
#include<sstream>
#include<iostream>


class Load
{
    public:
    
        std::vector<int> triangleIndex;
        std::vector<float> normal;

        void loadObjFile(std::vector<float> &vertices, const char * objFilePath);
};