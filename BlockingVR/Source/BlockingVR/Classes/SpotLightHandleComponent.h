// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#if WITH_EDITORONLY_DATA

#pragma once
#include "LightHandleBase.h"
#include "SpotLightHandleComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class USpotLightHandleComponent : public ULightHandleBase
{
	GENERATED_UCLASS_BODY()

	virtual void DrawDebugMeshes() override;

public:

private:

};

#endif