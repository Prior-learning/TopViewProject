// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef LOSTARK_LostArkCharacter_generated_h
#error "LostArkCharacter.generated.h already included, missing '#pragma once' in LostArkCharacter.h"
#endif
#define LOSTARK_LostArkCharacter_generated_h

#define LostArk_Source_LostArk_LostArkCharacter_h_12_SPARSE_DATA
#define LostArk_Source_LostArk_LostArkCharacter_h_12_RPC_WRAPPERS
#define LostArk_Source_LostArk_LostArkCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS
#define LostArk_Source_LostArk_LostArkCharacter_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesALostArkCharacter(); \
	friend struct Z_Construct_UClass_ALostArkCharacter_Statics; \
public: \
	DECLARE_CLASS(ALostArkCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LostArk"), NO_API) \
	DECLARE_SERIALIZER(ALostArkCharacter)


#define LostArk_Source_LostArk_LostArkCharacter_h_12_INCLASS \
private: \
	static void StaticRegisterNativesALostArkCharacter(); \
	friend struct Z_Construct_UClass_ALostArkCharacter_Statics; \
public: \
	DECLARE_CLASS(ALostArkCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LostArk"), NO_API) \
	DECLARE_SERIALIZER(ALostArkCharacter)


#define LostArk_Source_LostArk_LostArkCharacter_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ALostArkCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ALostArkCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ALostArkCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ALostArkCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ALostArkCharacter(ALostArkCharacter&&); \
	NO_API ALostArkCharacter(const ALostArkCharacter&); \
public:


#define LostArk_Source_LostArk_LostArkCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ALostArkCharacter(ALostArkCharacter&&); \
	NO_API ALostArkCharacter(const ALostArkCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ALostArkCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ALostArkCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ALostArkCharacter)


#define LostArk_Source_LostArk_LostArkCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__TopDownCameraComponent() { return STRUCT_OFFSET(ALostArkCharacter, TopDownCameraComponent); } \
	FORCEINLINE static uint32 __PPO__CameraBoom() { return STRUCT_OFFSET(ALostArkCharacter, CameraBoom); } \
	FORCEINLINE static uint32 __PPO__CursorToWorld() { return STRUCT_OFFSET(ALostArkCharacter, CursorToWorld); }


#define LostArk_Source_LostArk_LostArkCharacter_h_9_PROLOG
#define LostArk_Source_LostArk_LostArkCharacter_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LostArk_Source_LostArk_LostArkCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	LostArk_Source_LostArk_LostArkCharacter_h_12_SPARSE_DATA \
	LostArk_Source_LostArk_LostArkCharacter_h_12_RPC_WRAPPERS \
	LostArk_Source_LostArk_LostArkCharacter_h_12_INCLASS \
	LostArk_Source_LostArk_LostArkCharacter_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define LostArk_Source_LostArk_LostArkCharacter_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LostArk_Source_LostArk_LostArkCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	LostArk_Source_LostArk_LostArkCharacter_h_12_SPARSE_DATA \
	LostArk_Source_LostArk_LostArkCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	LostArk_Source_LostArk_LostArkCharacter_h_12_INCLASS_NO_PURE_DECLS \
	LostArk_Source_LostArk_LostArkCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOSTARK_API UClass* StaticClass<class ALostArkCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID LostArk_Source_LostArk_LostArkCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
