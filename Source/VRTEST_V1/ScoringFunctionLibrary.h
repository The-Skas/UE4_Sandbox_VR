// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ScoringFunctionLibrary.generated.h"

/**
 * 
 */
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EActionEnum : uint8
{
	Hit UMETA(DisplayName = "Hit"),
	Shoot 	UMETA(DisplayName = "Shoot"),
	Spin	UMETA(DisplayName = "Spin"),
	Equip UMETA(DisplayName = "Equip"),
	Release UMETA(DisplayName = "Release"),
	Grab UMETA(DisplayName = "Grab"),
	Stop UMETA(DisplayName = "Stop")
};
USTRUCT(BlueprintType)
struct FComboData
{
	GENERATED_BODY()
public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
		UObject * Subject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
		EActionEnum Verb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
		UObject * Object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
		UObject * SubjectTo;
};

USTRUCT(BlueprintType)
struct FComboNode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
	FComboData node;	
	
	TArray<FComboNode*> combo_nodes;

	TArray<FComboData> stop_nodes;
};

USTRUCT(BlueprintType)
struct FComboGraph
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")	
	FString comboName;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")	
	FComboNode comboStart;
	//TArray<FComboNode*> combo_nodes;
};

UCLASS()
class VRTEST_V1_API UScoringFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//Combo Data

	//Combo Node
	UFUNCTION(BlueprintCallable, Category = "Score System")
	static int32 getLengthStopData(UPARAM(ref) FComboNode & inNode);
	
	UFUNCTION(BlueprintPure, Category = "Score System")
	static void addStopData(UPARAM(ref) FComboNode & inNode, FComboData data, FComboNode &outNode);

	UFUNCTION(BlueprintPure, Category = "Score System")
	static void addComboNode(UPARAM(ref) FComboNode & inNode, UPARAM(ref) FComboNode & addNode, struct FComboNode &outNode);

	
	UFUNCTION(BlueprintPure, Category = "Score System")
	static void get
	
};
