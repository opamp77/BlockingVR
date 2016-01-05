// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#if WITH_EDITORONLY_DATA

#pragma once

#include "BlockingVRLightActorBase.generated.h"

UCLASS()
class ABlockingVRLightActorBase : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(Category = Light, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Light,Rendering,Rendering|Components|Light", AllowPrivateAccess = "true"))
	ULightComponent* LightComponent;
	//virtual void Tick(float DeltaSeconds) override;
public:

private:

};

#endif