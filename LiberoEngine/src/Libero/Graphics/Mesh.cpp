#include "Liber_pch.h"
#include "Mesh.h"

#include "assimp/postprocess.h"

namespace Libero
{
	Mesh::Mesh(const std::string& filename, size_t meshIdx)
	{
		m_pImporter = new Assimp::Importer{};

		m_pImporter->SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_TRIANGLE);
		m_pScene = m_pImporter->ReadFile(filename, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
		m_pMesh = m_pScene->mMeshes[meshIdx];
	}

	Mesh::~Mesh()
	{
		SafeDelete(m_pImporter);
	}

	const aiScene* Mesh::GetScene() const
	{
		return m_pScene;
	}
	aiMesh* Mesh::GetMesh() const
	{
		return m_pMesh;
	}
}
