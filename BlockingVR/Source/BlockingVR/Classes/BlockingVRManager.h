// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#if WITH_EDITOR

#pragma once

#include "BlockingVRManager.generated.h"

class UActorHandleBase;
class ULightHandleBase; 
class UPointLightHandleComponent;
class USpotLightHandleComponent;
class UDirectionalLightHandleComponent;
//class USkyLightHandleComponent;
class UParticleHandleComponent;

UENUM(BlueprintType)		//HandleTypes
enum class EBVRHandleType : uint8
{
	BVR_DirectionalLightHandle	UMETA(DisplayName = "DirectionalLightHandle"),
	BVR_PointLightHandle 	UMETA(DisplayName = "PointLightHandle"),
	BVR_SpotLightHandle 	UMETA(DisplayName = "SpotLightHandle"),
	BVR_ParticleHandle		UMETA(DisplayName = "ParticleHandle")
};

UENUM(BlueprintType)		// required as using ELightComponent in SceneTypes.h was causing compile errors for some reason?.
enum class EBVRLightType : uint8
{
	BVR_DirectionalLight	UMETA(DisplayName = "Directional"),
	BVR_PointLight 	UMETA(DisplayName = "Point"),
	BVR_SpotLight 	UMETA(DisplayName = "Spot")
};

UCLASS()
class ABlockingVRManager : public AActor
{
	GENERATED_UCLASS_BODY()
	virtual void BeginPlay() override;

public:

	/*New Lights that have been spawned in PIE and will be added to the editor upon Endplay()*/
	UPROPERTY(BluePrintReadOnly, Category = "BlockingVR")
		TArray<AEmitter*> NewEditorParticles;

	/*New Lights that have been spawned in PIE and will be added to the editor upon Endplay()*/
	UPROPERTY(BluePrintReadOnly, Category = "BlockingVR")
		TArray<ALight*> NewEditorLights;

	/*Lights that have been Modified in PIE and will be Updated in the editor upon Endplay()*/
	UPROPERTY(BluePrintReadOnly, Category = "BlockingVR")
		TArray<ALight*> ModifiedEditorLights;

	/*New Actors(ExcludingLights) that have been spawned in PIE and will be added to the editor upon Endplay()*/
	UPROPERTY(BluePrintReadOnly, Category = "BlockingVR")
		TArray<AActor*> NewEditorActors;

	/*Actors(Excluding Lights) that have been Modified in PIE and will be Updated in the editor upon Endplay()*/
	UPROPERTY(BluePrintReadOnly, Category = "BlockingVR")
		TArray<AActor*> ModifiedEditorActors;

	/*Editor Actors/Lights/Particles that have been Deleted in PIE and will be Deleted in the editor upon Endplay()*/
	UPROPERTY(BluePrintReadOnly, Category = "BlockingVR")
		TArray<AActor*> DeletedEditorActors;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UFUNCTION(BlueprintCallable, Category = "BlockingVR")
		void GetCollectionActorClasses(UPARAM(ref) TArray< TSubclassOf<AActor> > &ActorClassesArray);

	UFUNCTION(BlueprintCallable, Category = "BlockingVR")
		void GetCollectionStaticMeshes(UPARAM(ref) TArray<UStaticMesh*> &StaticMeshReferenceArray);

	UFUNCTION(BlueprintCallable, Category = "BlockingVR")
		void GetCollectionParticles(UPARAM(ref) TArray<UParticleSystem*> &ParticleSystemReferenceArray);

	UFUNCTION(BlueprintCallable, Category = "BlockingVR")
		void GetCollectionMaterials(UPARAM(ref) TArray<UMaterialInterface*> &MaterialReferenceArray);

	//UFUNCTION(BlueprintCallable, Category = "BlockingVR")
	//	void GetCollectionSkeletalMeshes(UPARAM(ref) TArray<USkeletalMesh*> &SkeletalMeshReferenceArray);

