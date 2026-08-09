// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CatGame : ModuleRules
{
	public CatGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"CatGame",
			"CatGame/Variant_Platforming",
			"CatGame/Variant_Platforming/Animation",
			"CatGame/Variant_Combat",
			"CatGame/Variant_Combat/AI",
			"CatGame/Variant_Combat/Animation",
			"CatGame/Variant_Combat/Gameplay",
			"CatGame/Variant_Combat/Interfaces",
			"CatGame/Variant_Combat/UI",
			"CatGame/Variant_SideScrolling",
			"CatGame/Variant_SideScrolling/AI",
			"CatGame/Variant_SideScrolling/Gameplay",
			"CatGame/Variant_SideScrolling/Interfaces",
			"CatGame/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
