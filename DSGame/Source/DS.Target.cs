// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DSTarget : TargetRules
{
	public DSTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "DSCore", "DSCoreFrameWork", "DSTable", "DSUI_Core", "DSUtil", "DSActor", "DS" } );
	}
}
