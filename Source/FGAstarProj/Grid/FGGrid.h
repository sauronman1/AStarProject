// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FGNode.h"
#include "GameFramework/Actor.h"
#include "FGGrid.generated.h"

UCLASS()
class FGASTARPROJ_API AFGGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGGrid();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	AFGNode* CurrentNode;
	AFGNode* GoalNode;
	TArray<AFGNode*> NodesList;
	bool StartNodeSelected;
	bool GoalNodeSelected;
	bool IsReset;
	float Timer;
	
	UPROPERTY(EditDefaultsOnly)
		int Width;
	UPROPERTY(EditDefaultsOnly)
		int Height;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AFGNode> NodeClass;
	
	void MakeGrid();
	void ResetGrid();
	void GetNeighbours(int X, int Y);
	void FindPath();
	int GetHScore(int X, int Y);
	bool HasOpenNodes();

};
