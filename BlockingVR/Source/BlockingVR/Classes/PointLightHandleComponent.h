// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#if WITH_EDITOR

#pragma once
#include "LightHandleBase.h"
#include "PointLightHandleComponent.generated.h"

UCLASS()
class UPointLightHandleComponent : public ULightHandleBase
{
	GENERATED_UCLASS_BODY()
	virtual void DrawDebugMeshes() override;
public:

private:

};

#endif