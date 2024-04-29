#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "DashState.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPG_API UDashState : public UBaseState
{
	GENERATED_BODY()
	
private:
	float elapsedDashTime;
	FVector dashDirection;

public:
	virtual bool IsValidEnterState(AActor* owner) override;
	virtual void OnEnterState(AActor* owner) override;
	virtual void TickState(float deltaTime) override;
	virtual void OnExitState() override;

	float DashSpeed = 20.0f;
	double DashDuration = 0.1f;
};
