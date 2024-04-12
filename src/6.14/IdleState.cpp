#include "IdleState.h"
#include <ActionRPG/Core/ActionCharacter.h>
#include "GameFramework/CharacterMovementComponent.h"

bool UIdleState::IsValidEnterState(AActor* owner)
{
	Super::IsValidEnterState(owner);

	return true;
}

void UIdleState::OnEnterState(AActor* owner)
{
	IsDebug = true;
	StateDisplayName = FName(TEXT("Idle State"));

	Super::OnEnterState(owner);

	//Bind delegates that apply to this state
	if (IPlayerController)
	{
		IPlayerController->GetDashDelegate()->AddUObject(this, &UIdleState::DoDashDelegate);
		IPlayerController->GetWalkDelegate()->AddUObject(this, &UIdleState::DoWalkDelegate);
	}
}

void UIdleState::OnExitState()
{
	Super::OnExitState();

	//Remove all bound delegates so they dont fire when not in this state
	IPlayerController->GetDashDelegate()->RemoveAll(this);
	IPlayerController->GetWalkDelegate()->RemoveAll(this);
}

void UIdleState::DoDashDelegate()
{
	PlayerRef->GetStateManager()->SwitchStateByKey("Dash");
}

void UIdleState::DoWalkDelegate()
{
	PlayerRef->GetStateManager()->SwitchStateByKey("Walk");
}

void UIdleState::TickState(float deltaTime)
{
	Super::TickState(deltaTime);
}
