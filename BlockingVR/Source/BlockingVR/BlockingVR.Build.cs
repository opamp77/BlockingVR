// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BlockingVR : ModuleRules
{
	public BlockingVR(TargetInfo Target)
	{
		
		PublicIncludePaths.AddRange(
			new string[] {
				"BlockingVR/Public",
                "Runtime/Engine/Public",
                "Runtime/Engine/Classes/GameFramework",
                 "Runtime/Engine/Classes/Engine",
                 "Runtime/Engine/Classes/Components",
                 "Runtime/HeadMountedDisplay/Public/",
                 "Runtime/AssetRegistry/Public/",
                 "Editor/PropertyEditor/Public"
             
                 //"Runtime/Engine/Classes/Kismet/"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"BlockingVR/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"InputCore",
				"UnrealEd",
				"LevelEditor",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "HeadMountedDisplay",
                "AssetRegistry",
                "PropertyEditor"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
