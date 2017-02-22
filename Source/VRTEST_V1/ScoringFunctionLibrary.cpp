// Fill out your copyright notice in the Description page of Project Settings.

#include "VRTEST_V1.h"
#include "ScoringFunctionLibrary.h"


void UScoringFunctionLibrary::addStopData(UPARAM(ref) FComboNode & inNode, FComboData data, FComboNode &outNode) {
	inNode.stop_nodes.Add(data);
	outNode = inNode;
}

void UScoringFunctionLibrary::addComboNode( UPARAM(ref) FComboNode & inNode, UPARAM(ref) FComboNode & addNode, struct FComboNode &outNode) {
	inNode.combo_nodes.Add(&addNode);
	outNode = inNode;
}


int32 UScoringFunctionLibrary::getLengthStopData(UPARAM(ref) FComboNode & inNode) {
	return inNode.stop_nodes.Num();
}

