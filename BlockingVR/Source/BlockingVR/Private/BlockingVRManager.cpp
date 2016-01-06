// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#if WITH_EDITORONLY_DATA

#include "BlockingVRPrivatePCH.h"
#include "BlockingVRManager.h"
#include "LightHandleBase.h"
#include "PointLightHandleComponent.h"
#include "SpotLightHandleComponent.h"
#include "DirectionalLightHandleComponent.h"
#include "SkyLightHandleComponent.h"

ABlockingVRManager::ABlockingVRManager(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{	
	USceneComponent* comp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(comp);
}

void ABlockingVRManager::BeginPlay(void)
{
	Super::BeginPlay();
	//Attach PointLight Handles
	for (TActorIterator<APointLight> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
	{
		UPointLightHandleComponent* pComponent = NewObject<UPointLightHandleComponent>(*ActorItr, FName("LightHandleComponent"));
		if (pComponent)
		{
			pComponent->AttachTo(ActorItr->GetRootComponent(), NAME_None, EAttachLocation::SnapToTarget, false);
			pComponent->RegisterComponentWithWorld(GetWorld());
			ActorItr->SetActorHiddenInGame(false);
			pComponent->SetHiddenInGame(false);
			pComponent->SetVisibility(true);
		}
	}
	//Attach SpotLight Handles
	for (TActorIterator<ASpotLight> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
	{
		USpotLightHandleComponent* pComponent = NewObject<USpotLightHandleComponent>(*ActorItr, FName("LightHandleComponent"));
		if (pComponent)
		{
			pComponent->AttachTo(ActorItr->GetRootComponent(), NAME_None, EAttachLocation::SnapToTarget, false);
			pComponent->RegisterComponentWithWorld(GetWorld());
			ActorItr->SetActorHiddenInGame(false);
			pComponent->SetHiddenInGame(false);
			pComponent->SetVisibility(true);
		}
	}
	//Attach DirectionalLight Handles
	for (TActorIterator<ADirectionalLight> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
	{
		UDirectionalLightHandleComponent* pComponent = NewObject<UDirectionalLightHandleComponent>(*ActorItr, FName("LightHandleComponent"));
		if (pComponent)
		{
			pComponent->AttachTo(ActorItr->GetRootComponent(), NAME_None, EAttachLocation::SnapToTarget, false);
			pComponent->RegisterComponentWithWorld(GetWorld());
			ActorItr->SetActorHiddenInGame(false);
			pComponent->SetHiddenInGame(false);
			pComponent->SetVisibility(true);
		}
	}
	//Attach SkyLight Handles
	/*for (TActorIterator<ASkyLight> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
	{
		USkyLightHandleComponent* pComponent = NewObject<USkyLightHandleComponent>(*ActorItr, FName("LightHandleComponent"));
		if (pComponent)
		{
			pComponent->AttachTo(ActorItr->GetRootComponent(), NAME_None, EAttachLocation::SnapToTarget, false);
			pComponent->RegisterComponentWithWorld(GetWorld());
			ActorItr->SetActorHiddenInGame(false);
			pComponent->SetHiddenInGame(false);
			pComponent->SetVisibility(true);
		}
	}*/
}

UTexture2D* ABlockingVRManager::CreateActorThumbnailTexture(TSubclassOf<AActor> ActorIN)
{
	UPackage* PKG = Cast<UPackage>(ActorIN->GetOuter());
	if (!PKG) return nullptr;
	FName PackageName = FName(*PKG->GetName());
	return CreateThumbnailTexture(PackageName);
}

UTexture2D* ABlockingVRManager::CreateMeshThumbnailTexture(class UStaticMesh* MeshIN)
{
	UPackage* PKG = Cast<UPackage>(MeshIN->GetOuter());
	if (!PKG) return nullptr;
	FName PackageName = FName(*PKG->GetName());
	FString ObjectPath = PKG->GetName() + "." + MeshIN->GetName();
	FName Path = FName(*ObjectPath);
	return CreateThumbnailTexture(PackageName, Path);
}

UTexture2D* ABlockingVRManager::CreateSkeletalMeshThumbnailTexture(class USkeletalMesh* SMeshIN)
{
	UPackage* PKG = Cast<UPackage>(SMeshIN->GetOuter());
	if (!PKG) return nullptr;
	FName PackageName = FName(*PKG->GetName());
	FString ObjectPath = PKG->GetName() + "." + SMeshIN->GetName();
	FName Path = FName(*ObjectPath);
	return CreateThumbnailTexture(PackageName, Path);
}

UTexture2D* ABlockingVRManager::CreateMaterialThumbnailTexture(class UMaterial* MaterialIN)
{
	UPackage* PKG = Cast<UPackage>(MaterialIN->GetOuter());
	if (!PKG) return nullptr;
	FName PackageName = FName(*PKG->GetName()); 
	FString ObjectPath = PKG->GetName() + "." + MaterialIN->GetName();
	FName Path = FName(*ObjectPath);
	return CreateThumbnailTexture(PackageName, Path);
}

UTexture2D* ABlockingVRManager::CreateParticleThumbnailTexture(class UParticleSystem* ParticleIN)
{
	UPackage* PKG = Cast<UPackage>(ParticleIN->GetOuter());
	if (!PKG) return nullptr;
	FName PackageName = FName(*PKG->GetName());
	FString ObjectPath = PKG->GetName() + "." + ParticleIN->GetName();
	FName Path = FName(*ObjectPath);
	return CreateThumbnailTexture(PackageName,Path);
}

UTexture2D* ABlockingVRManager::CreateThumbnailTexture(FName PackageName ,FName ObjectPath) //private
{
	//TODO: NEED TO CREATE THUMBNAIL IF PACKAGE HAS YET TO BE SAVED...
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	
	if (ObjectPath == FName(""))
		AssetRegistryModule.Get().GetAssetsByPackageName(PackageName, AssetData);
	else
	{
		FARFilter Filter;
		Filter.PackageNames.Add(PackageName);
		Filter.ObjectPaths.Add(ObjectPath);
		AssetRegistryModule.Get().GetAssets(Filter, AssetData);
	}
	if (AssetData.Num() > 0)
	{	
		FString PackageFilename;
		if (FPackageName::DoesPackageExist(AssetData[0].PackageName.ToString(), nullptr, &PackageFilename))
		{
			FThumbnailMap ThumbnailMap;
			TSet<FName> ObjectFullNames;
			ObjectFullNames.Add(FName(*AssetData[0].GetFullName()));
			ThumbnailTools::LoadThumbnailsFromPackage(PackageFilename, ObjectFullNames, ThumbnailMap);
			const FObjectThumbnail* ThumbnailPtr = ThumbnailMap.Find(FName(*AssetData[0].GetFullName()));
			if (ThumbnailPtr)
			{
				TArray<uint8> Data = ThumbnailPtr->GetUncompressedImageData();
				UTexture2D* Texture = nullptr;
				Texture = UTexture2D::CreateTransient(ThumbnailPtr->GetImageWidth(), ThumbnailPtr->GetImageHeight());
				if (Texture)
				{
					FTexture2DMipMap& Mip = Texture->PlatformData->Mips[0];
					void* MipData = Mip.BulkData.Lock(LOCK_READ_WRITE);
					FMemory::Memcpy(MipData, &Data[0], Data.Num());
					Mip.BulkData.Unlock();
					Texture->UpdateResource();
				}
				return Texture;
			}
			else return nullptr;
		}
		else return nullptr;
	}
	else return nullptr;
}

void ABlockingVRManager::ApplyDeferredChanges(void)
{
	//Do deleted Editor Actors(Including lights)
	for (AActor* EditorActor : DeletedEditorActors)
	{
		GEditor->GetEditorWorldContext().World()->DestroyActor(EditorActor);
		UPackage* Package = Cast<UPackage>(GEditor->GetEditorWorldContext().World()->GetOuter());
		Package->SetDirtyFlag(true);
	}
	//Do add new editor Lights.
	for (const ALight* PIELight : NewEditorLights)
	{
		//PointLight
		if ((uint8)PIELight->GetLightComponent()->GetLightType() == (uint8)EBVRLightType::VBR_PointLight)
		{
			//add the editor Light
			APointLight* EditorPointLight = Cast<APointLight>(AddEditorLight(PIELight->GetTransform(), EBVRLightType::VBR_PointLight));
			if (EditorPointLight)
			{
				//needs to be set to movable temporarily to be able to apply certian properties such as radius/cone angles
				EditorPointLight->SetMobility(EComponentMobility::Movable);
				SetCommonEditorLightProperties(EditorPointLight, PIELight); //common properties
				EditorPointLight->SetRadius(Cast<UPointLightComponent>(PIELight->GetLightComponent())->AttenuationRadius); //radius
				EditorPointLight->GetLightComponent()->SetIESTexture(PIELight->GetLightComponent()->IESTexture); //IES
				EditorPointLight->GetLightComponent()->bUseIESBrightness = PIELight->GetLightComponent()->bUseIESBrightness;
				EditorPointLight->GetLightComponent()->IESBrightnessScale = PIELight->GetLightComponent()->IESBrightnessScale;
				EditorPointLight->SetMobility(EComponentMobility::Stationary); //all new lights will default to Stationary
			}
		}
		//SpotLight
		else if ((uint8)PIELight->GetLightComponent()->GetLightType() == (uint8)EBVRLightType::VBR_SpotLight)
		{
			ASpotLight* EditorSpotLight = Cast<ASpotLight>(AddEditorLight(PIELight->GetTransform(), EBVRLightType::VBR_SpotLight));
			if (EditorSpotLight)
			{
				//needs to be set to movable temporarily to be able to apply certain properties such as radius/cone angles
				EditorSpotLight->SetMobility(EComponentMobility::Movable);
				SetCommonEditorLightProperties(EditorSpotLight, PIELight); //common Properties
				
				USpotLightComponent* EditorSpotLightComponent = Cast<USpotLightComponent>(EditorSpotLight->GetLightComponent());
				USpotLightComponent* PIESpotLightComponent = Cast<USpotLightComponent>(PIELight->GetLightComponent());

				EditorSpotLightComponent->AttenuationRadius = PIESpotLightComponent->AttenuationRadius; //radius
				EditorSpotLightComponent->SetOuterConeAngle(PIESpotLightComponent->OuterConeAngle); //outercone
				EditorSpotLightComponent->SetInnerConeAngle(PIESpotLightComponent->InnerConeAngle); //InnerCone
				EditorSpotLight->GetLightComponent()->SetIESTexture(PIELight->GetLightComponent()->IESTexture); //IES
				EditorSpotLight->GetLightComponent()->bUseIESBrightness = PIELight->GetLightComponent()->bUseIESBrightness;
				EditorSpotLight->GetLightComponent()->IESBrightnessScale = PIELight->GetLightComponent()->IESBrightnessScale;

				EditorSpotLight->SetMobility(EComponentMobility::Stationary); //default Mobility
			}
		}
		//DirectionalLight...
		else if ((uint8)PIELight->GetLightComponent()->GetLightType() == (uint8)EBVRLightType::VBR_DirectionalLight)
		{
			ADirectionalLight* EditorDirectionalLight = Cast<ADirectionalLight>(AddEditorLight(PIELight->GetTransform(), EBVRLightType::VBR_DirectionalLight));
			if (EditorDirectionalLight)
			{
				SetCommonEditorLightProperties(EditorDirectionalLight, PIELight);
			}
		}
	}
	//Do to be Modified Editor Lights
	for (const ALight* PIELight : ModifiedEditorLights)
	{
		//find editor version and apply properties
		//TODO CHECK ALL SUBLEVELS FOR ACTOR
		if (GEditor->ObjectsThatExistInEditorWorld.Get(PIELight))
		{
			const bool bExactClass = false;
			ALight* EditorLight = FindObject<ALight>(GEditor->GetEditorWorldContext().World()->GetCurrentLevel(), *PIELight->GetFName().ToString(), bExactClass);
			if (EditorLight)
			{
				EComponentMobility::Type OriginalMobility = PIELight->GetRootComponent()->Mobility;
				EditorLight->SetMobility(EComponentMobility::Movable);

				//common poroperties of all lights
				SetCommonEditorLightProperties(EditorLight, PIELight);
				//pointlights
				if ((uint8)PIELight->GetLightComponent()->GetLightType() == (uint8)EBVRLightType::VBR_PointLight)
				{
					APointLight* EditorPointLight = Cast<APointLight>(EditorLight);
					const APointLight* PIEPointLight = Cast<APointLight>(PIELight);
					UPointLightComponent* PIEPointLightComponent = Cast<UPointLightComponent>(PIEPointLight->GetLightComponent());
					UPointLightComponent* EditorPointLightComponent = Cast<UPointLightComponent>(EditorPointLight->GetLightComponent());
					EditorPointLightComponent->bUseInverseSquaredFalloff = PIEPointLightComponent->bUseInverseSquaredFalloff;
					EditorPointLight->SetRadius(PIEPointLightComponent->AttenuationRadius);
				
				}
				//spotlights
				else if ((uint8)PIELight->GetLightComponent()->GetLightType() == (uint8)EBVRLightType::VBR_SpotLight)
				{
					ASpotLight* EditorSpotLight = Cast<ASpotLight>(EditorLight);
					const ASpotLight* PIESpotLight = Cast<ASpotLight>(PIELight);
					USpotLightComponent* PIESpotLightComponent = Cast<USpotLightComponent>(PIESpotLight->GetLightComponent());
					USpotLightComponent* EditorSpotLightComponent = Cast<USpotLightComponent>(EditorSpotLight->GetLightComponent());
					
					EditorSpotLightComponent->bUseInverseSquaredFalloff = PIESpotLightComponent->bUseInverseSquaredFalloff;
					EditorSpotLightComponent->AttenuationRadius = PIESpotLightComponent->AttenuationRadius; //radius
					EditorSpotLightComponent->SetOuterConeAngle(PIESpotLightComponent->OuterConeAngle); //outer
					EditorSpotLightComponent->SetInnerConeAngle(PIESpotLightComponent->InnerConeAngle); //inner
				}
				//Directional Lights
				else if ((uint8)PIELight->GetLightComponent()->GetLightType() == (uint8)EBVRLightType::VBR_DirectionalLight)
				{
					//COVERED BY SetCommonEditorLightProperties();
				}
				//TODO MODIFIED SKYLIGHTS...

				EditorLight->SetMobility(OriginalMobility); //restore original Mobility
			} //end if editor light
		}	//end exits in world
	} //end for
	
	/////////////////////////////////////////////////////////////////////////////
	//Do add new editor Actors
	for (AActor* PIEActor : NewEditorActors)
	{
		AddEditorActor(PIEActor->GetTransform(), PIEActor);
	}
	//Do to be modified Editor Actors
	for (const AActor* PIEActor : ModifiedEditorActors)
	{
		if (GEditor->ObjectsThatExistInEditorWorld.Get(PIEActor))
		{
			const bool bExactClass = false;
			//TODO CHECK ALL SUBLEVELS FOR ACTOR
			AActor* EditorActor = FindObject<AActor>(GEditor->GetEditorWorldContext().World()->GetCurrentLevel(), *PIEActor->GetFName().ToString(), bExactClass);
			if (EditorActor)
			{
				EditorActor->SetActorTransform(PIEActor->GetTransform());
			}
		}
	}
	DeletedEditorActors.Empty();
	NewEditorActors.Empty();
	NewEditorLights.Empty();
	ModifiedEditorActors.Empty();
	ModifiedEditorLights.Empty();
}

///////////////////////////////////////////////////////////////////////////////////

bool ABlockingVRManager::PIESetStaticMesh(UStaticMeshComponent* StaticMeshComponent,UStaticMesh* Mesh)
{
	if (!StaticMeshComponent || !Mesh) return false;
	EComponentMobility::Type OriginalMobility = StaticMeshComponent->GetAttachmentRoot()->Mobility;
	StaticMeshComponent->GetAttachmentRoot()->SetMobility(EComponentMobility::Movable);
	bool result = StaticMeshComponent->SetStaticMesh(Mesh);
	StaticMeshComponent->GetAttachmentRoot()->SetMobility(OriginalMobility);
	if (result)
	{
		AActor* Actor = StaticMeshComponent->GetAttachmentRootActor();
		if (Actor)
		{
			int32 Index = NewEditorActors.Find(Actor);
			if (Index == INDEX_NONE) NotifyModifiedActor(Actor);
		}
	}
	return result;
}

AActor* ABlockingVRManager::AddPIEActor(TSubclassOf<class AActor> Actor, FTransform T)
{
	if (!IsAllowedClass(Actor)) return nullptr;

	AActor* PIEActor = nullptr;
	FVector L = T.GetLocation();
	PIEActor = GetWorld()->SpawnActor(Actor,&L);
	
	if (PIEActor)
	{
		EComponentMobility::Type DefaultMobility = PIEActor->GetRootComponent()->Mobility;
		PIEActor->GetRootComponent()->SetMobility(EComponentMobility::Movable);
		PIEActor->SetActorTransform(T,false,nullptr, ETeleportType::TeleportPhysics);
		PIEActor->GetRootComponent()->SetMobility(DefaultMobility);
		PIEActor->MarkComponentsRenderStateDirty();
		//Currently the editor world additions are deffered until ApllyDeferredChanges()
		NewEditorActors.Add(PIEActor);	
	}
	return PIEActor;
}

void ABlockingVRManager::PastePIEActor(AActor* Actor, FVector Location)
{
	if (!Actor || !IsAllowedClass(Actor) ) return;
	
	ALight* Light = Cast<ALight>(Actor);

	//light Actor
	if (Light)
	{ 
		PastePIELight(Light, Location);
		return;
	}
	
	//StaticMeshActor
	else if (Actor->IsA(AStaticMeshActor::StaticClass()) )
	{
		//PasteMesh
		FTransform T = Actor->GetTransform();
		T.SetLocation(Location);
		AActor* PIEActor = AddPIEActor(Actor->GetClass(), T);

		if (PIEActor)
		{
			EComponentMobility::Type OriginalMobility = Actor->GetRootComponent()->Mobility;
			PIEActor->GetRootComponent()->SetMobility(EComponentMobility::Movable);
			Cast<AStaticMeshActor>(PIEActor)->GetStaticMeshComponent()->SetStaticMesh(Cast<AStaticMeshActor>(Actor)->GetStaticMeshComponent()->StaticMesh);
			PIEActor->GetRootComponent()->SetMobility(OriginalMobility);
			//ensure materials are the same
			TArray<UMaterialInterface*> MeshMaterials = Cast<AStaticMeshActor>(Actor)->GetStaticMeshComponent()->GetMaterials();
			for (int32 i = 0; i < MeshMaterials.Num(); i++)
			{
				Cast<AStaticMeshActor>(PIEActor)->GetStaticMeshComponent()->SetMaterial(i, MeshMaterials[i]);
			}
		}
	}
	//Other Actor
	else 
	{
		FTransform T = Actor->GetTransform();
		T.SetLocation(Location);
		AddPIEActor(Actor->GetClass(), T);
	}
}

void ABlockingVRManager::SetTransformPIEActor(AActor* Actor, FTransform T)
{
	if (!Actor || !IsAllowedClass(Actor)) return;
	TArray<bool> PhysicsEnabledList;
	TArray<ECollisionEnabled::Type> CollisionEnabledList;
	TArray<UActorComponent*> ComponentList = Actor->GetComponentsByClass(UStaticMeshComponent::StaticClass());
	for (UActorComponent* Comp : ComponentList)
	{	
		PhysicsEnabledList.Add(Cast<UStaticMeshComponent>(Comp)->IsSimulatingPhysics());
		CollisionEnabledList.Add(Cast<UStaticMeshComponent>(Comp)->GetCollisionEnabled());
		Cast<UStaticMeshComponent>(Comp)->SetSimulatePhysics(false);
		Cast<UStaticMeshComponent>(Comp)->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//Cast<UStaticMeshComponent>(Comp)->SetWorldTransform(T, false, nullptr, ETeleportType::TeleportPhysics);
	}
	EComponentMobility::Type OriginalMobility = Actor->GetRootComponent()->Mobility;
	Actor->GetRootComponent()->SetMobility(EComponentMobility::Movable);
	Actor->SetActorTransform(T, false, nullptr, ETeleportType::TeleportPhysics);
	Actor->GetRootComponent()->SetMobility(OriginalMobility);
	for (int32 i = 0; i < ComponentList.Num(); i++)
	{
		Cast<UStaticMeshComponent>(ComponentList[i])->SetSimulatePhysics(PhysicsEnabledList[i]);
		Cast<UStaticMeshComponent>(ComponentList[i])->SetCollisionEnabled(CollisionEnabledList[i]);
	}
	
	ALight* Light = Cast<ALight>(Actor);
	if (Light) //Light
	{
		if (OriginalMobility == EComponentMobility::Static || EComponentMobility::Stationary)
			InvalidateEditorLightingCache(Light);
		NotifyModifiedLight(Light);
		return;
	}
	else //other Actor
	{
		if (OriginalMobility == EComponentMobility::Static)
			InvalidateEditorLightingCache(Actor);
		NotifyModifiedActor(Actor);
	}
}

void ABlockingVRManager::SetLocationPIEActor(AActor* Actor, FVector Location, bool Snap, bool UseEditorSnapSize, float SnapSize)
{
	if (!Actor || !IsAllowedClass(Actor)) return;
	if (Snap)
	{
		if (UseEditorSnapSize)
			Location = SnapVector(Location, GEditor->GetGridSize());
		else 
			Location = SnapVector(Location, SnapSize);
	}
	TArray<bool> PhysicsEnabledList;
	TArray<ECollisionEnabled::Type> CollisionEnabledList;
	TArray<UActorComponent*> ComponentList = Actor->GetComponentsByClass(UStaticMeshComponent::StaticClass());
	for (UActorComponent* Comp : ComponentList)
	{
		PhysicsEnabledList.Add(Cast<UStaticMeshComponent>(Comp)->IsSimulatingPhysics());
		CollisionEnabledList.Add(Cast<UStaticMeshComponent>(Comp)->GetCollisionEnabled());
		Cast<UStaticMeshComponent>(Comp)->SetSimulatePhysics(false);
		Cast<UStaticMeshComponent>(Comp)->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	EComponentMobility::Type OriginalMobility = Actor->GetRootComponent()->Mobility;
	Actor->GetRootComponent()->SetMobility(EComponentMobility::Movable);
	Actor->SetActorLocation(Location, false, nullptr, ETeleportType::TeleportPhysics);
	Actor->GetRootComponent()->SetMobility(OriginalMobility);
	for (int32 i = 0; i < ComponentList.Num(); i++)
	{
		Cast<UStaticMeshComponent>(ComponentList[i])->SetSimulatePhysics(PhysicsEnabledList[i]);
		Cast<UStaticMeshComponent>(ComponentList[i])->SetCollisionEnabled(CollisionEnabledList[i]);
	}

	ALight* Light = Cast<ALight>(Actor);
	if (Light)
	{
		if (OriginalMobility == EComponentMobility::Static || EComponentMobility::Stationary)
			InvalidateEditorLightingCache(Light);
		NotifyModifiedLight(Light);
		return;
	}
	else
	{
		if (OriginalMobility == EComponentMobility::Static)
			InvalidateEditorLightingCache(Actor);
		NotifyModifiedActor(Actor);
	}
}

void ABlockingVRManager::SetRotationPIEActor(AActor* Actor, FRotator Rotation, bool Snap, bool UseEditorSnapSize, float SnapSize)
{
	if (!Actor || !IsAllowedClass(Actor)) return;
	if (Snap)
	{
		if (UseEditorSnapSize)
			Rotation = SnapRotator( Rotation, GEditor->GetRotGridSize().Yaw );
		else
			Rotation = SnapRotator(Rotation, SnapSize);
	}
	TArray<bool> PhysicsEnabledList;
	TArray<ECollisionEnabled::Type> CollisionEnabledList;
	TArray<UActorComponent*> ComponentList = Actor->GetComponentsByClass(UStaticMeshComponent::StaticClass());
	for (UActorComponent* Comp : ComponentList)
	{
		PhysicsEnabledList.Add(Cast<UStaticMeshComponent>(Comp)->IsSimulatingPhysics());
		CollisionEnabledList.Add(Cast<UStaticMeshComponent>(Comp)->GetCollisionEnabled());
		Cast<UStaticMeshComponent>(Comp)->SetSimulatePhysics(false);
		Cast<UStaticMeshComponent>(Comp)->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	EComponentMobility::Type OriginalMobility = Actor->GetRootComponent()->Mobility;
	Actor->GetRootComponent()->SetMobility(EComponentMobility::Movable);
	Actor->SetActorRotation(Rotation);
	Actor->GetRootComponent()->SetMobility(OriginalMobility);
	for (int32 i = 0; i < ComponentList.Num(); i++)
	{
		Cast<UStaticMeshComponent>(ComponentList[i])->SetSimulatePhysics(PhysicsEnabledList[i]);
		Cast<UStaticMeshComponent>(ComponentList[i])->SetCollisionEnabled(CollisionEnabledList[i]);
	}

	ALight* Light = Cast<ALight>(Actor);
	if (Light)
	{
		if (OriginalMobility == EComponentMobility::Static || EComponentMobility::Stationary)
			InvalidateEditorLightingCache(Light);
		Light->MarkComponentsRenderStateDirty(); //test
		NotifyModifiedLight(Light);
		return;
	}
	else
	{
		if (OriginalMobility == EComponentMobility::Static)
			InvalidateEditorLightingCache(Actor);
		NotifyModifiedActor(Actor);
	}
}

void ABlockingVRManager::SetScalePIEActor(AActor* Actor, FVector Scale, bool Snap,bool UseEditorSnapSize, float SnapSize)
{
	if (!Actor || !IsAllowedClass(Actor)) return;
	if (Snap)
	{
		if (UseEditorSnapSize)
			Scale = SnapVector(Scale, GEditor->GetScaleGridSize() );
		else Scale = SnapVector(Scale, SnapSize );
	}
	TArray<bool> PhysicsEnabledList;
	TArray<ECollisionEnabled::Type> CollisionEnabledList;
	TArray<UActorComponent*> ComponentList = Actor->GetComponentsByClass(UStaticMeshComponent::StaticClass());
	for (UActorComponent* Comp : ComponentList)
	{
		PhysicsEnabledList.Add(Cast<UStaticMeshComponent>(Comp)->IsSimulatingPhysics());
		CollisionEnabledList.Add(Cast<UStaticMeshComponent>(Comp)->GetCollisionEnabled());
		Cast<UStaticMeshComponent>(Comp)->SetSimulatePhysics(false);
		Cast<UStaticMeshComponent>(Comp)->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	EComponentMobility::Type OriginalMobility = Actor->GetRootComponent()->Mobility;
	Actor->GetRootComponent()->SetMobility(EComponentMobility::Movable);
	Actor->SetActorScale3D(Scale);
	Actor->GetRootComponent()->SetMobility(OriginalMobility);
	for (int32 i = 0; i < ComponentList.Num(); i++)
	{
		Cast<UStaticMeshComponent>(ComponentList[i])->SetSimulatePhysics(PhysicsEnabledList[i]);
		Cast<UStaticMeshComponent>(ComponentList[i])->SetCollisionEnabled(CollisionEnabledList[i]);
	}

	ALight* Light = Cast<ALight>(Actor);
	if (Light)
	{
		if (OriginalMobility == EComponentMobility::Static || EComponentMobility::Stationary)
			InvalidateEditorLightingCache(Light);
		NotifyModifiedLight(Light);
		return;
	}
	else
	{
		if (OriginalMobility == EComponentMobility::Static)
			InvalidateEditorLightingCache(Actor);
		NotifyModifiedActor(Actor);
	}
}

void ABlockingVRManager::DeletePIEActor(AActor* Actor)
{
	if (!Actor || !IsAllowedClass(Actor)) return;
	ALight* Light = Cast<ALight>(Actor);
	if (Light)
	{
		DeletePIELight(Light);
		return;
	}
	//Check to see if this is a new Actor
	bool bIsNewActor = false;
	for (int32 i = 0; i < NewEditorActors.Num(); i++)
	{
		if (NewEditorActors[i] == Actor)
		{
			bIsNewActor = true;
			NewEditorActors.RemoveAt(i); //remove from deferred additions Array;
			Actor->Destroy();
			break;
		}
	} //end for
	if (bIsNewActor == false)
	{
		//try and find the editor version for destruction then destroy the PIE verson
		DeleteEditorActor(Actor);
		Actor->Destroy();
	}
}

ALight* ABlockingVRManager::AddPIELight(FVector Location, EBVRLightType LightType)
{
	ALight* PIELight = nullptr;

	if (LightType == EBVRLightType::VBR_PointLight)
	{
		PIELight = Cast<ALight>(GetWorld()->SpawnActor(APointLight::StaticClass(), &Location));
	}
	else if (LightType == EBVRLightType::VBR_SpotLight)
	{
		AActor* A = GetWorld()->SpawnActor(ASpotLight::StaticClass(), &Location);
		PIELight = Cast<ALight>(A);
	}
	else if (LightType == EBVRLightType::VBR_DirectionalLight)
	{
		AActor* A = GetWorld()->SpawnActor(ADirectionalLight::StaticClass(), &Location);
		PIELight = Cast<ALight>(A);
	}
	if (PIELight)
	{
		//add handle
		ULightHandleBase* pComponent = nullptr;
		if (LightType == EBVRLightType::VBR_PointLight)
			pComponent = NewObject<UPointLightHandleComponent>(PIELight, FName("LightHandleComponent"));
		else if (LightType == EBVRLightType::VBR_SpotLight)
			pComponent = NewObject<USpotLightHandleComponent>(PIELight, FName("LightHandleComponent"));
		else if (LightType == EBVRLightType::VBR_DirectionalLight)
			pComponent = NewObject<UDirectionalLightHandleComponent>(PIELight, FName("LightHandleComponent"));
		
		if (pComponent)
		{
			pComponent->AttachTo(PIELight->GetRootComponent(), NAME_None, EAttachLocation::SnapToTarget, false);
			pComponent->RegisterComponentWithWorld(GetWorld());
			PIELight->SetActorHiddenInGame(false);
			pComponent->SetHiddenInGame(false);
			pComponent->SetVisibility(true);
		}
		PIELight->SetMobility(EComponentMobility::Movable);
		NewEditorLights.Add(PIELight); //add to deffered array
	}
	return PIELight;
}

void ABlockingVRManager::SetPIELightColor(ALight* Light, FLinearColor Color)
{
	if (!Light) return;
	if (Light->GetLightColor().Equals(Color)) return;
	
	EComponentMobility::Type OriginalMobility = Light->GetRootComponent()->Mobility;
	Light->SetMobility(EComponentMobility::Stationary);
	Light->SetLightColor(Color);
	Light->SetMobility(OriginalMobility);
	if (OriginalMobility == EComponentMobility::Static)
		InvalidateEditorLightingCache(Light);
	NotifyModifiedLight(Light);
}

void ABlockingVRManager::SetPIELightIntensity(ALight* Light, float Intensity)
{
	if (!Light) return;
	EComponentMobility::Type OriginalMobility = Light->GetRootComponent()->Mobility;
	Light->SetMobility(EComponentMobility::Stationary);
	Light->GetLightComponent()->SetIntensity(Intensity);
	Light->SetMobility(OriginalMobility);
	if (OriginalMobility == EComponentMobility::Static)
		InvalidateEditorLightingCache(Light);
	NotifyModifiedLight(Light);
}

void ABlockingVRManager::SetPIELightSquareFallOff(ALight* Light, bool bSqrFalloff)
{
	if (!Light) return;
	//USpotLightComponent is a subclass of UPointLightComponent!
	UPointLightComponent* PointLightComponent = Cast<UPointLightComponent>(Light->GetLightComponent());
	if (PointLightComponent)
	{
		EComponentMobility::Type OriginalMobility = Light->GetRootComponent()->Mobility;
		Light->SetMobility(EComponentMobility::Movable);
		PointLightComponent->bUseInverseSquaredFalloff = bSqrFalloff;
		Light->SetMobility(OriginalMobility);
		if (OriginalMobility == EComponentMobility::Static || EComponentMobility::Stationary)
			InvalidateEditorLightingCache(Light);
		NotifyModifiedLight(Light);
	}
}

void ABlockingVRManager::SetPIELightStaticShadows(ALight* Light, bool bStaticShadows)
{
	Light->GetLightComponent()->CastStaticShadows = bStaticShadows;
	if (Light->GetRootComponent()->Mobility == EComponentMobility::Static || EComponentMobility::Stationary)
		InvalidateEditorLightingCache(Light);

	NotifyModifiedLight(Light);
}

void ABlockingVRManager::SetPIELightDynamicShadows(ALight* Light, bool bDynamicShadows)
{
	Light->GetLightComponent()->CastDynamicShadows = bDynamicShadows;
	Light->MarkComponentsRenderStateDirty(); //test
		NotifyModifiedLight(Light);
}

void ABlockingVRManager::SetPIELightTranslucentLighting(ALight* Light, bool bTranslucentLighting)
{
	if (!Light) return;
	if (Light->GetLightComponent()->bAffectTranslucentLighting != bTranslucentLighting)
	{
		Light->GetLightComponent()->bAffectTranslucentLighting = bTranslucentLighting;
		Light->MarkComponentsRenderStateDirty();
		if (Light->GetRootComponent()->Mobility == EComponentMobility::Static)
			InvalidateEditorLightingCache(Light);
		NotifyModifiedLight(Light);
	}
}

void  ABlockingVRManager::SetPIEPointLightRadius(APointLight* PointLight, float Radius)
{
	if (!PointLight) return;
	EComponentMobility::Type OriginalMobility = PointLight->GetRootComponent()->Mobility;
	PointLight->SetMobility(EComponentMobility::Movable);
	PointLight->SetRadius(Radius);
	PointLight->SetMobility(OriginalMobility);
	if (OriginalMobility == EComponentMobility::Static || EComponentMobility::Stationary)
		InvalidateEditorLightingCache(PointLight); 
	NotifyModifiedLight(PointLight);
}

float  ABlockingVRManager::GetPIEPointLightRadius(APointLight* PointLight)
{
	if (!PointLight) return -1;
	return Cast<UPointLightComponent>(PointLight->GetLightComponent())->AttenuationRadius;
}

float  ABlockingVRManager::GetPIESpotLightRadius(ASpotLight* SpotLight)
{
	if (!SpotLight) return -1;
	return Cast<USpotLightComponent>(SpotLight->GetLightComponent())->AttenuationRadius;
}

void  ABlockingVRManager::SetPIESpotLightRadius(ASpotLight* SpotLight, float Radius)
{
	if (!SpotLight) return;
	EComponentMobility::Type OriginalMobility = SpotLight->GetRootComponent()->Mobility;
	SpotLight->SetMobility(EComponentMobility::Movable);
	USpotLightComponent* SpotLightComponent = Cast<USpotLightComponent>(SpotLight->GetLightComponent());
	SpotLightComponent->AttenuationRadius = Radius;
	SpotLight->SetMobility(OriginalMobility);
	if (OriginalMobility == EComponentMobility::Static || EComponentMobility::Stationary)
		InvalidateEditorLightingCache(SpotLight);
		
	NotifyModifiedLight(SpotLight);
}

void  ABlockingVRManager::SetPIESpotLightOuterCone(ASpotLight* SpotLight, float AngleD)
{
	if (!SpotLight) return;
	EComponentMobility::Type OriginalMobility = SpotLight->GetRootComponent()->Mobility;
	SpotLight->SetMobility(EComponentMobility::Movable);
	USpotLightComponent* SpotLightComponent = Cast<USpotLightComponent>(SpotLight->GetLightComponent());
	if (AngleD < SpotLightComponent->InnerConeAngle) SpotLightComponent->SetInnerConeAngle(AngleD);
	SpotLightComponent->SetOuterConeAngle(AngleD);
	SpotLight->SetMobility(OriginalMobility);
	if (OriginalMobility == EComponentMobility::Static || EComponentMobility::Stationary)
		InvalidateEditorLightingCache(SpotLight);
	NotifyModifiedLight(SpotLight);
	
}

void  ABlockingVRManager::SetPIESpotLightInnerCone(ASpotLight* SpotLight, float AngleD)
{
	if (!SpotLight) return;
	EComponentMobility::Type OriginalMobility = SpotLight->GetRootComponent()->Mobility;
	SpotLight->SetMobility(EComponentMobility::Movable);
	USpotLightComponent* SpotLightComponent = Cast<USpotLightComponent>(SpotLight->GetLightComponent());
	if (AngleD > SpotLightComponent->OuterConeAngle) SpotLightComponent->SetOuterConeAngle(AngleD);
	SpotLightComponent->SetInnerConeAngle(AngleD);
	SpotLight->SetMobility(OriginalMobility);
	if (OriginalMobility == EComponentMobility::Static || EComponentMobility::Stationary)
		InvalidateEditorLightingCache(SpotLight);
	NotifyModifiedLight(SpotLight);
}

void ABlockingVRManager::SetPIELightHandleVisibility(ALight* Light, bool bVisible)
{
	if (!Light) return;
	TArray<UActorComponent*> ComponentList = Light->GetComponents();
	for (UActorComponent* Component : ComponentList)
	{ 
		ULightHandleBase* LightHandle = Cast<ULightHandleBase>(Component);
		if (LightHandle)
		{
			LightHandle->bShouldRender = bVisible;
			LightHandle->SetVisibility(bVisible);
			LightHandle->SetCollisionEnabled((ECollisionEnabled::Type)bVisible);
			break;
		}
	}
}

void ABlockingVRManager::HideAllPIELightHandles()
{
	for (TActorIterator<ALight> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		SetPIELightHandleVisibility(*ActorItr, false);
	}
}

void ABlockingVRManager::ShowAllPIELightHandles()
{
	for (TActorIterator<ALight> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		SetPIELightHandleVisibility(*ActorItr, true);
	}
	
}

void ABlockingVRManager::SetPIELightDebugMeshVisibility(ALight* Light, bool bVisible)
{
	if (!Light) return;
	TArray<UActorComponent*> ComponentList = Light->GetComponents();
	for (UActorComponent* Component : ComponentList)
	{
		if (Light->GetLightComponent()->GetLightType() == ELightComponentType::LightType_Directional)
		{
			ADirectionalLight* DirLight = Cast<ADirectionalLight>(Light);
			
			if (bVisible)
			{
				DirLight->GetArrowComponent()->SetVisibility(true);
				DirLight->GetArrowComponent()->SetHiddenInGame(false);
			}
			else
			{
				DirLight->GetArrowComponent()->SetVisibility(false);
				DirLight->GetArrowComponent()->SetHiddenInGame(true);
			}
			break;
		}
		
		if (Cast<ULightHandleBase>(Component))
		{
			if (bVisible)
			{
				Cast<ULightHandleBase>(Component)->bDrawDebugMeshes = true;
			}
			else
			{
				Cast<ULightHandleBase>(Component)->bDrawDebugMeshes = false;
			}
			break;
		}
	}

}

void ABlockingVRManager::HideAllPIELightDebugMeshes()
{
	for (TActorIterator<ALight> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		SetPIELightDebugMeshVisibility(*ActorItr, false);
	}
}

void ABlockingVRManager::ShowAllPIELightDebugMeshes()
{
	for (TActorIterator<ALight> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		SetPIELightDebugMeshVisibility(*ActorItr, true);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
void ABlockingVRManager::AddEditorActor(FTransform T, AActor* Actor) //private
{
	if (!Actor) return;

	if (GEditor && GEditor->GetEditorWorldContext().World() && GEditor->GetEditorWorldContext().World()->GetCurrentLevel())
	{
		AActor* EditorActor = GEditor->AddActor(GEditor->GetEditorWorldContext().World()->GetCurrentLevel(), Actor->GetClass(), T);
		if (EditorActor && Actor->GetClass() == AStaticMeshActor::StaticClass())
		{
			EComponentMobility::Type OriginalMobility = Actor->GetRootComponent()->Mobility;
			EditorActor->GetRootComponent()->SetMobility(EComponentMobility::Movable);
			Cast<AStaticMeshActor>(EditorActor)->GetStaticMeshComponent()->SetStaticMesh(Cast<AStaticMeshActor>(Actor)->GetStaticMeshComponent()->StaticMesh);
			EditorActor->SetActorTransform(T);
			EditorActor->GetRootComponent()->SetMobility(OriginalMobility);
			//ensure materials are the same
			TArray<UMaterialInterface*> MeshMaterials = Cast<AStaticMeshActor>(Actor)->GetStaticMeshComponent()->GetMaterials();
			for (int32 i = 0; i < MeshMaterials.Num(); i++)
			{
				Cast<AStaticMeshActor>(EditorActor)->GetStaticMeshComponent()->SetMaterial(i, MeshMaterials[i]);
			}
		}
	}
}

void ABlockingVRManager::DeleteEditorActor(AActor* Actor) //private
{
	if (!Actor) return;
	if (GEditor->ObjectsThatExistInEditorWorld.Get(Actor))
	{
		const bool bExactClass = false;
		//TODO CHECK ALL SUBLEVELS FOR ACTOR
		AActor* EditorActor = FindObject<AActor>(GEditor->GetEditorWorldContext().World()->GetCurrentLevel(), *Actor->GetFName().ToString(), bExactClass);
		if (EditorActor)
		{
			DeletedEditorActors.Add(EditorActor);
		}
	}
}

ALight* ABlockingVRManager::AddEditorLight(FTransform T, EBVRLightType LightType) //private
{
	ALight* Result = nullptr;

	if (GEditor && GEditor->GetEditorWorldContext().World() && GEditor->GetEditorWorldContext().World()->GetCurrentLevel())
	{
		AActor* EditorLight = nullptr;

		if (LightType == EBVRLightType::VBR_PointLight)
		{
			EditorLight = GEditor->AddActor(GEditor->GetEditorWorldContext().World()->GetCurrentLevel(), APointLight::StaticClass(), T);
		}
		else if (LightType == EBVRLightType::VBR_SpotLight)
		{
			EditorLight = GEditor->AddActor(GEditor->GetEditorWorldContext().World()->GetCurrentLevel(), ASpotLight::StaticClass(), T);
		}
		else if (LightType == EBVRLightType::VBR_DirectionalLight)
		{
			EditorLight = GEditor->AddActor(GEditor->GetEditorWorldContext().World()->GetCurrentLevel(), ADirectionalLight::StaticClass(), T);
		}
		if (EditorLight)
		{
			//EditorLight->MarkComponentsRenderStateDirty();
			Result = Cast<ALight>(EditorLight);
		}
	} //end if geditor

	return Result;

}

void ABlockingVRManager::DeletePIELight(ALight* Light) //private
{
	//Check to see if this is a new Light
	bool bIsNewLight = false;
	for (int32 i = 0; i < NewEditorLights.Num(); i++)
	{
		if (NewEditorLights[i] == Light)
		{
			bIsNewLight = true;
			NewEditorLights.RemoveAt(i); //remove from deferred additions Array;
			break;
		}
	} //end for
	if (bIsNewLight == false)
	{
		if (Light->GetRootComponent()->Mobility == EComponentMobility::Static)
			InvalidateEditorLightingCache(Light);
		//try and find the editor version for destruction then destroy the PIE verson
		DeleteEditorActor(Light);
	}
	Light->Destroy();
}

void ABlockingVRManager::PastePIELight(ALight* Light, FVector Location) //private
{
	if (Light->LightComponent->GetLightType() == ELightComponentType::LightType_Point)
	{
		PastePIEPointLight(Cast<APointLight>(Light), Location);
	}
	else if (Light->LightComponent->GetLightType() == ELightComponentType::LightType_Spot)
	{
		PastePIESpotLight(Cast<ASpotLight>(Light), Location);
	}
	else if (Light->LightComponent->GetLightType() == ELightComponentType::LightType_Directional)
	{
		PastePIEDirectionalLight(Cast<ADirectionalLight>(Light), Location);
	}
	/*else if (Cast to a skylight)
	{

	}*/
}

void ABlockingVRManager::SetCommonEditorLightProperties(ALight* EditorLight, const ALight* PIELight) //private
{
	EditorLight->SetActorTransform(PIELight->GetTransform());
	EditorLight->SetLightColor(PIELight->GetLightColor());
	EditorLight->GetLightComponent()->SetIntensity(PIELight->GetLightComponent()->Intensity);
	EditorLight->GetLightComponent()->CastStaticShadows = PIELight->GetLightComponent()->CastStaticShadows;
	EditorLight->GetLightComponent()->CastDynamicShadows = PIELight->GetLightComponent()->CastDynamicShadows;
	EditorLight->GetLightComponent()->bAffectTranslucentLighting = PIELight->GetLightComponent()->bAffectTranslucentLighting;
}

void ABlockingVRManager::PastePIEPointLight(APointLight* PointLight, FVector Location) //private
{
	if (!PointLight) return;
	APointLight* PIELight = Cast<APointLight>(AddPIELight(Location, EBVRLightType::VBR_PointLight));
	if (PIELight)
	{
		PIELight->SetActorRotation(PointLight->GetActorRotation()); //rotation
		PIELight->SetLightColor(PointLight->GetLightColor()); //color
		PIELight->GetLightComponent()->SetIntensity(PointLight->GetLightComponent()->Intensity); //intensity
		PIELight->SetRadius(Cast<UPointLightComponent>(PointLight->GetLightComponent())->AttenuationRadius); //radius
		PIELight->GetLightComponent()->SetIESTexture(PointLight->GetLightComponent()->IESTexture); //IES
		PIELight->GetLightComponent()->bUseIESBrightness = PointLight->GetLightComponent()->bUseIESBrightness;
		PIELight->GetLightComponent()->IESBrightnessScale = PointLight->GetLightComponent()->IESBrightnessScale;
	}
}

void ABlockingVRManager::PastePIESpotLight(ASpotLight* SpotLight, FVector Location) //private
{
	if (!SpotLight) return;
	ASpotLight* PIELight = Cast<ASpotLight>(AddPIELight(Location, EBVRLightType::VBR_SpotLight));
	if (PIELight)
	{
		PIELight->SetActorRotation(SpotLight->GetActorRotation()); //rotation
		PIELight->SetLightColor(SpotLight->GetLightColor()); //color
		PIELight->GetLightComponent()->SetIntensity(SpotLight->GetLightComponent()->Intensity); //intensity

		float radius = Cast<USpotLightComponent>(SpotLight->GetLightComponent())->AttenuationRadius; //radius
		Cast<USpotLightComponent>(PIELight->GetLightComponent())->AttenuationRadius = radius;

		Cast<USpotLightComponent>(PIELight->GetLightComponent())->SetInnerConeAngle(
			Cast<USpotLightComponent>(SpotLight->GetLightComponent())->InnerConeAngle); //inner cone angle
		Cast<USpotLightComponent>(PIELight->GetLightComponent())->SetOuterConeAngle(
			Cast<USpotLightComponent>(SpotLight->GetLightComponent())->OuterConeAngle); //outer cone angle
		PIELight->GetLightComponent()->SetIESTexture(SpotLight->GetLightComponent()->IESTexture); //IES
		PIELight->GetLightComponent()->bUseIESBrightness = SpotLight->GetLightComponent()->bUseIESBrightness;
		PIELight->GetLightComponent()->IESBrightnessScale = SpotLight->GetLightComponent()->IESBrightnessScale;
	}

}

void ABlockingVRManager::PastePIEDirectionalLight(ADirectionalLight* DirectionalLight, FVector Location) //private
{
	if (!DirectionalLight) return;
	ADirectionalLight* PIELight = Cast<ADirectionalLight>(AddPIELight(Location, EBVRLightType::VBR_DirectionalLight));
	if (PIELight)
	{
		PIELight->SetActorRotation(DirectionalLight->GetActorRotation()); //rotation
		PIELight->SetLightColor(DirectionalLight->GetLightColor()); //color
		PIELight->GetLightComponent()->SetIntensity(DirectionalLight->GetLightComponent()->Intensity); //intensity

	}
}

void ABlockingVRManager::InvalidateEditorLightingCache(AActor* PIEActor) //private
{
	PIEActor->InvalidateLightingCache();
	if (GEditor->ObjectsThatExistInEditorWorld.Get(PIEActor))
	{
		const bool bExactClass = false;
		AActor* EditorActor = FindObject<AActor>(GEditor->GetEditorWorldContext().World()->GetCurrentLevel(), *PIEActor->GetFName().ToString(), bExactClass);
		if (EditorActor)
		{
			EditorActor->InvalidateLightingCache();
		}
	}
}

void ABlockingVRManager::NotifyModifiedLight(ALight* Light) //private
{
	//check to see if this is a new light for the editor
	//if not add to ModiefiedEditorlights.
	if (GEditor->ObjectsThatExistInEditorWorld.Get(Light))
	{
		const bool bExactClass = false;
		//TODO CHECK ALL SUBLEVELS FOR ACTOR
		ALight* EditorLight = FindObject<ALight>(GEditor->GetEditorWorldContext().World()->GetCurrentLevel(), *Light->GetFName().ToString(), bExactClass);
		if (EditorLight)
		{
			bool bAllreadyInList = false;
			for (int i = 0; i < ModifiedEditorLights.Num(); i++)
			{
				if (ModifiedEditorLights[i] == Light)
				{
					bAllreadyInList = true;
					break;
				}
			}
			if (!bAllreadyInList) ModifiedEditorLights.Add(Light);
		}
	}
}

void ABlockingVRManager::NotifyModifiedActor(AActor* Actor) //private
{
	//check to see if this is a new actor for the editor
	//if not add to ModiefiedEditorActors.
	if (GEditor->ObjectsThatExistInEditorWorld.Get(Actor))
	{
		
		const bool bExactClass = false;
		//TODO CHECK ALL SUBLEVELS FOR ACTOR
		AActor* EditorActor = FindObject<AActor>(GEditor->GetEditorWorldContext().World()->GetCurrentLevel(), *Actor->GetFName().ToString(), bExactClass);
		if (EditorActor)
		{
			bool bAllreadyInList = false;
			for (int i = 0; i < ModifiedEditorActors.Num(); i++)
			{
				if (ModifiedEditorActors[i] == Actor)
				{
					bAllreadyInList = true;
					break;
				}
			}
			if (!bAllreadyInList) ModifiedEditorActors.Add(Actor);
		}
	}
}

FVector ABlockingVRManager::SnapVector(FVector V, float SnapValue) //private
{
	V = V.GridSnap(SnapValue); 
	return V; 
}

FRotator ABlockingVRManager::SnapRotator(FRotator R, float SnapValue) //private
{
	R = R.GridSnap(FRotator(SnapValue, SnapValue, SnapValue));
	return R;
}

bool ABlockingVRManager::IsAllowedClass(AActor* Actor)
{
	if (Actor->IsA(ASkyLight::StaticClass()) || Actor->IsA(ABlockingVolume::StaticClass()) || Actor->IsA(ABrush::StaticClass()))
		return false;
	else return true;
	//return IsAllowedClass(Actor->GetClass());
}

bool ABlockingVRManager::IsAllowedClass(TSubclassOf<class AActor> ClassIN) //TODO: Need Class version of isa()!?!
{
	if (ClassIN == ASkyLight::StaticClass() || ClassIN == ABlockingVolume::StaticClass() || ClassIN == ABrush::StaticClass() )
		return false;
	else return true;
}

#endif