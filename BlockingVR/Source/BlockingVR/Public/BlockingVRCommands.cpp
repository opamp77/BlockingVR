// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#if WITH_EDITOR

#include "BlockingVRPrivatePCH.h"
#include "BlockingVRCommands.h"

#define LOCTEXT_NAMESPACE "FBlockingVRModule"

void FBlockingVRCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "BlockingVR", "Bring up BlockingVR window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE

#endif
