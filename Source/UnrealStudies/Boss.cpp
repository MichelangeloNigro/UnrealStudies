// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"

#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"

// Sets default values
ABoss::ABoss()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABoss::Fire()
{
	FCollisionQueryParams Params;
	// Ignore the enemy's pawn
	AActor* Myself = Cast<AActor>(this);
	Params.AddIgnoredActor(Myself);
	
	FCollisionShape CollShape = FCollisionShape::MakeSphere(100);
	
	FVector ZForward = GetActorLocation() ;
	FVector Start = ZForward;
	FVector End = Start + (GetActorForwardVector()*3000);
	
	FHitResult Hit;
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), fireFX, GetActorLocation());
	UGameplayStatics::SpawnSound2D(GetWorld(), SoundFire);
	bool bHit = GetWorld()->SweepSingleByChannel(Hit, Start, End, FQuat::Identity, ECC_Pawn, CollShape, Params);
	
	if (bHit) {
		ATP_ThirdPersonCharacter* HitPlayer = Cast<ATP_ThirdPersonCharacter>(Hit.Actor.Get());
	
		if (HitPlayer) {
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Hit! Player"));
			HitPlayer->GetHealthComponent()->GetDamage(fireDamage);
		} else {
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Hit! " + Hit.Actor.Get()->GetName()));
		}		
	}
}

void ABoss::CheckState()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.2f, FColor::Emerald, TEXT("checking"));
	previousstate = state;
	float curHealth = GetHealthComponent()->Health;
	float maxHealth = GetHealthComponent()->HealthMaxValue;
	float percent = (curHealth * 100) / maxHealth;
	if (percent > 70 || percent < 50)
	{
		state = FireCircle;
		if (previousstate != FireCircle)
		{
			FireEvent.Broadcast();
		}
		return;
	}else
	{
		state = EbossStates::MeteorRain;
		if (previousstate!=EbossStates::MeteorRain)
		{
			CalmEvent2.Broadcast();
			GetWorldTimerManager().SetTimer(handle,TimerDelegate , pauseBetwenCalm, false);

			
		}
		return;
	}
}

void ABoss::MeteorRain()
{
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();
	TimerDelegate.BindLambda([&]()
	{
		MeteorRainEvent.Broadcast();
	});
}


// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
