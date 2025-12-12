// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FrictionGame : ModuleRules
{
	public FrictionGame(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate",
			"PhysicsCore"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"FrictionGame",
			"FrictionGame/Variant_Horror",
			"FrictionGame/Variant_Horror/UI",
			"FrictionGame/Variant_Shooter",
			"FrictionGame/Variant_Shooter/AI",
			"FrictionGame/Variant_Shooter/UI",
			"FrictionGame/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
