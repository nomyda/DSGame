// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DSEditorTarget : TargetRules
{
	public DSEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "DSCore", "DSCoreFrameWork", "DSTable", "DSUI_Core", "DSUtil", "DSActor", "DS" } );
	}
}
