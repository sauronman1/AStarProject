#include "FGPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "FGAstarProj/Grid/FGGRid.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"

AFGPlayer::AFGPlayer()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);
	
}

void AFGPlayer::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> AllGridActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFGGrid::StaticClass(), AllGridActors);

	if (AllGridActors.Num() > 0)
	{
		CurrentGridActor = Cast<AFGGrid>(AllGridActors[0]);
	}
}

void AFGPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateMovement(DeltaSeconds);

}


void AFGPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAction(TEXT("Select"), IE_Pressed, this, &AFGPlayer::SelectNode);
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AFGPlayer::Handle_Forward);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AFGPlayer::Handle_Right);
	PlayerInputComponent->BindAxis(TEXT("Up"), this, &AFGPlayer::Handle_Up);}

void AFGPlayer::SelectNode()
{
	if(CurrentGridActor->Timer > 5)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());

		if (CurrentGridActor == nullptr) {return;}
		if (PlayerController == nullptr) {return;}

		float MouseX = 0.f;
		float MouseY = 0.f;

		// PlayerController->GetMousePosition(MouseX, MouseY);
		PlayerController->bShowMouseCursor = true;
		// FVector MouseWorldLocation;
		// FVector MouseDirection;
		//
		// PlayerController->DeprojectScreenPositionToWorld(MouseX, MouseY, MouseWorldLocation, MouseDirection);

	
		TArray<AActor*> ActorsToIgnore;
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_WorldDynamic, false, HitResult);

		bool IsHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), GetActorLocation(),  HitResult.Location, UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Blue, FLinearColor::White, 5.f);
	
		if(IsHit)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Trace Hit: %s"), *HitResult.Actor->GetName()));
			AFGNode* SelectedNode = Cast<AFGNode>(HitResult.Actor);
			if(SelectedNode == nullptr || SelectedNode->NodeType == NodeType::BLOCKED) {return;}

			if(!CurrentGridActor->StartNodeSelected)
			{
				SelectedNode->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0, SelectedNode->OpenedM);
				SelectedNode->NodeType = NodeType::OPEN;
				SelectedNode->IsStart = true;
				CurrentGridActor->CurrentNode = SelectedNode;
				CurrentGridActor->StartNodeSelected = true;
			
			}
			else if(!CurrentGridActor->GoalNodeSelected && CurrentGridActor->StartNodeSelected && SelectedNode->IsStart != true)
			{
				SelectedNode->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0, SelectedNode->GoalM);
				SelectedNode->NodeType = NodeType::UNCHECKED;
				SelectedNode->IsGoal = true;
				CurrentGridActor->GoalNode = SelectedNode;
				CurrentGridActor->GoalNodeSelected = true;
			}
		}
	}
}

void AFGPlayer::UpdateMovement(float DeltaTime)
{
	if (!InputVector.IsNearlyZero())
	{
		FVector HorizontalMovement = GetActorTransform().TransformVectorNoScale(FVector(InputVector.X, InputVector.Y, 0.0f).GetSafeNormal());
		FVector VerticalMovement = FVector(0, 0, InputVector.Z);

		AddActorWorldOffset(HorizontalMovement * HorizontalMovementSpeed * DeltaTime);
		AddActorWorldOffset(VerticalMovement * VerticalMovementSpeed * DeltaTime);
	}

	InputVector = FVector::ZeroVector;
}

void AFGPlayer::Handle_Forward(float Value)
{
	InputVector.X += Value;
}

void AFGPlayer::Handle_Right(float Value)
{
	InputVector.Y += Value;
}

void AFGPlayer::Handle_Up(float Value)
{
	InputVector.Z += Value;
}