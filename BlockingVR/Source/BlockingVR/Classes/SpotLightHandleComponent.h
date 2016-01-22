// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#if WITH_EDITOR

#pragma once
#include "LightHandleBase.h"
#include "SpotLightHandleComponent.generated.h"

UCLASS()
class USpotLightHandleComponent : public ULightHandleBase
{
	GENERATED_UCLASS_BODY()

	virtual void DrawDebugMeshes() override;

public:

private:

};

#endif