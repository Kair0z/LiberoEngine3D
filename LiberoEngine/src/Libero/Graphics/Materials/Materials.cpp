#include "Liber_pch.h"
#include "Materials.h"
#include "MaterialMaster.h"
#include "Libero/Math/Color/Colors.h"
namespace Libero
{
    IMaterial* Libero::LiberoMaterials::DefaultMaterial()
    {
        MaterialMaster* pMatMaster = MaterialLocator::Get();

        IMaterial* pResult = pMatMaster->GetMaterial("Libero_DefaultMaterial");
        if (!pResult)
        {
            MatDefaultShaded* pDefaultShade = pMatMaster->CreateMaterial<MatDefaultShaded>("Libero_DefaultMaterial");
            pDefaultShade->SetDefaultColor(Colors::OffWhite);

            pResult = pDefaultShade;
        }

        return pResult;
    }
}

