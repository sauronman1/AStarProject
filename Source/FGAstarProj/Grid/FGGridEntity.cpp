

#include "FGGridEntity.h"

AFGGridEntity::AFGGridEntity()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFGGridEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFGGridEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FollowPath(DeltaTime);
}

void AFGGridEntity::FollowPath(float DeltaTime)
{
	if(HasNewPath)
	{
		CurrentLocation += CurrentDestination * Speed * DeltaTime;
		SetActorLocation(CurrentLocation);
		CurrentDistance = (PathNodes[CurrentIndex % PathNodes.Num()]->GetActorLocation() - CurrentLocation).Size();

		UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentDistance);
		if(CurrentDistance < 120.1f)
		{
			CurrentIndex++;
			if(Steps == CurrentIndex)
				HasNewPath = false;

			ChangeDestination();
		}
	}
}

void AFGGridEntity::ChangeDestination()
{
	CurrentDestination = PathNodes[CurrentIndex % PathNodes.Num()]->GetActorLocation() - GetActorLocation();
	CurrentDestination.Z = CurrentDestination.Z + 120.f;
	CurrentDestination = CurrentDestination.GetSafeNormal();
	
	CurrentLocation = GetActorLocation();
}


