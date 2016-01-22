// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#if WITH_EDITOR

#include "BlockingVRPrivatePCH.h"
#include "PointLightHandleComponent.h"


UPointLightHandleComponent::UPointLightHandleComponent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	SetMaterial(0, LoadObject<UMaterialInstance>(nullptr,
		TEXT("MaterialInstanceConstant'/BlockingVR/Example/Menus/Materials/PointLightIcon.PointLightIcon'")));
}


void UPointLightHandleComponent::DrawDebugMeshes(void)
{
	APointLight* Light = Cast<APointLight>(GetOwner());
	if (Light)
	{
		FTransform T = FTransform();
		T.SetLocation(Light->GetActorLocation());
		float Radius = Cast<UPointLightComponent>(Light->GetLightComponent())->AttenuationRadius;
		
		DrawDebugCircle(GetWorld(), T.ToMatrixNoScale(), Radius, 64, FColor(127, 127, 0), false, 0.014, 0, 2, false);
		FRotator R = FRotator(0, 90, 0);
		T.SetRotation(R.Quaternion());
		DrawDebugCircle(GetWorld(), T.ToMatrixNoScale(), Radius, 64, FColor(127, 127, 0), false, 0.014, 0, 2, false);
		R = FRotator(90, 90, 0);
		T.SetRotation(R.Quaternion());
		DrawDebugCircle(GetWorld(), T.ToMatrixNoScale(), Radius, 64, FColor(127, 127, 0), false, 0.014, 0, 2, false);
	}
}

#endif