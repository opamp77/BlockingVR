// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#if WITH_EDITORONLY_DATA

#include "BlockingVRPrivatePCH.h"
#include "BlockingVRManager.h"
#include "LightHandleBase.h"
#include "PointLightHandleComponent.h"
#include "SpotLightHandleComponent.h"
#include "DirectionalLightHandleComponent.h"
//#include "SkyLightHandleComponent.h"
#include "ParticleHandleComponent.h"

ABlockingVRManager::ABlockingVRManager(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{	
	USceneComponent* comp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(comp);
}

void ABlockingVRManager::GetCollectionActorClasses(TArray< TSubclassOf<AActor> > &ActorClassesArray)
{
	FCollectionManagerModule& CollectionManagerModule = FCollectionManagerModule::GetModule();
	ICollectionManager& CollectionManager = CollectionManagerModule.Get();

	TArray<FName> ObjectPaths;

	CollectionManager.GetObjectsInCollection(FName("BlockingVRCollection"), ECollectionShareType::CST_Local, ObjectPaths);

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	TArray<FAssetData> AssetData;
	FARFilter Filter;
	Filter.ObjectPaths = ObjectPaths;
	AssetRegistryModule.Get().GetAssets(Filter, AssetData);

	for (FAssetData Data : AssetData)
	{
		UObject* Object = Data.GetAsset();

		if (Data.GetClass()->IsChildOf(UBlueprint::StaticClass()))
		{
			UBlueprint* BluePrint = Cast<UBlueprint>(Object);
			if (BluePrint)
			{
				UClass* GeneratedClass = BluePrint->GeneratedClass;
				TSubclassOf<AActor> ActorClass = GeneratedClass;
				if (ActorClass)
				{
						ActorClassesArray.Add(ActorClass);
				}
			}
		}
		else if (Data.GetClass()->IsChildOf(AActor::StaticClass()) )
		{
			TSubclassOf<AActor> ActorClass = Object->GetClass();
			ActorClassesArray.Add(ActorClass);
		}
	}
}

void ABlockingVRManager::GetCollectionStaticMeshes(TArray<UStaticMesh*> &StaticMeshReferenceArray)
{
	FCollectionManagerModule& CollectionManagerModule = FCollectionManagerModule::GetModule();
	ICollectionManager& CollectionManager = CollectionManagerModule.Get();

	TArray<FName> ObjectPaths;

	CollectionManager.GetObjectsInCollection(FName("BlockingVRCollection"), ECollectionShareType::CST_Local, ObjectPaths);

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	TArray<FAssetData> AssetData;
	FARFilter Filter;
	Filter.ObjectPaths = ObjectPaths;
	AssetRegistryModule.Get().GetAssets(Filter, AssetData);

	for (FAssetData Data : AssetData)
	{
		UObject* Object = Data.GetAsset();

		if (Data.GetClass()->IsChildOf(UStaticMesh::StaticClass()))
		{
			UStaticMesh* StaticMesh = Cast<UStaticMesh>(Data.GetAsset());
			if (StaticMesh)
			{
				StaticMeshReferenceArray.Add(StaticMesh);
			}
		}
	}
}

void ABlockingVRManager::GetCollectionParticles(TArray<UParticleSystem*> &ParticleSystemReferenceArray)
{
	FCollectionManagerModule& CollectionManagerModule = FCollectionManagerModule::GetModule();
	ICollectionManager& CollectionManager = CollectionManagerModule.Get();

	TArray<FName> ObjectPaths;

	CollectionManager.GetObjectsInCollection(FName("BlockingVRCollection"), ECollectionShareType::CST_Local, ObjectPaths);

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	TArray<FAssetData> AssetData;
	FARFilter Filter;
	Filter.ObjectPaths = ObjectPaths;
	AssetRegistryModule.Get().GetAssets(Filter, AssetData);

	for (FAssetData Data : AssetData)
	{
		UObject* Object = Data.GetAsset();

		if (Data.GetClass()->IsChildOf(UParticleSystem::StaticClass()))
		{
			UParticleSystem* ParticleSystem = Cast<UParticleSystem>(Data.GetAsset());
			if (ParticleSystem)
			{
				ParticleSystemReferenceArray.Add(ParticleSystem);
			}
		}
	}
}

void ABlockingVRManager::GetCollectionSkeletalMeshes(TArray<USkeletalMesh*> &SkeletalMeshReferenceArray)
{
	FCollectionManagerModule& CollectionManagerModule = FCollectionManagerModule::GetModule();
	ICollectionManager& CollectionManager = CollectionManagerModule.Get();

	TArray<FName> ObjectPaths;

	CollectionManager.GetObjectsInCollection(FName("BlockingVRCollection"), ECollectionShareType::CST_Local, ObjectPaths);

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	TArray<FAssetData> AssetData;
	FARFilter Filter;
	Filter.ObjectPaths = ObjectPaths;
	AssetRegistryModule.Get().GetAssets(Filter, AssetData);

	for (FAssetData Data : AssetData)
	{
		UObject* Object = Data.GetAsset();

		if (Data.GetClass()->IsChildOf(USkeletalMesh::StaticClass()))
		{
			USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(Data.GetAsset());
			if (SkeletalMesh)
			{
				SkeletalMeshReferenceArray.Add(SkeletalMesh);
			}
		}
	}
}

void ABlockingVRManager::BeginPlay(void)
{
	Super::BeginPlay();
	//Attach PointLight Handles
	for (TActorIterator<APointLight> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
	{
		AttachHandle(*ActorItr,EBVRHandleType::BVR_PointLightHandle);
	}
	//Attach SpotLight Handles
	for (TActorIterator<ASpotLight> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
	{
		AttachHandle(*ActorItr, EBVRHandleType::BVR_SpotLightHandle);
	}
	//Attach DirectionalLight Handles
	for (TActorIterator<ADirectionalLight> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
	{
		AttachHandle(*ActorItr, EBVRHandleType::BVR_DirectionalLightHandle);
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
	//Attach Particle Handles
	for (TActorIterator<AEmitter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AttachHandle(*ActorItr, EBVRHandleType::BVR_ParticleHandle);
	}
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
			ThumbnailTools::ConditionallyLoadThumbnailsFromPackage(PackageFilename, ObjectFullNames, ThumbnailMap);

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
			} //end if thumbnail
		} //end if package
			//Create New Thumbnail
		else
		{
			FObjectThumbnail* NewThumbNail = ThumbnailTools::GenerateThumbnailForObjectToSaveToDisk(AssetData[0].GetAsset());
			if (NewThumbNail)
			{
					TArray<uint8> Data = NewThumbNail->GetUncompressedImageData();
				UTexture2D* Texture = nullptr;
				Texture = UTexture2D::CreateTransient(NewThumbNail->GetImageWidth(), NewThumbNail->GetImageHeight());
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
		return nullptr;
	}
	else return nullptr;
}

void ABlockingVRManager::ApplyDeferredChanges(void)
{
	//Do deleted Editor Actors(Including lights and particles)
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
		if (!PIELight->IsValidLowLevel()) UE_LOG(BlockingVR_Log, Error, TEXT("BLockingVRManager::ApplyDeferredChanges() A PIELight within NewEditorLights is no Longer valid!!!! 320"));
		if ((uint8)PIELight->GetLightComponent()->GetLightType() == (uint8)EBVRLightType::BVR_PointLight)
		{
			//add the editor Light
			APointLight* EditorPointLight = Cast<APointLight>(AddEditorLight(PIELight->GetTransform(), EBVRLightType::BVR_PointLight));
			if (EditorPointLight)
			{
				//needs to be set to movable temporarily to be able to apply certian properties such as radius/cone angles
				EditorPointLight->SetMobility(EComponentMobility::Movable);
				CopyCommonLightProperties(EditorPointLight, PIELight); //common properties
				EditorPointLight->SetRadius(Cast<UPointLightComponent>(PIELight->GetLightComponent())->AttenuationRadius); //radius
				EditorPointLight->GetLightComponent()->SetIESTexture(PIELight->GetLightComponent()->IESTexture); //IES
				EditorPointLight->GetLightComponent()->bUseIESBrightness = PIELight->GetLightComponent()->bUseIESBrightness;
				EditorPointLight->GetLightComponent()->IESBrightnessScale = PIELight->GetLightComponent()->IESBrightnessScale;
				EditorPointLight->SetMobility(EComponentMobility::Stationary); //all new lights will default to Stationary
			}
		}
		//SpotLight
		else if ((uint8)PIELight->GetLightComponent()->GetLightType() == (uint8)EBVRLightType::BVR_SpotLight)
		{
			ASpotLight* EditorSpotLight = Cast<ASpotLight>(AddEditorLight(PIELight->GetTransform(), EBVRLightType::BVR_SpotLight));
			if (EditorSpotLight)
			{
				//needs to be set to movable temporarily to be able to apply certain properties such as radius/cone angles
				EditorSpotLight->SetMobility(EComponentMobility::Movable);
				CopyCommonLightProperties(EditorSpotLight, PIELight); //common Properties
				
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
		else if ((uint8)PIELight->GetLightComponent()->GetLightType() == (uint8)EBVRLightType::BVR_DirectionalLight)
		{
			ADirectionalLight* EditorDirectionalLight = Cast<ADirectionalLight>(AddEditorLight(PIELight->GetTransform(), EBVRLightType::BVR_DirectionalLight));
			if (EditorDirectionalLight)
			{
				CopyCommonLightProperties(EditorDirectionalLight, PIELight);
			}
		}
	}
	//Do to be Modified Editor Lights
	for (const ALight* PIELight : ModifiedEditorLights)
	{
		if (!PIELight->IsValidLowLevel()) UE_LOG(BlockingVR_Log, Error, TEXT("BLockingVRManager::ApplyDeferredChanges() A PIELight within ModifiedEditorLights is no Longer valid!!!! 373"));

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
				CopyCommonLightProperties(EditorLight, PIELight);
				//pointlights
				if (!PIELight->IsValidLowLevel()) UE_LOG(BlockingVR_Log, Error, TEXT("BLockingVRManager::ApplyDeferredChanges() PIELight No Loger Valid!!!! 389"));
				if ((uint8)PIELight->GetLightComponent()->GetLightType() ==(uint8)EBVRLightType::BVR_PointLight)
				{
					APointLight* EditorPointLight = Cast<APointLight>(EditorLight);
					const APointLight* PIEPointLight = Cast<APointLight>(PIELight);
					UPointLightComponent* PIEPointLightComponent = Cast<UPointLightComponent>(PIEPointLight->GetLightComponent());
					UPointLightComponent* EditorPointLightComponent = Cast<UPointLightComponent>(EditorPointLight->GetLightComponent());
					EditorPointLightComponent->bUseInverseSquaredFalloff = PIEPointLightComponent->bUseInverseSquaredFalloff;
					EditorPointLight->SetRadius(PIEPointLightComponent->AttenuationRadius);
				
				}
				//spotlights
				else if ((uint8)PIELight->GetLightComponent()->GetLightType() == (uint8)EBVRLightType::BVR_SpotLight)
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
				else if ((uint8)PIELight->GetLightComponent()->GetLightType() == (uint8)EBVRLightType::BVR_DirectionalLight)
				{
					//COVERED BY CopyCommonLightProperties();
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
		if (!PIEActor->IsValidLowLevel()) UE_LOG(BlockingVR_Log, Error, TEXT("BLockingVRManager::ApplyDeferredChanges() PIEActor No Loger Valid!!!! 429"));

		AddEditorActor(PIEActor->GetTransform(), PIEActor);
	}
	//Do to be modified Editor Actors(including particles)
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
				EditorActor->MarkComponentsRenderStateDirty();
			}
		}
	}
	//Do NewEditorParticles
	for (AEmitter* PIEEmitter : NewEditorParticles)
	{
		AddEditorParticle(PIEEmitter->GetTransform(), PIEEmitter);
	}
	DeletedEditorActors.Empty();
	NewEditorActors.Empty();
	NewEditorLights.Empty();
	ModifiedEditorActors.Empty();
	ModifiedEditorLights.Empty();
	NewEditorParticles.Empty();
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

AEmitter* ABlockingVRManager::AddPIEParticle(UParticleSystem* Template, FTransform T)
{
	if (!Template) return nullptr;

	AEmitter* PIEEmitter = nullptr;
	AActor* PIEActor = nullptr;
	FVector L = T.GetLocation();

	PIEActor = GetWorld()->SpawnActor(AEmitter::StaticClass(), &L);
	if (PIEActor) PIEEmitter = Cast<AEmitter>(PIEActor);

	if (PIEEmitter)
	{
		AttachHandle(PIEEmitter, EBVRHandleType::BVR_ParticleHandle);
		PIEEmitter->SetActorTransform(T, false, nullptr, ETeleportType::TeleportPhysics);
		PIEEmitter->GetParticleSystemComponent()->SetTemplate(Template);
		//Currently the editor world additions are deffered until ApllyDeferredChanges()
		NewEditorParticles.Add(PIEEmitter);
	}
	return PIEEmitter;
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
	//Particle Emitter Actor
	else if (Actor->IsA(AEmitter::StaticClass()))
	{
		PastePIEParticle(Cast<AEmitter>(Actor), Location);
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
		if ( (OriginalMobility == EComponentMobility::Static || EComponentMobility::Stationary) && !Light->IsA(ADirectionalLight::StaticClass()) )
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

void ABlockingVRManager::SetRotationPIEActor(AActor* Actor, FRotator Rotation, bool Relative, bool Snap, bool UseEditorSnapSize, float SnapSize)
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
	if (Relative)
		Actor->SetActorRotation(Rotation);
	else
		Actor->SetActorRelativeRotation(Rotation);

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
	AEmitter* Emitter = Cast<AEmitter>(Actor);
	if (Emitter)
	{
		DeletePIEEmitter(Emitter);
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
		for (int32 i = 0; i < ModifiedEditorActors.Num(); i++) //remove from modiefied list if in there
		{
			if (ModifiedEditorActors[i] == Actor) //fixes previous crash bug
			{
				ModifiedEditorActors.RemoveAt(i);
				break;
			}
		}
		//try and find the editor version for destruction then destroy the PIE verson
		DeleteEditorActor(Actor);
		Actor->Destroy();
	}
}

ALight* ABlockingVRManager::AddPIELight(FVector Location, EBVRLightType LightType)
{
	ALight* PIELight = nullptr;

	if (LightType == EBVRLightType::BVR_PointLight)
	{
		PIELight = Cast<ALight>(GetWorld()->SpawnActor(APointLight::StaticClass(), &Location));
	}
	else if (LightType == EBVRLightType::BVR_SpotLight)
	{
		AActor* A = GetWorld()->SpawnActor(ASpotLight::StaticClass(), &Location);
		PIELight = Cast<ALight>(A);
	}
	else if (LightType == EBVRLightType::BVR_DirectionalLight)
	{
		AActor* A = GetWorld()->SpawnActor(ADirectionalLight::StaticClass(), &Location);
		PIELight = Cast<ALight>(A);
	}
	if (PIELight)
	{
		//add handle
		if (LightType == EBVRLightType::BVR_PointLight)
			AttachHandle(PIELight, EBVRHandleType::BVR_PointLightHandle);
		else if (LightType == EBVRLightType::BVR_SpotLight)
			AttachHandle(PIELight, EBVRHandleType::BVR_SpotLightHandle);
		else if (LightType == EBVRLightType::BVR_DirectionalLight)
			AttachHandle(PIELight, EBVRHandleType::BVR_DirectionalLightHandle);

		
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
		if (PointLightComponent->bUseInverseSquaredFalloff != bSqrFalloff)
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
}

void ABlockingVRManager::SetPIELightStaticShadows(ALight* Light, bool bStaticShadows)
{
	if (!Light) return;
	if (Light->GetLightComponent()->CastStaticShadows != bStaticShadows)
	{
		Light->GetLightComponent()->CastStaticShadows = bStaticShadows;
		if (Light->GetRootComponent()->Mobility == EComponentMobility::Static || EComponentMobility::Stationary)
			InvalidateEditorLightingCache(Light);

		NotifyModifiedLight(Light);
	}
}

void ABlockingVRManager::SetPIELightDynamicShadows(ALight* Light, bool bDynamicShadows)
{
	if (!Light) return;
	if (Light->GetLightComponent()->CastDynamicShadows != bDynamicShadows)
	{
		Light->GetLightComponent()->CastDynamicShadows = bDynamicShadows;
		Light->MarkComponentsRenderStateDirty();
		NotifyModifiedLight(Light);
	}
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

void ABlockingVRManager::ShowAllPIEHandles(void)
{
	ShowAllPIELightHandles();
	ShowAllPIEParticleHandles();
}

void ABlockingVRManager::HideAllPIEHandles(void)
{
	HideAllPIELightHandles();
	HideAllPIEParticleHandles();
}

void ABlockingVRManager::HideAllPIELightHandles(void)
{
	for (TActorIterator<ALight> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		SetPIELightHandleVisibility(*ActorItr, false);
	}
}

void ABlockingVRManager::ShowAllPIELightHandles(void)
{
	for (TActorIterator<ALight> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		SetPIELightHandleVisibility(*ActorItr, true);
	}
	
}

void ABlockingVRManager::SetPIEParticleHandleVisibility(AEmitter* Emitter, bool bVisible)
{
	if (!Emitter) return;
	TArray<UActorComponent*> ComponentList = Emitter->GetComponents();
	for (UActorComponent* Component : ComponentList)
	{
		UParticleHandleComponent* ParticleHandle = Cast<UParticleHandleComponent>(Component);
		if (ParticleHandle)
		{
			ParticleHandle->bShouldRender = bVisible;
			ParticleHandle->SetVisibility(bVisible);
			ParticleHandle->SetCollisionEnabled((ECollisionEnabled::Type)bVisible);
			break;
		}
	}
}

void ABlockingVRManager::ShowAllPIEParticleHandles(void)
{
	for (TActorIterator<AEmitter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		SetPIEParticleHandleVisibility(*ActorItr, true);
	}
}

void ABlockingVRManager::HideAllPIEParticleHandles(void)
{
	for (TActorIterator<AEmitter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		SetPIEParticleHandleVisibility(*ActorItr, false);
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

void ABlockingVRManager::HideAllPIELightDebugMeshes(void)
{
	for (TActorIterator<ALight> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		SetPIELightDebugMeshVisibility(*ActorItr, false);
	}
}

void ABlockingVRManager::ShowAllPIELightDebugMeshes(void)
{
	for (TActorIterator<ALight> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		SetPIELightDebugMeshVisibility(*ActorItr, true);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
void ABlockingVRManager::AddEditorParticle(FTransform T, AEmitter* Emitter)
{
	if (!Emitter)
	{
		UE_LOG(BlockingVR_Log, Error, TEXT("ABlockingVRManager::AddEditorParticle() Emitter = nullptr"));
		return;
	}

	if (GEditor && GEditor->GetEditorWorldContext().World() && GEditor->GetEditorWorldContext().World()->GetCurrentLevel())
	{
		AActor* EditorActor = GEditor->AddActor(GEditor->GetEditorWorldContext().World()->GetCurrentLevel(), Emitter->GetClass(), T);
		if (EditorActor)
		{
			AEmitter* EditorEmitter = Cast<AEmitter>(EditorActor);
			EditorEmitter->GetParticleSystemComponent()->SetTemplate(Emitter->GetParticleSystemComponent()->Template);
		}
		else UE_LOG(BlockingVR_Log, Error, TEXT("ABlockingVRManager::AddEditorParticle() Failed!"));
	}
}

void ABlockingVRManager::AddEditorActor(FTransform T, AActor* Actor) //private
{
	if (!Actor)
	{
		UE_LOG(BlockingVR_Log, Error, TEXT("ABlockingVRManager::AddEditorActor() Actor = nullptr"));
		return;
	}

	if (GEditor && GEditor->GetEditorWorldContext().World() && GEditor->GetEditorWorldContext().World()->GetCurrentLevel())
	{
		AActor* EditorActor = GEditor->AddActor(GEditor->GetEditorWorldContext().World()->GetCurrentLevel(), Actor->GetClass(), T);
		if (!EditorActor) UE_LOG(BlockingVR_Log, Error, TEXT("ABlockingVRManager::AddEditorActor() Faild!"));
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
	if (!Actor)
	{
		UE_LOG(BlockingVR_Log, Error, TEXT("ABlockingVRManager::DeleteEditorActor() Actor = nullptr"));
		return;
	}

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

		if (LightType == EBVRLightType::BVR_PointLight)
		{
			EditorLight = GEditor->AddActor(GEditor->GetEditorWorldContext().World()->GetCurrentLevel(), APointLight::StaticClass(), T);
		}
		else if (LightType == EBVRLightType::BVR_SpotLight)
		{
			EditorLight = GEditor->AddActor(GEditor->GetEditorWorldContext().World()->GetCurrentLevel(), ASpotLight::StaticClass(), T);
		}
		else if (LightType == EBVRLightType::BVR_DirectionalLight)
		{
			EditorLight = GEditor->AddActor(GEditor->GetEditorWorldContext().World()->GetCurrentLevel(), ADirectionalLight::StaticClass(), T);
		}
		if (EditorLight)
		{
			Result = Cast<ALight>(EditorLight);
		}
	} //end if geditor
	if (!Result) UE_LOG(BlockingVR_Log, Error, TEXT("ABlockingVRManager::AddEditorLight() Failed!"));
	return Result;

}

void ABlockingVRManager::DeletePIEEmitter(AEmitter* Emitter)
{
	bool bIsNewEmitter = false;
	for (int32 i = 0; i < NewEditorParticles.Num(); i++)
	{
		if (NewEditorParticles[i] == Emitter)
		{
			bIsNewEmitter = true;
			NewEditorParticles.RemoveAt(i); //remove from deferred additions Array;
			break;
		}
	} //end for
	if (bIsNewEmitter == false)
	{
		for (int32 i = 0; i < ModifiedEditorActors.Num(); i++) //remove from modiefied list if in there
		{
			if (ModifiedEditorActors[i] == StaticCast<AActor*>(Emitter)) //fixes previous crash bug
			{
				ModifiedEditorActors.RemoveAt(i);
				break;
			}
		}
		//try and find the editor version for destruction then destroy the PIE verson
		DeleteEditorActor(Emitter);
	}
	Emitter->Destroy();
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
		for (int32 i = 0; i < ModifiedEditorLights.Num(); i++) //remove from modiefied list if in there
		{
			if (ModifiedEditorLights[i] == Light) //fixes previous crash bug
			{
				ModifiedEditorLights.RemoveAt(i);
				break;
			}
		}
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

void ABlockingVRManager::CopyCommonLightProperties(ALight* ToLight, const ALight* FromLight) //private
{
	ToLight->SetActorTransform(FromLight->GetTransform());
	ToLight->SetLightColor(FromLight->GetLightColor());
	ToLight->GetLightComponent()->SetIntensity(FromLight->GetLightComponent()->Intensity);
	ToLight->GetLightComponent()->CastStaticShadows = FromLight->GetLightComponent()->CastStaticShadows;
	ToLight->GetLightComponent()->CastDynamicShadows = FromLight->GetLightComponent()->CastDynamicShadows;
	ToLight->GetLightComponent()->bAffectTranslucentLighting = FromLight->GetLightComponent()->bAffectTranslucentLighting;
	ToLight->GetLightComponent()->CastTranslucentShadows = FromLight->GetLightComponent()->CastTranslucentShadows;
}

void ABlockingVRManager::PastePIEPointLight(APointLight* PointLight, FVector Location) //private
{
	if (!PointLight) return;
	APointLight* PIELight = Cast<APointLight>(AddPIELight(Location, EBVRLightType::BVR_PointLight));
	if (PIELight)
	{
		CopyCommonLightProperties(PIELight, PointLight);
		PIELight->SetActorLocation(Location);
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
	ASpotLight* PIELight = Cast<ASpotLight>(AddPIELight(Location, EBVRLightType::BVR_SpotLight));
	if (PIELight)
	{
		CopyCommonLightProperties(PIELight, SpotLight);
		PIELight->SetActorLocation(Location);
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
	ADirectionalLight* PIELight = Cast<ADirectionalLight>(AddPIELight(Location, EBVRLightType::BVR_DirectionalLight));
	if (PIELight)
	{
		CopyCommonLightProperties(PIELight, DirectionalLight);
		PIELight->SetActorLocation(Location);
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

bool ABlockingVRManager::IsAllowedClass(TSubclassOf<class AActor> ClassIN)
{

	if (ClassIN->IsChildOf(ASkyLight::StaticClass()) || ClassIN->IsChildOf(ABlockingVolume::StaticClass()) || ClassIN->IsChildOf(ABrush::StaticClass()) )
		return false;
	if (ClassIN->IsChildOf(AActor::StaticClass())) return true;
	else return false;
}

void ABlockingVRManager::AttachHandle(AActor* Actor, EBVRHandleType HandleType)
{
	UActorHandleBase* pComponent = nullptr;
	if (HandleType == EBVRHandleType::BVR_PointLightHandle)
		pComponent = NewObject<UPointLightHandleComponent>(Actor, FName("LightHandleComponent"));
	else if (HandleType == EBVRHandleType::BVR_SpotLightHandle)
		pComponent = NewObject<USpotLightHandleComponent>(Actor, FName("LightHandleComponent"));
	else if (HandleType == EBVRHandleType::BVR_DirectionalLightHandle)
		pComponent = NewObject<UDirectionalLightHandleComponent>(Actor, FName("LightHandleComponent"));
	else if (HandleType == EBVRHandleType::BVR_ParticleHandle)
		pComponent = NewObject<UParticleHandleComponent>(Actor, FName("ParticleHandleComponent"));

	if (pComponent)
	{
		pComponent->AttachTo(Actor->GetRootComponent(), NAME_None, EAttachLocation::SnapToTarget, false);
		pComponent->RegisterComponentWithWorld(GetWorld());
		if (HandleType == EBVRHandleType::BVR_PointLightHandle || HandleType == EBVRHandleType::BVR_SpotLightHandle || HandleType == EBVRHandleType::BVR_DirectionalLightHandle)
		{
			Actor->SetActorHiddenInGame(false);
		}
		pComponent->SetHiddenInGame(false);
		pComponent->SetVisibility(true);
	}
}

void ABlockingVRManager::PastePIEParticle(AEmitter* Emitter, FVector Location) //private
{
	if (!Emitter) return;
	FTransform T = Emitter->GetTransform();
	T.SetLocation(Location);
	AEmitter* PIEEmitter = Cast<AEmitter>(AddPIEParticle(Emitter->GetParticleSystemComponent()->Template, T));
	if (PIEEmitter)
	{
		PIEEmitter->SetActorRotation(Emitter->GetActorRotation()); //rotation
		PIEEmitter->SetActorScale3D(Emitter->GetActorScale3D()); //scale
	}

}

#endif