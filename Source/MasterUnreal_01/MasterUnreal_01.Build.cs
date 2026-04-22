// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MasterUnreal_01 : ModuleRules
{
	public MasterUnreal_01(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
