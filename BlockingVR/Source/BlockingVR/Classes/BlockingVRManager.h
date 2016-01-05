// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
//#if WITH_EDITORONLY_DATA

#pragma once

#include "BlockingVRManager.generated.h"

class ULightHandleBase; 
class UPointLightHandleComponent;
class USpotLightHandleComponent;
class UDirectionalLightHandleComponent;
class USkyLightHandleComponent;

UENUM(BlueprintType)		// required as using ELightComponent in SceneTypes.h was causing compile errors for some reason?.
enum class EBVRLightType : uint8
{
	VBR_DirectionalLight	UMETA(DisplayName = "Directional"),
	VBR_PointLight 	UMETA(DisplayName = "Point"),
	VBR_SpotLight 	UMETA(DisplayName = "Spot")
};

UCLASS()
class ABlockingVRManager : public AActor
{
	GENERATED_UCLASS_BODY()
	virtual void BeginPlay() override;

public:

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

	/*Editor Actors/Lights that have been Deleted in PIE and will be Deleted in the editor upon Endplay()*/
	UPROPERTY(BluePrintReadOnly, Category = "BlockingVR")
		TArray<AActor*> DeletedEditorActors;
	
	/*Create UTexture from Thumbnail Data of ActorClass*/
	/*Unfinished. currently only works for assets that have been saved.*/
	UFUNCTION(BlueprintCallable, Category = "BlockingVR")
		UTexture2D* CreateActorThumbnailTexture(TSubclassOf<AActor> ActorIN);

	/*Create UTexture from Thumbnail Data of StaticMesh*/
	/*Unfinished. currently only works for assets that have been saved.*/
	UFUNCTION(BlueprintCallable, Category = "BlockingVR")
		UTexture2D* CreateMeshThumbnailTexture(class UStaticMesh* MeshIN);

	/*Create UTexture from Thumbnail Data of SkeletalMesh*/
	/*Unfinished. currently only works for assets that have been saved.*/
	UFUNCTION(BlueprintCallable, Category = "BlockingVR")
		UTexture2D* CreateSkeletalMeshThumbnailTexture(class USkeletalMesh* SMeshIN);

	/*Create UTexture from Thumbnail Data of Material*/
	/*Unfinished. currently only works for assets that have been saved.*/
	UFUNCTION(BlueprintCallable, Category = "BlockingVR")
		UTexture2D* CreateMaterialThumbnailTexture(class UMaterial* MaterialIN);

	/*Create UTexture from Thumbnail Data of ParticleSystem*/
	/*Unfinished. currently only works for assets that have been saved.*/
	UFUNCTION(BlueprintCallable, Category = "BlockingVR")
		UTexture2D* CreateParticleThumbnailTexture(class UParticleSystem* ParticleIN);

	/*Apply's Deferred changes to Editor World and emptys Arrays*/
	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void ApplyDeferredChanges();

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
	/*Pie Light Handles and debug meshes*/

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
		void SetRotationPIEActor(AActor* Actor, FRotator Rotation, bool Snap = false, bool UseEditorSnapSize = false, float SnapSize = 1.0);

	UFUNCTION(BluePrintCallable, Category = "BlockingVR")
		void SetScalePIEActor(AActor* Actor, FVector Scale, bool Snap = false, bool UseEditorSnapSize = false, float SnapSize = 1.0);

	/* Removes the PIE Actor as well as the editor world Actor if it exists
	   and removes the refererence from NewEditorActors/ModifiedEditorActors Array. */
	UFUNCTION(BluePrintCallable, Category = "BlockingVR") 
		void DeletePIEActor(AActor* Actor);

private:

	UTexture2D* CreateThumbnailTexture(FName PackageName, FName ObjectPath = FName(""));
	
	bool IsAllowedClass(AActor* Actor);

	bool IsAllowedClass(TSubclassOf<class AActor> ClassIN);

	FVector SnapVector(FVector V, float SnapValue);

	FRotator SnapRotator(FRotator R, float SnapValue);

	void InvalidateEditorLightingCache(AActor* PIEActor);

	/* Adds The Actor to the editor world. */
	void AddEditorActor(FTransform T, AActor* Actor);

	/* Deletes the editor world actor if it already exists in the editor world. */
	/* Used for all Actor Types. */
	void DeleteEditorActor(AActor* Actor);

	void DeletePIELight(ALight* Light);

	void PastePIELight(ALight* Light, FVector Location);

	void PastePIEPointLight(APointLight* PointLight, FVector Location);

	void PastePIESpotLight(ASpotLight* SpotLight, FVector Location);

	void PastePIEDirectionalLight(ADirectionalLight* PointLight, FVector Location);

	/*Adds the Light to the Editor world*/
	ALight* AddEditorLight(FTransform T, EBVRLightType LightType);

	/*Set properties shared by all light actors*/
	void SetCommonEditorLightProperties(ALight* EditorLight, const ALight* PIELight);

	/* Update Arrays*/

	void NotifyModifiedActor(AActor* Actor);

	void NotifyModifiedLight(ALight* Light);


};

