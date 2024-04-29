#include "DashState.h"
#include "GameFramework/Character.h"

bool UDashState::IsValidEnterState(AActor* owner)
{
	// Note: handles PlayerRef creation, always returns false.
	Super::IsValidEnterState(owner);

	return PlayerRef->GetDashable();
}

void UDashState::OnEnterState(AActor* owner)
{
	PlayerRef->BeginDashCooldown();
	CanTickState = true;
	//TODO: debugging to display state name
	IsDebug = true;
	StateDisplayName = FName(TEXT("Dash State"));

	elapsedDashTime = 0.0f;

	Super::OnEnterState(owner);

	FHitResult hit;
	if (PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, hit))
	{
		FVector dir = (hit.Location - PlayerRef->GetActorLocation());
		dashDirection = dir.GetSafeNormal2D();
	}
}

void UDashState::TickState(float deltaTime)
{
	Super::TickState(deltaTime);
	UE_LOG(LogTemp, Warning, TEXT("direciton: %s"), *dashDirection.ToString());

	FHitResult hit;
	PlayerRef->AddActorWorldOffset(dashDirection * DashSpeed, true, &hit, ETeleportType::TeleportPhysics);
	
	if (elapsedDashTime > DashDuration || hit.bBlockingHit)
	{
		PlayerRef->GetStateManager()->SwitchStateByKey("Walk");
	}

	elapsedDashTime += deltaTime;
}

void UDashState::OnExitState()
{
	Super::OnExitState();
}

