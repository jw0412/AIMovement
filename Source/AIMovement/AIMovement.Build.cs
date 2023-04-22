// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AIMovement : ModuleRules
{
	public AIMovement(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" });

		// AI Modules
		PublicDependencyModuleNames.AddRange(new string[] { "AIModule", "NavigationSystem", "GameplayTasks" });
	}
}
