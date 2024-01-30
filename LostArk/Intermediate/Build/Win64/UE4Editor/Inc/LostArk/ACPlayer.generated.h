// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef LOSTARK_ACPlayer_generated_h
#error "ACPlayer.generated.h already included, missing '#pragma once' in ACPlayer.h"
#endif
#define LOSTARK_ACPlayer_generated_h

#define LostArk_Source_LostArk_Attacker_ACPlayer_h_10_SPARSE_DATA
#define LostArk_Source_LostArk_Attacker_ACPlayer_h_10_RPC_WRAPPERS
#define LostArk_Source_LostArk_Attacker_ACPlayer_h_10_RPC_WRAPPERS_NO_PURE_DECLS
#define LostArk_Source_LostArk_Attacker_ACPlayer_h_10_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAACPlayer(); \
	friend struct Z_Construct_UClass_AACPlayer_Statics; \
public: \
	DECLARE_CLASS(AACPlayer, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LostArk"), NO_API) \
	DECLARE_SERIALIZER(AACPlayer)


#define LostArk_Source_LostArk_Attacker_ACPlayer_h_10_INCLASS \
private: \
	static void StaticRegisterNativesAACPlayer(); \
	friend struct Z_Construct_UClass_AACPlayer_Statics; \
public: \
	DECLARE_CLASS(AACPlayer, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LostArk"), NO_API) \
	DECLARE_SERIALIZER(AACPlayer)


#define LostArk_Source_LostArk_Attacker_ACPlayer_h_10_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AACPlayer(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AACPlayer) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AACPlayer); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AACPlayer); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AACPlayer(AACPlayer&&); \
	NO_API AACPlayer(const AACPlayer&); \
public:


#define LostArk_Source_LostArk_Attacker_ACPlayer_h_10_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AACPlayer(AACPlayer&&); \
	NO_API AACPlayer(const AACPlayer&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AACPlayer); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AACPlayer); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AACPlayer)


#define LostArk_Source_LostArk_Attacker_ACPlayer_h_10_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__mCamera() { return STRUCT_OFFSET(AACPlayer, mCamera); } \
	FORCEINLINE static uint32 __PPO__mSpring() { return STRUCT_OFFSET(AACPlayer, mSpring); } \
	FORCEINLINE static uint32 __PPO__CursorToWorld() { return STRUCT_OFFSET(AACPlayer, CursorToWorld); }


#define LostArk_Source_LostArk_Attacker_ACPlayer_h_7_PROLOG
#define LostArk_Source_LostArk_Attacker_ACPlayer_h_10_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LostArk_Source_LostArk_Attacker_ACPlayer_h_10_PRIVATE_PROPERTY_OFFSET \
	LostArk_Source_LostArk_Attacker_ACPlayer_h_10_SPARSE_DATA \
	LostArk_Source_LostArk_Attacker_ACPlayer_h_10_RPC_WRAPPERS \
	LostArk_Source_LostArk_Attacker_ACPlayer_h_10_INCLASS \
	LostArk_Source_LostArk_Attacker_ACPlayer_h_10_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define LostArk_Source_LostArk_Attacker_ACPlayer_h_10_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LostArk_Source_LostArk_Attacker_ACPlayer_h_10_PRIVATE_PROPERTY_OFFSET \
	LostArk_Source_LostArk_Attacker_ACPlayer_h_10_SPARSE_DATA \
	LostArk_Source_LostArk_Attacker_ACPlayer_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
	LostArk_Source_LostArk_Attacker_ACPlayer_h_10_INCLASS_NO_PURE_DECLS \
	LostArk_Source_LostArk_Attacker_ACPlayer_h_10_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOSTARK_API UClass* StaticClass<class AACPlayer>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID LostArk_Source_LostArk_Attacker_ACPlayer_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
