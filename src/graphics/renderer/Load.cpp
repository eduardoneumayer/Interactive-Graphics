#include "Load.hpp"
#include <iostream>
#include <functional>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void Load::loadObjFile(std::vector<float>& vertices, std::vector<float>& uvs, const char* objFilePath, bool flipUVs)
{
    Assimp::Importer importer;
    unsigned flags =
        aiProcess_Triangulate |
        aiProcess_GenNormals |            // gera normais se não houver (não sobrescreve se houver)
        aiProcess_ImproveCacheLocality |
        aiProcess_SortByPType |
        aiProcess_JoinIdenticalVertices;  // opcional; ajuda a reduzir duplicatas

    if (flipUVs) flags |= aiProcess_FlipUVs;

    const aiScene* scene = importer.ReadFile(objFilePath, flags);
    if (!scene || !scene->mRootNode || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)) {
        std::cout << "Assimp falhou ao abrir " << objFilePath
                  << " -> " << importer.GetErrorString() << std::endl;
        return;
    }

    // limpa saídas
    vertices.clear();
    uvs.clear();
    normal.clear();
    triangleIndex.clear();

    // Vamos percorrer a cena inteira e achatar tudo em um único vetor.
    unsigned baseVertex = 0;

    std::function<void(aiNode*)> dfs = [&](aiNode* node){
        // processa as meshes deste nó
        for (unsigned mi = 0; mi < node->mNumMeshes; ++mi) {
            aiMesh* m = scene->mMeshes[node->mMeshes[mi]];

            // guardamos o offset deste bloco de vertices 
            unsigned start = baseVertex;

            // --- Vértices / Normais / UVs ---
            bool hasNormals = m->HasNormals();
            bool hasTex0   = m->HasTextureCoords(0); // canal 0 de UV

            for (unsigned i = 0; i < m->mNumVertices; ++i) {
                const aiVector3D& p = m->mVertices[i];
                vertices.push_back(p.x); vertices.push_back(p.y); vertices.push_back(p.z);

                if (hasNormals) {
                    const aiVector3D& n = m->mNormals[i];
                    normal.push_back(n.x); normal.push_back(n.y); normal.push_back(n.z);
                } else {
                    normal.push_back(0.f); normal.push_back(0.f); normal.push_back(1.f);
                }

                if (hasTex0) {
                    // Assimp usa vec3 para UV, mas z=0; pegamos xy
                    const aiVector3D& t = m->mTextureCoords[0][i];
                    uvs.push_back(t.x); uvs.push_back(t.y);
                } else {
                    uvs.push_back(0.f); uvs.push_back(0.f);
                }
            }

            // avançamos o total de vértices já escritos
            baseVertex += m->mNumVertices;

            // --- Índices (faces já trianguladas por aiProcess_Triangulate) ---
            for (unsigned f = 0; f < m->mNumFaces; ++f) {
                const aiFace& face = m->mFaces[f];
                // devem ser 3 por causa do Triangulate, mas iteramos por segurança
                for (unsigned j = 0; j < face.mNumIndices; ++j) {
                    triangleIndex.push_back(static_cast<int>(start + face.mIndices[j]));
                }
            }
        }

        // recursão nos filhos
        for (unsigned c = 0; c < node->mNumChildren; ++c)
            dfs(node->mChildren[c]);
    };

    dfs(scene->mRootNode);

    std::cout << "Loaded (Assimp) " << vertices.size()/3 << " vertices, "
              << normal.size()/3 << " normals, "
              << uvs.size()/2 << " uvs, "
              << triangleIndex.size()/3 << " triangles from " << objFilePath
              << std::endl;
}