// Fill out your copyright notice in the Description page of Project Settings.


#include "Meteor.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"

// Sets default values
AMeteor::AMeteor()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeteorModel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeteorModel"));
	RootComponent=CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	collider=CreateDefaultSubobject<UBoxComponent>(TEXT("UBoxComponent"));


}

void AMeteor::OnTriggerEnter(AActor* overlappedActor, AActor* overlappingActor)
{
	if(Cast<ATP_ThirdPersonCharacter>(overlappingActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Hit!"));
	}
}

// Called when the game starts or when spawned
void AMeteor::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this,&AMeteor::OnTriggerEnter);
	
}

// Called every frame
void AMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

