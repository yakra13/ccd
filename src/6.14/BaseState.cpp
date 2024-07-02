#include "BaseState.h"

void UBaseState::InitPlayerReference(AActor* owner)
{
	if (!PlayerRef)
	{
		PlayerRef = Cast<APlayerCharacter>(owner);
	}

	if (!PlayerController)
	{
		PlayerController = Cast<AActionRPGPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	}

	if (!IPlayerController)
	{
		IPlayerController = Cast<IIPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	}
}

bool UBaseState::IsValidEnterState(AActor* owner)
{
	if (!PlayerRef)
		InitPlayerReference(owner);

	return Super::IsValidEnterState(owner);
}

void UBaseState::OnEnterState(AActor* owner)
{
	Super::OnEnterState(owner);
}

void UBaseState::TickState(float deltaTime)
{
}

void UBaseState::OnExitState()
{
	Super::OnExitState();
}

void UBaseState::DoDashDelegate()
{
}

void UBaseState::DoIdleDelegate()
{
}

void UBaseState::DoWalkDelegate()
{
}

void UBaseState::DoDeactivateWalkDelegate()
{
}
