// Copyright 1998 - 2015 Epic Games, Inc.All Rights Reserved.
#if WITH_EDITORONLY_DATA

#pragma once

#include "ActorHandleBase.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class UActorHandleBase : public UStaticMeshComponent
{
	GENERATED_UCLASS_BODY()

	virtual void TickComponent
	(
	float DeltaTime,
	enum ELevelTick TickType,
		FActorComponentTickFunction * ThisTickFunction
		) override;

public:
	bool bShouldRender;
	bool bDrawDebugMeshes;
	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		virtual void DrawDebugMeshes();

private:
	FVector StartingScale;
	FRotator CorrectionRotation;

	FVector GetHMDWorldLocation(void);

};

#endif