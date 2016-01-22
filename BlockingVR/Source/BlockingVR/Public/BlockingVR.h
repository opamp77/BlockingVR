// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#if WITH_EDITOR

#pragma once

#include "ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(BlockingVR_Log, Log, All);

class FToolBarBuilder;
class FMenuBuilder;

class FBlockingVRModule : public IModuleInterface
{
public:
	/**
	* Singleton-like access to this module's interface.  This is just for convenience!
	* Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	*
	* @return Returns singleton instance, loading the module on demand if needed
	*/

	static inline FBlockingVRModule& Get()
	{
		return FModuleManager::LoadModuleChecked< FBlockingVRModule >("BlockingVR");
	}

	/**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	*
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("BlockingVR");
	}

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