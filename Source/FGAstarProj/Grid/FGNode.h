#pragma once
#include "Components/BoxComponent.h"
#include "FGNode.generated.h"

UENUM(BlueprintType)
enum class NodeType : uint8 {
	OPEN = 0 UMETA(DisplayName = "OPEN"),
	CLOSED = 1  UMETA(DisplayName = "CLOSED"),
	UNCHECKED = 2     UMETA(DisplayName = "UNCHECKED"),
	BLOCKED = 3     UMETA(DisplayName = "BLOCKED"),
	
};

UCLASS()
class AFGNode : public AActor
{
	GENERATED_BODY()
public:
	AFGNode();
	UPROPERTY(EditAnywhere)
		NodeType NodeType = NodeType::UNCHECKED;

	int XIndex = -1;
	int YIndex = -1;
	bool IsGoal;
	bool IsStart;
	
	FVector Position;
	int GScore = 0;
	int HScore = 0;
	int FScore = 0;

	UPROPERTY()
		TArray<AFGNode*> NeighbourNodes;
	
	
	AFGNode* Parent;

	UPROPERTY(EditAnywhere)
		int TileScore = 0;
	UPROPERTY(EditDefaultsOnly)
		UMaterial* UncheckedM;
	UPROPERTY(EditDefaultsOnly)
		UMaterial* BlockedM;
	UPROPERTY(EditDefaultsOnly)
		UMaterial* StartM;
	UPROPERTY(EditDefaultsOnly)
		UMaterial* GoalM;
	UPROPERTY(EditDefaultsOnly)
		UMaterial* OpenedM;
	UPROPERTY(EditDefaultsOnly)
		UMaterial* ClosedM;
	UPROPERTY(EditDefaultsOnly)
		UMaterial* CorrectM;

	
};