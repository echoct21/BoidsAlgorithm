// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlockingManager.h"
#include "FlockingGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FLOCKING_API AFlockingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	AFlockingGameModeBase();

	public:
		UPROPERTY(EditAnywhere, meta=(ClampMin="-10.0", ClampMax="10.0"))
    	float Speed;
		
	private:

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent * AgentMesh;

	UPROPERTY() UFlockingManager *Manager;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
