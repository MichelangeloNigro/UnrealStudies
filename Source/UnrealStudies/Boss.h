// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Meteor.h"
#include "GameFramework/Character.h"
#include "Boss.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnemyState);

UENUM()
enum EbossStates
{
	Calm1 UMETA(DisplayName= "calm"),
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USoundBase* soundCalm;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USoundBase* FightMusic;
	// Sets default values for this character's properties
	ABoss();
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Meteor")
	bool MeteorOnSoil;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FEnemyState CalmEvent1;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FEnemyState CalmEvent2;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FEnemyState FireEvent;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Meteor")
	FEnemyState MeteorRainEvent;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Fire Attack")
	FEnemyState FireAttack;
	UPROPERTY(EditAnywhere,Category="Fire Attack")
	int fireDamage;
	UPROPERTY(EditAnywhere, Category="Meteor")
	int meteorDamage;
	UPROPERTY(EditAnywhere)
	float pauseBetwenCalm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* gateManager;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float percent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TEnumAsByte<EbossStates> state;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TEnumAsByte<EbossStates> previousstate;
	UFUNCTION(BlueprintCallable,Category="Fire Attack")
	void Fire();
	UFUNCTION(BlueprintCallable)
	void CheckState();
	UFUNCTION(BlueprintCallable, Category="Meteor")
	void MeteorRain();
	UPROPERTY(EditAnywhere, Category="Meteor")
	UClass* meteor;
	UPROPERTY(EditAnywhere, Category="Meteor")
	float minVel;
	UPROPERTY(EditAnywhere, Category="Meteor")
	float maxvel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Meteor")
	int meteors;
	FTimerDelegate TimerDelegate;
	UPROPERTY(EditAnywhere,Category="Fire Attack")
	UParticleSystem* fireFX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Fire Attack")
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
