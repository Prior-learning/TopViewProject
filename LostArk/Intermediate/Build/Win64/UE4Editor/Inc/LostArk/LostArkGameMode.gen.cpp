// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LostArk/LostArkGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLostArkGameMode() {}
// Cross Module References
	LOSTARK_API UClass* Z_Construct_UClass_ALostArkGameMode_NoRegister();
	LOSTARK_API UClass* Z_Construct_UClass_ALostArkGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_LostArk();
// End Cross Module References
	void ALostArkGameMode::StaticRegisterNativesALostArkGameMode()
	{
	}
	UClass* Z_Construct_UClass_ALostArkGameMode_NoRegister()
	{
		return ALostArkGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ALostArkGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ALostArkGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_LostArk,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ALostArkGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "LostArkGameMode.h" },
		{ "ModuleRelativePath", "LostArkGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ALostArkGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALostArkGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ALostArkGameMode_Statics::ClassParams = {
		&ALostArkGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_ALostArkGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ALostArkGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ALostArkGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ALostArkGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ALostArkGameMode, 1399802134);
	template<> LOSTARK_API UClass* StaticClass<ALostArkGameMode>()
	{
		return ALostArkGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ALostArkGameMode(Z_Construct_UClass_ALostArkGameMode, &ALostArkGameMode::StaticClass, TEXT("/Script/LostArk"), TEXT("ALostArkGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALostArkGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
