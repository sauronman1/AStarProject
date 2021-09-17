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
	NodeType NodeType = NodeType::UNCHECKED;

	int XIndex = -1;
	int YIndex = -1;
	bool isGoal;
	
	FVector Position;
	int GScore = 0;
	int HScore = 0;
	int FScore = 0;
	
	TArray<AFGNode*> NeighbourNodes;

	AFGNode* Parent;

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

	void SetNeighbours(int Width, int Height, TArray<AFGNode> NodesList);
};