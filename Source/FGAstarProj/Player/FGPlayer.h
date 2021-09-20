#pragma once
#include "FGPlayer.generated.h"

class UCameraComponent;
class AFGGrid;

UCLASS()
class AFGPlayer : public APawn
{
	GENERATED_BODY()
public:
	AFGPlayer();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	UCameraComponent* CameraComponent = nullptr;
	UPROPERTY(BlueprintReadWrite, Category = "Player")
	AFGGrid* CurrentGridActor = nullptr;
	
	void SelectNode();
};