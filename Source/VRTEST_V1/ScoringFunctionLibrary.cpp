// Fill out your copyright notice in the Description page of Project Settings.

#include "VRTEST_V1.h"
#include "ScoringFunctionLibrary.h"
#include "IGun.h"

void UScoringFunctionLibrary::addStopTemplate(UPARAM(ref) FComboNode & inNode, FComboTemplate data, FComboNode &outNode) {
	inNode.stop_nodes.Add(data);
	outNode = inNode;
}

void UScoringFunctionLibrary::addComboNode( UPARAM(ref) FComboNode & inNode, UPARAM(ref) FComboNode & addNode, struct FComboNode &outNode) {
	//bool does_implement = inNode.node.Object->GetClass()->ImplementsInterface(UIGun::StaticClass());
	//if (does_implement) {
	//	UE_LOG(LogTemp, Warning, TEXT("In!"));
	//}

	//bool isChild = inNode.node.Subject->IsA(AActor::StaticClass());
	//FName yoyo = inNode.node.Subject->GetClass()->GetFName();
	//FString yawyaw = yoyo.ToString();
	//if (isChild) {
	//	UE_LOG(LogTemp, Warning, TEXT("In!"));
	//}
	//if (inNode.node.Subject->IsA(inNode.node.Subject->GetClass())) {
	//	UE_LOG(LogTemp, Warning, TEXT("In!"));
	//}

	//if (inNode.node.Subject->IsA(inNode.node.Object->GetClass())) {
	//	
	//	UE_LOG(LogTemp, Warning, TEXT("In!"));
	//}
	//

	inNode.combo_nodes.Add(&addNode);
	
	outNode = inNode;
}


int32 UScoringFunctionLibrary::getLengthStopData(UPARAM(ref) FComboNode & inNode) {
	return inNode.stop_nodes.Num();
}

bool UScoringFunctionLibrary::isTagEqual(AActor * actorA, AActor * actorB) {
	for (auto &tagi : actorA->Tags) {
			for (auto &tagj : actorB->Tags) {
				if (tagi == tagj)
				{
					return true;
				}
			}
	}
	return false;
}

bool UScoringFunctionLibrary::isTagEqual(AActor * actorA, FString tag) {
	if (tag == "ANY")
	{
		return true;
	}
	else if (tag == "NONE")
	{
		//TODO: FIX:
		//This requires an actor class dedicated to None types because an actor wont be passed null..
		return actorA == NULL;
	}
	else if (actorA == NULL) {
		return false;
	}

	for (auto &tagi : actorA->Tags) {
		if (tagi == FName(*tag))
		{
			return true;
		}
	}
	return false;
}

bool UScoringFunctionLibrary::isEqualTemplate(UPARAM(ref) FComboData & comboData, UPARAM(ref) FComboTemplate & comboTemp ) {
	bool isEqualSubj = isTagEqual(comboData.Subject, comboTemp.SubjectTag);
	bool isEqualVerb = comboData.Verb == comboTemp.Verb;
	bool isEqualObj = isTagEqual(comboData.Object, comboTemp.ObjectTag);
	bool isEqualSubjTo = isTagEqual(comboData.SubjectTo, comboTemp.SubjectToTag); 

	//todo: check time diff 
	//This should be adjustable... less then?

	return isEqualSubj && isEqualVerb && isEqualObj && isEqualSubjTo;
}

//Returns when the currentCombo coming in ---> , is equal to comboData which initiated the combo
//												AND It satisfies the template restrictions 
bool UScoringFunctionLibrary::isEqual(UPARAM(ref) FComboData & comboData, UPARAM(ref) FComboTemplate & comboTemp, UPARAM(ref) FComboData & currentCombo)
{

	bool isEqualSubj = isTagEqual(comboData.Subject, comboTemp.SubjectTag);
	bool isEqualVerb = comboData.Verb == comboTemp.Verb;
	bool isEqualObj = isTagEqual(comboData.Object, comboTemp.ObjectTag);
	bool isEqualSubjTo = isTagEqual(comboData.SubjectTo, comboTemp.SubjectToTag); 

	bool isEqualTemp =isEqualSubj && isEqualVerb && isEqualObj && isEqualSubjTo;

	isEqualSubj = !comboTemp.bSubj    || comboData.Subject == currentCombo.Subject;
	isEqualObj  = !comboTemp.bObj     || comboData.Object == currentCombo.Object;
	isEqualSubjTo = !comboTemp.bSubjTo || comboData.SubjectTo == currentCombo.SubjectTo;

	bool isEqualCurr = isEqualSubj && isEqualObj && isEqualSubjTo;

	return isEqualTemp && isEqualCurr;
}


void UScoringFunctionLibrary::getChildrenComboNode(UPARAM(ref) FComboNode & inNode, TArray<FComboNode> &outChildrenNodes) {
	TArray<FComboNode> temp;
	for (auto &childNode : inNode.combo_nodes) {
		temp.Add(*childNode);
	}
	outChildrenNodes = temp;
}


void UScoringFunctionLibrary::getStopNodes(UPARAM(ref) FComboNode & inNode, TArray<FComboTemplate> &outStopNodes) {
	outStopNodes = inNode.stop_nodes;
}
