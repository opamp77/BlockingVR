// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#if WITH_EDITOR

#pragma once

#include "SlateBasics.h"
#include "BlockingVRStyle.h"

class FBlockingVRCommands : public TCommands<FBlockingVRCommands>
{
public:

	FBlockingVRCommands()
		: TCommands<FBlockingVRCommands>(TEXT("BlockingVR"), NSLOCTEXT("Contexts", "BlockingVR", "BlockingVR Plugin"), NAME_None, FBlockingVRStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};

#endif