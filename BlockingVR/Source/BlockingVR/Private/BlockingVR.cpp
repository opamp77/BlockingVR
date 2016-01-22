// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#if WITH_EDITOR

#include "BlockingVRPrivatePCH.h"

#include "SlateBasics.h"
#include "SlateExtras.h"

#include "BlockingVRStyle.h"
#include "BlockingVRCommands.h"

#include "LevelEditor.h"

DEFINE_LOG_CATEGORY(BlockingVR_Log);

static const FName BlockingVRTabName("BlockingVR");

#define LOCTEXT_NAMESPACE "FBlockingVRModule"

void FBlockingVRModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FBlockingVRStyle::Initialize();
	FBlockingVRStyle::ReloadTextures();

	FBlockingVRCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FBlockingVRCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FBlockingVRModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FBlockingVRModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FBlockingVRModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(BlockingVRTabName, FOnSpawnTab::CreateRaw(this, &FBlockingVRModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FBlockingVRTabTitle", "BlockingVR"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FCollectionManagerModule& CollectionManagerModule = FCollectionManagerModule::GetModule();
	ICollectionManager& CollectionManager = CollectionManagerModule.Get();

	if (!CollectionManager.CollectionExists(FName("BlockingVRCollection"), ECollectionShareType::CST_Local))
	{
		CollectionManager.CreateCollection(FName("BlockingVRCollection"), ECollectionShareType::CST_Local, ECollectionStorageMode::Static);
	}
}

void FBlockingVRModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FBlockingVRStyle::Shutdown();

	FBlockingVRCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(BlockingVRTabName);
}

TSharedRef<SDockTab> FBlockingVRModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FBlockingVRModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("BlockingVR.cpp"))
		);
	
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FBlockingVRModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(BlockingVRTabName);
}

void FBlockingVRModule::AddMenuExtension(FMenuBuilder& Builder)
{
	//Builder.AddMenuEntry(FBlockingVRCommands::Get().OpenPluginWindow);
}

void FBlockingVRModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	//Builder.AddToolBarButton(FBlockingVRCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBlockingVRModule, BlockingVR)

#endif