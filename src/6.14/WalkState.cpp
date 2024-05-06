#include "WalkState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include <NiagaraFunctionLibrary.h>

bool UWalkState::IsValidEnterState(AActor* owner)
{
	// Note: handles PlayerRef creation, always returns false.
	Super::IsValidEnterState(owner);

	return true;
}

void UWalkState::OnEnterState(AActor* owner)
{
	IsDebug = true;
	StateDisplayName = FName(TEXT("Walk State"));

	Super::OnEnterState(owner);

	//Bind delegates that apply to this state
	if (IPlayerController)
	{
		IPlayerController->GetDashDelegate()->AddUObject(this, &UWalkState::DoDashDelegate);
		IPlayerController->GetIdleDelegate()->AddUObject(this, &UWalkState::DoIdleDelegate);
		IPlayerController->GetWalkDelegate()->AddUObject(this, &UWalkState::DoWalkDelegate);
		IPlayerController->GetDeactivateWalkDelegate()->AddUObject(this, &UWalkState::DoDeactivateWalkDelegate);
	}

	DoWalkDelegate();
}

void UWalkState::OnExitState()
{
	Super::OnExitState();

	IPlayerController->GetDashDelegate()->RemoveAll(this);
	IPlayerController->GetIdleDelegate()->RemoveAll(this);
	IPlayerController->GetWalkDelegate()->RemoveAll(this);
	IPlayerController->GetDeactivateWalkDelegate()->RemoveAll(this);
}

void UWalkState::TickState(float deltaTime)
{
	if (PlayerController->GetPawn()->GetMovementComponent()->Velocity == FVector::Zero())
	{
		PlayerRef->GetStateManager()->SwitchStateByKey("Idle");
	}
}

void UWalkState::DoDashDelegate()
{
	PlayerRef->GetStateManager()->SwitchStateByKey("Dash");
}

void UWalkState::DoIdleDelegate()
{
	PlayerRef->GetStateManager()->SwitchStateByKey("Idle");
}

void UWalkState::DoWalkDelegate()
{
	//everytime you click this will happen

	// We look for the location in the world where the player has pressed the input
	FHitResult hit;
	
	// If we hit a surface, cache the location
	if (PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, hit))
	{
		//TODO: stored for picking things up
		//TODO: if clicked on NPC
		PlayerController->SetHitActor(hit.GetActor());
		PlayerController->SetCachedDestination(hit.Location);
	}

	//increase follow time which represents how long you've held the button
	//with a small grace window (ie quick double clicks are considered the same click
	//as the dodeactivatewalk will skip execution if 
	PlayerController->FollowTime += GetWorld()->GetDeltaSeconds();

	// Move towards mouse pointer or touch
	if (PlayerRef != nullptr)
	{
		FVector worldDirection = (PlayerController->GetCachedDestination() - PlayerRef->GetActorLocation()).GetSafeNormal();
		PlayerRef->AddMovementInput(worldDirection, 1.0, false);
	}
}

void UWalkState::DoDeactivateWalkDelegate()
{
	if (PlayerController->FollowTime <= PlayerController->ShortPressThreshold)
	{
		bool itemClicked = PlayerController->GetHitActor()->ActorHasTag(TEXT("Hovered"));
		//if clicked on an pickupable item set as pick up target else set it to nullptr (no pickup target)
		PlayerRef->SetPickupTarget(itemClicked ? PlayerController->GetHitActor() : nullptr);
		//if its already in range pick it up and do not move
		if (PlayerRef->PickUpItem())
		{
			//TODO: when u pick up an item should it cancel move state and put you in idle? probably
			return;
		}

		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(PlayerController, PlayerController->GetCachedDestination());

		//Do not show the click FX if an item was clicked
		if (PlayerController->ShowCursorEffect && !itemClicked)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(PlayerController, 
														   PlayerController->FXCursor, 
														   PlayerController->GetCachedDestination(),
														   FRotator::ZeroRotator, 
														   FVector(1.f, 1.f, 1.f),
														   true,
														   true, 
														   ENCPoolMethod::None, 
														   true);
		}
	}

	PlayerController->FollowTime = 0.0f;
}
