#pragma once

#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/mesh.h"

namespace Libero
{
	class Mesh final
	{
	public:
		Mesh(const std::string& filename, size_t meshIdx = 0);
		~Mesh();

		const aiScene* GetScene() const;
		aiMesh* GetMesh() const;

	private:
		Assimp::Importer* m_pImporter = nullptr;
		const aiScene* m_pScene = nullptr;
		aiMesh* m_pMesh = nullptr;
	};
}


