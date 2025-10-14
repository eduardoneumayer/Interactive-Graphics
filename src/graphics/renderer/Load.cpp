#include "Load.hpp"


void Load::loadObjFile(std::vector<float>& vertices, const char* objFilePath) {
        std::ifstream file(objFilePath);
        if (!file.is_open()) {
            std::cout << "Can't open obj file " << objFilePath << std::endl;
            return;
        }

        vertices.clear();
        triangleIndex.clear(); // Assumindo que triangleIndex é um std::vector<int> membro da classe
        normal.clear();

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string type;
            iss >> type;

            if (type == "v")
            {
                float x, y, z;
                if (iss >> x >> y >> z) {
                    vertices.push_back(x);
                    vertices.push_back(y);
                    vertices.push_back(z);
                }
            }

            else if (type == "vn")
            {
                float xn, yn, zn;
                if (iss >> xn >> yn >> zn)
                {
                    normal.push_back(xn);
                    normal.push_back(yn);
                    normal.push_back(zn);
                }
            }

            else if (type == "f") {
                std::vector<int> faceIndices;
                std::string vertexData;
                while (iss >> vertexData) {
                    
                    size_t slashPos = vertexData.find('/');
                    std::string vertexIndexStr = vertexData.substr(0, slashPos);
                    try {
                        int vertexIndex = std::stoi(vertexIndexStr) - 1; // OBJ usa índices base 1
                        faceIndices.push_back(vertexIndex);
                    } catch (const std::exception& e) {
                        std::cout << "Error parsing face index: " << vertexData << std::endl;
                    }
                }

                // Triangulação
                if (faceIndices.size() >= 3) {
                    for (size_t i = 1; i + 1 < faceIndices.size(); ++i) {
                        triangleIndex.push_back(faceIndices[0]);
                        triangleIndex.push_back(faceIndices[i]);
                        triangleIndex.push_back(faceIndices[i + 1]);
                    }
                }
            }
        }

        file.close();
        std::cout << "Loaded " << vertices.size() / 3 << " vertices and "
                << triangleIndex.size() / 3 << " triangles from " << objFilePath << std::endl;
    }

