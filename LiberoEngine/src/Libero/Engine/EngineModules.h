#pragma once

#include "Libero/Graphics/GraphicsMaster.h"
#include "Libero/Physics/PhysicsMaster.h"
#include "Libero/Interfaces/Observer/SubjectMaster.h"
#include "Libero/Content/ContentMaster.h"
#include "Libero/Files/FileMaster.h"
#include "Libero/Graphics/CameraMaster.h"
#include "Libero/ECS/ECSMaster.h"
#include "Libero/Input/InputMaster.h"
#include "Libero/Scene/SceneMaster.h"
#include "Libero/Graphics/Materials/MaterialMaster.h"
#include "Libero/Time/Time.h"
#include "Libero/Logging/Logger.h"
#include "Libero/Editor/Editor.h"

namespace Libero
{
	struct EngineModules
	{
		ECSMaster* m_pECSMaster{ nullptr };
		GraphicsMaster* m_pGraphicsMaster{ nullptr };
		SubjectMaster* m_pSubjectMaster{ nullptr };
		Editor* m_pEditor{ nullptr };
		InputMaster* m_pInputMaster{ nullptr };
		Time* m_pTime{ nullptr };
		SceneMaster* m_pSceneMaster{ nullptr };
		CameraMaster* m_pCameraMaster{ nullptr };
		ContentMaster* m_pContentMaster{ nullptr };
		Logger* m_pLogger{ nullptr };
		FileMaster* m_pFileMaster{ nullptr };
		MaterialMaster* m_pMaterialMaster{ nullptr };
		PhysicsMaster* m_pPhysicsMaster{ nullptr };
	};
}


