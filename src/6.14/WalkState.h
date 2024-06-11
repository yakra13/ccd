#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "WalkPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPG_API UWalkState : public UBaseState
{
	GENERATED_BODY()

protected:
	virtual void DoDashDelegate() override;
	virtual void DoIdleDelegate() override;
	virtual void DoWalkDelegate() override;
	virtual void DoDeactivateWalkDelegate() override;

public:
	virtual bool IsValidEnterState(AActor* owner) override;
	virtual void OnEnterState(AActor* owner) override;
	virtual void TickState(float deltaTime) override;
	virtual void OnExitState() override;
};
