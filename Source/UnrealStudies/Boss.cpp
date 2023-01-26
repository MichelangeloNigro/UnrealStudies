// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"

#include "HealthComponent.h"
#include "Commandlets/EditorCommandlets.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"

// Sets default values
ABoss::ABoss()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void ABoss::Fire()
{
	FireAttack.Broadcast();
	FCollisionQueryParams Params;
	// Ignore the enemy's pawn
	AActor* Myself = Cast<AActor>(this);
	Params.AddIgnoredActor(Myself);

	FCollisionShape CollShape = FCollisionShape::MakeSphere(100);

	FVector Start = GetActorLocation() + FVector(0, 0, 50);
	FVector End = Start + (GetActorForwardVector() * 3000);
	FHitResult Hit;
	UGameplayStatics::SpawnSound2D(GetWorld(), SoundFire);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), fireFX, GetActorLocation(), GetActorRotation());
	bool bHit = GetWorld()->SweepSingleByChannel(Hit, Start, End, FQuat::Identity, ECC_Pawn, CollShape, Params);

	if (bHit)
	{
		ATP_ThirdPersonCharacter* HitPlayer = Cast<ATP_ThirdPersonCharacter>(Hit.Actor.Get());

		if (HitPlayer)
		{
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Hit! Player"));
			HitPlayer->GetHealthComponent()->GetDamage(fireDamage);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Hit! " + Hit.Actor.Get()->GetName()));
		}
	}
}

void ABoss::CheckState()
{
	previousstate = state;
	float curHealth = GetHealthComponent()->Health;
	float maxHealth = GetHealthComponent()->HealthMaxValue;
	percent = (curHealth * 100) / maxHealth;
	if (70 > percent && 50 < percent)
	{
		state = EbossStates::MeteorRain;
		if (previousstate != EbossStates::MeteorRain)
		{
			CalmEvent2.Broadcast();
			GetWorld()->GetTimerManager().SetTimer(handle, TimerDelegate, pauseBetwenCalm, false);
		}
	}
	else
	{
		state = EbossStates::FireCircle;
		if (previousstate != EbossStates::FireCircle)
		{
			FireEvent.Broadcast();
		}
	}
}

void ABoss::MeteorRain(UClass* meteor)
{
	float rand = FMath::FRandRange(0, 360);
	float degree = 360 / meteors;
	for (int i = 0; i < meteors + 1; i++)
	{
		FActorSpawnParameters SpawnInfo;
		FRotator rot = FRotator(0, 0, rand + (degree * i));
		AActor* temp = GetWorld()->SpawnActor<AActor>(meteor, GetActorLocation(), rot);
		FVector speed;
		UGameplayStatics::SuggestProjectileVelocity_CustomArc(GetWorld(), speed, temp->GetActorLocation(),
		                                                      temp->GetActorForwardVector() * FMath::FRandRange(2, 10));
		
		if (Cast<UActorComponents>(temp))
		{
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, Cast<UStaticMesh>(temp)->GetName());
			

		}else
		{
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("fail"));

		}
	}
}

void ABoss::Death()
{
	GetCharacterMovement()->MaxWalkSpeed = 0.0f;
	HealthComponent->OnHealtToZero.RemoveDynamic(this, &ABoss::Death);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Destroy();
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnHealtToZero.AddDynamic(this, &ABoss::Death);
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
