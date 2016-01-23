// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#if WITH_EDITOR

#pragma once
#include "LightHandleBase.h"
#include "SkyLightHandleComponent.generated.h"

UCLASS()
class USkyLightHandleComponent : public ULightHandleBase
{
	GENERATED_UCLASS_BODY()

	virtual void DrawDebugMeshes() override;

public:

private:

};

#endif