// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#if WITH_EDITOR

#include "BlockingVRPrivatePCH.h"
#include "ActorHandleBase.h"

UActorHandleBase::UActorHandleBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	SetStaticMesh(LoadObject<UStaticMesh>(nullptr,
		TEXT("StaticMesh'/Engine/EditorLandscapeResources/FlattenPlaneMesh.FlattenPlaneMesh'")));
	bGenerateOverlapEvents = false;
	bCanEverAffectNavigation = false;
	SetCollisionProfileName(FName(TEXT("UI")));
	SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);

	CorrectionRotation = FRotator(180, 90, -90);
	bDrawDebugMeshes = false;
	bShouldRender = true;
	PrimaryComponentTick.bCanEverTick = true;
	bTickInEditor = false;
	StartingScale = FVector(0.001, 0.001, 0.001);

	//MaterialInstanceConstant'/BlockingVR/Menus/Materials/SomeMatherial.SomeMaterial' in subclasses
}

void UActorHandleBase::DrawDebugMeshes(void) //virtual base
{
}

FVector UActorHandleBase::GetHMDWorldLocation(void)
{
	FVector Result = FVector();
	if (GEngine->HMDDevice.IsValid() && GEngine->HMDDevice->IsHMDEnabled()) //check pointer is valid
	{
		FQuat OrientationAsQuat;
		FVector Position(0.f);
		GEngine->HMDDevice->GetCurrentOrientationAndPosition(OrientationAsQuat, Position);
		FVector Unrotated = OrientationAsQuat.Rotator().UnrotateVector(Position);
		FTransform CameraManagerT = GEngine->GetFirstLocalPlayerController(GetWorld())->PlayerCameraManager->GetTransform();
		FVector HMDWorldPosition = CameraManagerT.TransformPosition(Unrotated);
		Result = HMDWorldPosition;
	}
	return Result;
}

void UActorHandleBase::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bShouldRender)
	{		//Orient towards the player
		FVector HMDWorldPosition = GetHMDWorldLocation();
		FRotator LookAtRotation = (HMDWorldPosition - GetComponentLocation()).Rotation();
		FTransform T(LookAtRotation);
		T.ConcatenateRotation(CorrectionRotation.Quaternion());
		SetWorldRotation(T.GetRotation());
		//scale based on distance
		float Distance = FVector::Dist(GetComponentLocation(), HMDWorldPosition);

		FVector NewScale = StartingScale * Distance;
		SetWorldScale3D(NewScale);
	}
	if (bDrawDebugMeshes)
	{
		DrawDebugMeshes();
	}
}

#endif