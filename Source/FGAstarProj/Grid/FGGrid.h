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
	virtual void OnConstruction(const FTransform& Transform) override;
	
	AFGNode* CurrentNode;
	AFGNode* GoalNode;
	UPROPERTY()
		TArray<AFGNode*> NodesList;
	bool StartNodeSelected;
	bool GoalNodeSelected;
	bool IsReset;
	float Timer = 5;
	float TileCost;

	UPROPERTY(EditAnywhere)
		int BorderSpace;
	UPROPERTY(EditAnywhere)
		int Width;
	UPROPERTY(EditAnywhere)
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