	/*Create UTexture from Thumbnail Data of ActorClass*/
	UFUNCTION(BlueprintCallable, Category = "BlockingVR")
		UTexture2D* CreateActorThumbnailTexture(TSubclassOf<AActor> ActorIN);

	/*Create UTexture from Thumbnail Data of StaticMesh*/
	UFUNCTION(BlueprintCallable, Category = "BlockingVR")
		UTexture2D* CreateMeshThumbnailTexture(class UStaticMesh* MeshIN);

	/*Create UTexture from Thumbnail Data of SkeletalMesh*/
	//UFUNCTION(BlueprintCallable, Category = "BlockingVR")
	//	UTexture2D* CreateSkeletalMeshThumbnailTexture(class USkeletalMesh* SMeshIN);

	/*Create UTexture from Thumbnail Data of Material*/
	UFUNCTION(BlueprintCallable, Category = "BlockingVR")
		UTexture2D* CreateMaterialThumbnailTexture(class UMaterial* MaterialIN);

	/*Create UTexture from Thumbnail Data of ParticleSystem*/
	UFUNCTION(BlueprintCallable, Category = "BlockingVR")
		UTexture2D* CreateParticleThumbnailTexture(class UParticleSystem* ParticleIN);

	/*Apply's Deferred changes to Editor World and emptys Arrays*/
	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void ApplyDeferredChanges();

	//Particles
	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		AEmitter* AddPIEParticle(UParticleSystem* Template, FTransform T);

	//Lights

	/*Spawns a new Light Actor of EBVRLightType In the PIE world with deferred addition to the editor world*/
	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		ALight* AddPIELight(FVector Location, EBVRLightType LightType);

	/*Common Lighting*/

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void SetPIELightColor(ALight* Light, FLinearColor Color);

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void SetPIELightIntensity(ALight* Light, float Intensity);

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void SetPIELightSquareFallOff(ALight* Light, bool bSqrFalloff);

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void SetPIELightStaticShadows(ALight* Light, bool bStaticShadows);

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void SetPIELightDynamicShadows(ALight* Light, bool bDynamicShadows);

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void SetPIELightTranslucentLighting(ALight* Light, bool bTranslucentLighting);

	/*PointLight sets & Gets*/

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void SetPIEPointLightRadius(APointLight* PointLight, float Radius);

	/*required as Attenuation radius is currently not availible via blueprint*/
	UFUNCTION(BluePrintCallable, BlueprintPure, Category = "BlockingVR")
		float GetPIEPointLightRadius(APointLight* PointLight);

	/* SpotLight Sets & Gets*/

	/*required as Attenuation radius is currently not availible via blueprint*/
	UFUNCTION(BluePrintCallable, BlueprintPure, Category = "BlockingVR")
		float GetPIESpotLightRadius(ASpotLight* SpotLight);

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void SetPIESpotLightRadius(ASpotLight* SpotLight, float Radius);

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void SetPIESpotLightOuterCone(ASpotLight* SpotLight, float AngleD);

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void SetPIESpotLightInnerCone(ASpotLight* SpotLight, float AngleD);


	///////////////////////////////////////////////////////////////////////////////////
	/*Pie Actor Handles and debug meshes*/
	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void ShowAllPIEHandles();

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void HideAllPIEHandles();

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void SetPIEParticleHandleVisibility(AEmitter* Emitter, bool bVisible);

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void ShowAllPIEParticleHandles();

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void HideAllPIEParticleHandles();

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void SetPIELightHandleVisibility(ALight* Light, bool bVisible);

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void HideAllPIELightHandles();

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void ShowAllPIELightHandles();

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void SetPIELightDebugMeshVisibility(ALight* Light, bool bVisible );

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void HideAllPIELightDebugMeshes();

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void ShowAllPIELightDebugMeshes();
	
	//Actors

	/*Sets Mesh of staticMesh Component*/
	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		bool PIESetStaticMesh(UStaticMeshComponent* StaticMeshComponent, UStaticMesh* Mesh);

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		AStaticMeshActor* AddPIEStaticMesh(UStaticMesh* Mesh, FTransform T);

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void PIESetMaterial(UStaticMeshComponent* StaticMeshComponent, UMaterial* Material, uint8 Index = 0);

