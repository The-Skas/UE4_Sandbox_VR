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
	ShootCrit 	UMETA(DisplayName = "ShootCrit"),
	Miss 	UMETA(DisplayName = "Miss"),
	Spin	UMETA(DisplayName = "Spin"),
	Equip UMETA(DisplayName = "Equip"),
	Release UMETA(DisplayName = "Release"),
	Grab UMETA(DisplayName = "Grab"),
	Stop UMETA(DisplayName = "Stop")
};

USTRUCT(BlueprintType)
struct FComboTemplate
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
	FString SubjectTag;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
	bool bSubj;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
		EActionEnum Verb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
		FString  ObjectTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
	bool bObj;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
		FString  SubjectToTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
	bool bSubjTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
		float TimeDiff;
};
USTRUCT(BlueprintType)
struct FComboData
{
	GENERATED_BODY()
public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
		AActor * Subject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
		EActionEnum Verb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
		AActor * Object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
		AActor * SubjectTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
		float TimeDiff;
};

USTRUCT(BlueprintType)
struct FComboNode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
	FComboTemplate node;	
	
	TArray<FComboNode*> combo_nodes;

	TArray<FComboTemplate> stop_nodes;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
	int32 score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
	bool isCombo;
};

USTRUCT(BlueprintType)
struct FComboGraphInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")	
	FString comboName;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")	
	FComboNode currNode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
	FComboData currData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
	float startTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
	int32 baseScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
	int32 bonusScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score System")
	bool isCombo;
	//TArray<FComboNode*> combo_nodes;
};


UCLASS()
class VRTEST_V1_API UScoringFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//**Combo Data**
	//toCompare if a given Combo Data is equal to the expected Combo Template
	UFUNCTION(BlueprintPure, Category = "Score System")
	static bool isEqualTemplate(UPARAM(ref) FComboData & comboData, UPARAM(ref) FComboTemplate & comboTemp);

	UFUNCTION(BlueprintPure, Category = "Score System")
	static bool isEqual(UPARAM(ref) FComboData & comboData, UPARAM(ref) FComboTemplate & comboTemp, UPARAM(ref) FComboData & currentCombo);
	//Combo Node
	UFUNCTION(BlueprintCallable, Category = "Score System")
	static int32 getLengthStopData(UPARAM(ref) FComboNode & inNode);
	
	UFUNCTION(BlueprintPure, Category = "Score System")
	static void addStopTemplate(UPARAM(ref) FComboNode & inNode, FComboTemplate data, FComboNode &outNode);

	UFUNCTION(BlueprintPure, Category = "Score System")
	static void addComboNode(UPARAM(ref) FComboNode & inNode, UPARAM(ref) FComboNode & addNode, struct FComboNode &outNode);
	
	UFUNCTION(BlueprintPure, Category = "Score System")
	static void getChildrenComboNode(UPARAM(ref) FComboNode & inNode,   TArray<FComboNode> &outChildrenNodes);

	UFUNCTION(BlueprintPure, Category = "Score System")
	static void getStopNodes(UPARAM(ref) FComboNode & inNode,   TArray<FComboTemplate> &outStopNodes);
private:
	static bool isTagEqual(AActor * actorA, AActor * actorB);
	static bool isTagEqual(AActor * actorA, FString tag);
};
