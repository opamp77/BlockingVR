#if WITH_EDITOR

#include "BlockingVRPrivatePCH.h"
#include "DirectionalLightHandleComponent.h"


UDirectionalLightHandleComponent::UDirectionalLightHandleComponent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	SetMaterial(0, LoadObject<UMaterialInstance>(nullptr,
		TEXT("MaterialInstanceConstant'/BlockingVR/Example/Menus/Materials/DirectionalLightIcon.DirectionalLightIcon'")));
}

void UDirectionalLightHandleComponent::DrawDebugMeshes(void)
{

}

#endif