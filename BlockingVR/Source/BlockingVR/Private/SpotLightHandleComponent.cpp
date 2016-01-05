// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#if WITH_EDITORONLY_DATA

#include "BlockingVRPrivatePCH.h"
#include "SpotLightHandleComponent.h"


USpotLightHandleComponent::USpotLightHandleComponent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	SetMaterial(0, LoadObject<UMaterialInstance>(nullptr,
		TEXT("MaterialInstanceConstant'/BlockingVR/Example/Menus/Materials/SpotLightIcon.SpotLightIcon'")));
}

void USpotLightHandleComponent::DrawDebugMeshes(void)
{
	ASpotLight* Light = Cast<ASpotLight>(GetOwner());
	if (Light)
	{
		//Light->GetArrowComponent()->
		float Length = Cast<USpotLightComponent>(Light->GetLightComponent())->AttenuationRadius;
		float OuterAngle = Cast<USpotLightComponent>(Light->GetLightComponent())->OuterConeAngle;
		float InnerAngle = Cast<USpotLightComponent>(Light->GetLightComponent())->InnerConeAngle;
		FVector Direction = Light->GetLightComponent()->GetDirection();
		//outercone
		
		DrawDebugCone(GetWorld(), Light->GetActorLocation(), Direction, Length, 
			FMath::DegreesToRadians(OuterAngle), FMath::DegreesToRadians(OuterAngle), FMath::Clamp((int32)OuterAngle,16,64), FColor(127, 127, 0), false, 0.014);
		//innerangle
		if (InnerAngle > 0)
			DrawDebugCone(GetWorld(), Light->GetActorLocation(), Direction, Length, 
			FMath::DegreesToRadians(InnerAngle), FMath::DegreesToRadians(InnerAngle), FMath::Clamp((int32)InnerAngle, 16, 64), FColor(0, 127, 255), false, 0.014);
	}
}

#endif