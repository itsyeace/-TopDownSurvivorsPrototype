// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TDSurvivorsProto : ModuleRules
{
	public TDSurvivorsProto(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"NavigationSystem",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"Niagara",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"TDSurvivorsProto",
			"TDSurvivorsProto/Variant_Strategy",
			"TDSurvivorsProto/Variant_Strategy/UI",
			"TDSurvivorsProto/Variant_TwinStick",
			"TDSurvivorsProto/Variant_TwinStick/AI",
			"TDSurvivorsProto/Variant_TwinStick/Gameplay",
			"TDSurvivorsProto/Variant_TwinStick/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
