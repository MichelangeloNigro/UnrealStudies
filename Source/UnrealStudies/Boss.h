// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "GameFramework/Character.h"
#include "Boss.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnemyState);
UENUM()
enum EbossStates
{
	Calm UMETA(DisplayName= "calm"),
	FireCircle UMETA(DisplayName= "fireCircle"),
	Calm2 UMETA(DisplayName= "calm2"),
	MeteorRain UMETA(DisplayName= "MeteorRain"),
};
UCLASS()
class UNREALSTUDIES_API ABoss : public ACharacter
{
	GENERATED_BODY()

public:
	FTimerHandle handle;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	USoundBase* soundCalm;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	USoundBase* FightMusic;
	// Sets default values for this character's properties
	ABoss();
	UPROPERTY(BlueprintAssignable)
	FEnemyState CalmEvent1;
	UPROPERTY(BlueprintAssignable)
	FEnemyState CalmEvent2;
	UPROPERTY(BlueprintAssignable)
	FEnemyState FireEvent;
	UPROPERTY(BlueprintAssignable)
	FEnemyState MeteorRainEvent;
UPROPERTY(EditAnywhere)
	float divider;
	UPROPERTY(EditAnywhere)
	int fireDamage;

	UPROPERTY(EditAnywhere)
	float pauseBetwenCalm;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AActor* gateManager;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TEnumAsByte<EbossStates> state;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TEnumAsByte<EbossStates> previousstate;
	UFUNCTION(BlueprintCallable)
	void Fire();
	UFUNCTION(BlueprintCallable)
	void CheckState();
	void MeteorRain();
	FTimerDelegate TimerDelegate;
	UPROPERTY(EditAnywhere)
	UParticleSystem* fireFX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* SoundFire;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
    	UHealthComponent* HealthComponent;
    	UFUNCTION(BlueprintCallable, Category = "Health")
    	FORCEINLINE class UHealthComponent* GetHealthComponent() const { return HealthComponent; }
	void Death();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
