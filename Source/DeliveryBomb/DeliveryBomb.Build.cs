// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DeliveryBomb : ModuleRules
{
	public DeliveryBomb(ReadOnlyTargetRules Target) : base(Target)
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
			"DeliveryBomb",
			"DeliveryBomb/Variant_Platforming",
			"DeliveryBomb/Variant_Platforming/Animation",
			"DeliveryBomb/Variant_Combat",
			"DeliveryBomb/Variant_Combat/AI",
			"DeliveryBomb/Variant_Combat/Animation",
			"DeliveryBomb/Variant_Combat/Gameplay",
			"DeliveryBomb/Variant_Combat/Interfaces",
			"DeliveryBomb/Variant_Combat/UI",
			"DeliveryBomb/Variant_SideScrolling",
			"DeliveryBomb/Variant_SideScrolling/AI",
			"DeliveryBomb/Variant_SideScrolling/Gameplay",
			"DeliveryBomb/Variant_SideScrolling/Interfaces",
			"DeliveryBomb/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
