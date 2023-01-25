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
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

}

void ABoss::Fire()
{
	FCollisionQueryParams Params;
	// Ignore the enemy's pawn
	AActor* Myself = Cast<AActor>(this);
	Params.AddIgnoredActor(Myself);

	float WeaponRange = WeaponSlot.Range;
	float WeaponOffset = WeaponSlot.Offset;
	float WeaponRadius = WeaponSlot.HitRadius;

	FCollisionShape CollShape = FCollisionShape::MakeSphere(WeaponRadius);

	FVector ZForward = FVector::UpVector * AimOffset;
	FVector Start = WeaponMesh->GetComponentLocation()+ ZForward + (WeaponMesh->GetForwardVector() * WeaponOffset);
	FVector End = Start + (GetActorForwardVector() * WeaponRange);

	FHitResult Hit;

	bool bHit = GetWorld()->SweepSingleByChannel(Hit, Start, End, FQuat::Identity, ECC_Pawn, CollShape, Params);
	OnCharacterTraceLine.Broadcast();

	if (bHit) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponSlot.HitEFX, Hit.ImpactPoint);
		ATP_ThirdPersonCharacter* HitPlayer = Cast<ATP_ThirdPersonCharacter>(Hit.Actor.Get());

		if (HitPlayer) {
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Hit! Player"));
			HitPlayer->GetHealthComponent()->GetDamage(fireDamage);
		} else {
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Hit! " + Hit.Actor.Get()->GetName()));
		}		
	}
}

void ABoss::MeteorRain()
{
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

