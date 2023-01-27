// Fill out your copyright notice in the Description page of Project Settings.


#include "RealMeteor.h"

#include "Components/BoxComponent.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"

// Sets default values
ARealMeteor::ARealMeteor()
{
	MeteorModel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeteorModel"));
	coll = CreateDefaultSubobject<UBoxComponent>(TEXT("UBoxComponent"));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ARealMeteor::OnTriggerEnter(AActor* overlappedActor, AActor* overlappingActor)
{
	if (Cast<ATP_ThirdPersonCharacter>(overlappingActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Hit!"));
		Cast<ATP_ThirdPersonCharacter>(overlappingActor)->GetHealthComponent()->GetDamage(spawner->meteorDamage);
		onSoil.Clear();
		Destroy();
	}
	
}

void ARealMeteor::Death()
{
	onSoil.Clear();
	Destroy();
}

// Called when the game starts or when spawned
void ARealMeteor::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(handle2,this, &ARealMeteor::Death , 10, false);
	OnActorBeginOverlap.AddDynamic(this, &ARealMeteor::OnTriggerEnter);
	
}

// Called every frame
void ARealMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
