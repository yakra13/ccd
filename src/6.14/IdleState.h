#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "IdleState.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPG_API UIdleState : public UBaseState
{
	GENERATED_BODY()

public:
	virtual bool IsValidEnterState(AActor* owner) override;
	virtual void OnEnterState(AActor* owner) override;
	virtual void TickState(float deltaTime) override;
	virtual void OnExitState() override;

protected:
	virtual void DoDashDelegate() override;
	virtual void DoWalkDelegate() override;
};