	/* Use for special cases of spawning an actor which will be duplicated in the editor world */
	/* upon ApplyDeferredChanges(). Normally PastePIEActor() should be used which calls this. */
	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		AActor* AddPIEActor(TSubclassOf<class AActor> Actor, FTransform T);

	/* Creates a copy of an actor with the same scale and rotation at the specific location */
	/* which will be duplicated in the editor world upon ApllyDeferredChanges(). */
	/* If it is a light then the basic light propertys will also be copied via PastPIELight(). */
	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void PastePIEActor(AActor* Actor, FVector Location);

	/* Modifys Actor Transforms*/
	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void SetTransformPIEActor(AActor* Actor, FTransform T);

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void SetLocationPIEActor(AActor* Actor, FVector Location, bool Snap = false, bool UseEditorSnapSize = false, float SnapSize = 1.0);

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void SetRotationPIEActor(AActor* Actor, FRotator Rotation, bool relative = false, bool Snap = false, bool UseEditorSnapSize = false, float SnapSize = 1.0);

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void SetScalePIEActor(AActor* Actor, FVector Scale, bool Snap = false, bool UseEditorSnapSize = false, float SnapSize = 1.0);

	/* Removes the PIE Actor as well as the editor world Actor if it exists
	   and removes the refererence from NewEditorActors/ModifiedEditorActors Array. */
	UFUNCTION(BluePrintCallable, Category = "BlockingVR") 
		void DeletePIEActor(AActor* Actor);

private:

	void CopyStaticMeshActorMaterials(AStaticMeshActor* FromActor, AStaticMeshActor* ToActor);

	void AttachHandle(AActor* Actor,EBVRHandleType HandleType);

	UTexture2D* CreateThumbnailTexture(FName PackageName, FName ObjectPath = FName(""));
	
	bool IsAllowedClass(AActor* Actor);

	bool IsAllowedClass(TSubclassOf<class AActor> ClassIN);

	FVector SnapVector(FVector V, float SnapValue);

	FRotator SnapRotator(FRotator R, float SnapValue);

	void InvalidateEditorLightingCache(AActor* PIEActor);

	/* Adds The Actor to the editor world. */
	void AddEditorActor(FTransform T, AActor* Actor);

	void AddEditorParticle(FTransform T, AEmitter* Emitter);

	/* Deletes the editor world actor if it already exists in the editor world. */
	/* Used for all Actor Types. */
	void DeleteEditorActor(AActor* Actor);

	void DeletePIELight(ALight* Light);

	void DeletePIEEmitter(AEmitter* Emitter);

	void PastePIELight(ALight* Light, FVector Location);

	void PastePIEPointLight(APointLight* PointLight, FVector Location);

	void PastePIESpotLight(ASpotLight* SpotLight, FVector Location);

	void PastePIEDirectionalLight(ADirectionalLight* PointLight, FVector Location);

	void PastePIEParticle(AEmitter* Emitter, FVector Location);

	/*Adds the Light to the Editor world*/
	ALight* AddEditorLight(FTransform T, EBVRLightType LightType);

	/*Copy properties shared by all light actors(Including Transform. Excluding Mobility)*/
	void CopyCommonLightProperties(const ALight* FromLight, ALight* ToLight);

	/*Copy properties shared by all pointlights*/
	void CopyPointLightSpecificProperties(APointLight* FromLight, APointLight* ToLight);

	void CopySpotLightSpecificProperties(ASpotLight* FromLight , ASpotLight* ToLight);

	/* Update Arrays*/

	void NotifyModifiedActor(AActor* Actor);

	void NotifyModifiedLight(ALight* Light);

	/*Moves an actor regardless of current mobility*/
	/*but does mot invalidate lighting cache*/
	void MoveActor(AActor* Actor, FVector Location);

};

#endif

