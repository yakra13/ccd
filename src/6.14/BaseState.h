#pragma once

#include "CoreMinimal.h"
#include <ActionRPG/Core/PlayerCharacter.h>
#include <ActionRPG/Core/ActionRPGPlayerController.h>
#include <ActionRPG/IPlayerController.h>
#include <ARPGStateMachine/StateBase.h>
#include "Kismet/GameplayStatics.h"
#include "BaseState.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPG_API UBaseState : public UStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	APlayerCharacter* PlayerRef = nullptr;
	AActionRPGPlayerController* PlayerController = nullptr;
	IIPlayerController* IPlayerController = nullptr;

	virtual bool IsValidEnterState(AActor* owner) override;
	virtual void OnEnterState(AActor* owner) override;
	virtual void TickState(float deltaTime) override;
	virtual void OnExitState() override;

protected:
	virtual void InitPlayerReference(AActor* owner);
	virtual void DoIdleDelegate();
	virtual void DoWalkDelegate();
	virtual void DoDeactivateWalkDelegate();
	virtual void DoDashDelegate();
};
