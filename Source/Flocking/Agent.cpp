
// Fill out your copyright notice in the Description page of Project Settings.


#include "Agent.h"
#include "FlockingGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAgent::AAgent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AgentMesh"));	
	RootComponent = Mesh;
	Velocity = FVector(0.f);
}

// Called when the game starts or when spawned
void AAgent::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAgent::Init( UStaticMeshComponent *mesh, int id ) {
	UE_LOG(LogTemp, Warning, TEXT("Agent initialized.") );
	Mesh->SetStaticMesh( mesh->GetStaticMesh() );
}

// Called every frame
void AAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AFlockingGameModeBase *gmb = Cast<AFlockingGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
  	Velocity.Z = gmb->Speed;

	FVector loc = GetActorLocation();
	SetActorLocation( loc + Velocity );
	FVector newpos = loc + Velocity;
	//UE_LOG(LogTemp, Warning, TEXT("Moved Boid to: %s"), *newpos.ToString());
}

FVector AAgent::getVelocity(){
	return Velocity;
}

void AAgent::setVelocity(FVector vel){
	Velocity = vel;
}

FVector AAgent::getPosition(){
	return GetActorLocation();
}

void AAgent::setPosition(FVector pos){
	SetActorLocation(pos);
}

int AAgent::getIndex(){
	return index;
}

void AAgent::setIndex(int i){
	index = i;
}

