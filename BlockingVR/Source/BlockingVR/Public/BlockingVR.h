// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#if WITH_EDITORONLY_DATA

#pragma once

#include "ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(BlockingVR_Log, Log, All);

class FToolBarBuilder;
class FMenuBuilder;

class FBlockingVRModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);


	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};

#endif