// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FlockingManager.generated.h"

/**
 * 
 */
UCLASS()
class FLOCKING_API UFlockingManager : public UObject
{
	public:
	GENERATED_BODY()

	void Init( UWorld *world, UStaticMeshComponent *mesh );
	void Flock();

private:
	UWorld *World;	
	bool initialized;
	TArray<class AAgent *> Agents;

	FVector ruleOne(AAgent *boid);

	FVector ruleTwo(AAgent *boid);
	
	FVector ruleThree(AAgent *boid);

	FVector wind(AAgent *boid);
	
	FVector destination(AAgent *boid);
};
