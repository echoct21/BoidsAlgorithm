// Fill out your copyright notice in the Description page of Project Settings.


#include "FlockingManager.h"
#include "Agent.h"
#include "Math/Vector.h"
#include <cmath>

#define AGENT_COUNT 10


void UFlockingManager::Init( UWorld *world, UStaticMeshComponent *mesh ) {
	UE_LOG(LogTemp, Warning, TEXT("MANAGER INIT"));
	World = world;

  float incr = (PI * 2.f) / AGENT_COUNT;
  for( int i = 0; i < AGENT_COUNT; i++ ) {
    if( World != nullptr ) {
      FRotator rotation = FRotator();

      FVector location = FVector();
      location.X = FMath::Sin( incr * i ) * 165.f;
      location.Y = FMath::Cos( incr * i ) * 165.f; // made this Y for a horizontal ring. Also spread out the ring a bit to separate them.
      location.Z = 1000.0; //added a Z location to move it above the surface

      AAgent * agent = World->SpawnActor<AAgent>( location, rotation );
      agent->Init( mesh, i );
      agent->setIndex(i);
      agent->setVelocity(FVector(0.0f,0.0f,0.0f)); // Added initial velocity.
      Agents.Add( agent );
    }
  }
  initialized = true;
}

void UFlockingManager::Flock() {
  //UE_LOG(LogTemp, Warning, TEXT("Flock"));
  for(int i = 0; i < AGENT_COUNT; i++){
    AAgent *boid = Agents[i];
    FVector newVel = boid->getVelocity() + ruleOne(boid)  + ruleTwo(boid)  + ruleThree(boid) + wind(boid) + destination(boid);
    boid->setVelocity(newVel);
  }
}

// Move to center of mass
FVector UFlockingManager::ruleOne(AAgent *boid){
  FVector center = FVector(0.0f, 0.0f, 0.0f);

	for(int i = 0; i < AGENT_COUNT; i++){
    AAgent *bOther = Agents[i];
		if( bOther != boid){
			center = center + bOther->getPosition();
		}
	}

	center = center / (AGENT_COUNT - 1);

  FVector rule1 = (center - boid->getPosition()) / 100;
  //UE_LOG(LogTemp, Warning, TEXT("Moved Boid to: %s"), *rule1.ToString());

	return rule1;
}

// Don't get too close to others
FVector UFlockingManager::ruleTwo(AAgent *boid){
  FVector c  = FVector(0.0f, 0.0f, 0.0f);

	for(int i = 0; i < AGENT_COUNT; i++){
    AAgent *bOther = Agents[i];
		if( bOther != boid ){
			if( abs((bOther->getPosition() - boid->getPosition()).Size()) < 100){ //made this actual code
				c = (c - (bOther->getPosition() - boid->getPosition()))/5;
			}
    }
  }

	return c;
}

// Match velocity with nearby boids
FVector UFlockingManager::ruleThree(AAgent *boid){
  FVector pvJ  = FVector(0.0f, 0.0f, 0.0f);

	for(int i = 0; i < AGENT_COUNT; i++){
    AAgent *bOther = Agents[i];
		if( bOther != boid ){
			pvJ = pvJ + bOther->getVelocity();
		}
  }

	pvJ = pvJ / (AGENT_COUNT - 1);

	return (pvJ - boid->getVelocity()) / 8;
}

FVector UFlockingManager::wind(AAgent *boid){
  FVector wind = FVector(0.5f, 0.0f, 0.0f);

  return wind;
}
	
FVector UFlockingManager::destination(AAgent *boid){
  FVector destination = FVector(1500.0f, 1500.0f, 1500.0);

  return (destination - boid->getPosition()) / 100;
}
