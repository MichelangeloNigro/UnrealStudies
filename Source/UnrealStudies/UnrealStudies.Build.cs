// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealStudies : ModuleRules
{
	public UnrealStudies(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
