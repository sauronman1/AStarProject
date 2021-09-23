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
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	FVector InputVector;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	UCameraComponent* CameraComponent = nullptr;
	UPROPERTY(BlueprintReadWrite, Category = "Player")
	AFGGrid* CurrentGridActor = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
	float HorizontalMovementSpeed = 3000.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
	float VerticalMovementSpeed = 1000.0f;
	
	void SelectNode();
	void EditBlockNodes();
	void UpdateMovement(float DeltaTime);
	void Handle_Forward(float Value);
	void Handle_Right(float Value);
	void Handle_Up(float Value);
};