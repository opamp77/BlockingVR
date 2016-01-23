// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#if WITH_EDITOR

#include "BlockingVRPrivatePCH.h"
#include "ParticleHandleComponent.h"

UParticleHandleComponent::UParticleHandleComponent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	SetMaterial(0, LoadObject<UMaterialInstance>(nullptr,
		TEXT("MaterialInstanceConstant'/BlockingVR/Example/Menus/Materials/EmitterIcon.EmitterIcon'")));
}

#endif