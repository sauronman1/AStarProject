// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FGNode.h"
#include "GameFramework/Actor.h"
#include "FGGridEntity.generated.h"

UCLASS()
class FGASTARPROJ_API AFGGridEntity : public AActor
{
	GENERATED_BODY()
	
public:	
	AFGGridEntity();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	bool HasNewPath;
	UPROPERTY(VisibleAnywhere)
	int CurrentIndex = 0;
	UPROPERTY(VisibleAnywhere)
	int Steps;
	float TotalDistance;
	float CurrentDistance;
	FVector CurrentDestination;
	FVector CurrentLocation;
	
	UPROPERTY()
		TArray<AFGNode*> PathNodes;
	UPROPERTY(EditAnywhere)
		float Speed;
	
	void FollowPath(float DeltaTime);
	void ChangeDestination();
};
