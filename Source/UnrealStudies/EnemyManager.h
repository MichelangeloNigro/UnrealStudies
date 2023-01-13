// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"
UENUM()
enum EgameStates
{
	Stealth UMETA(DisplayName= "stealth"),
	Fighting UMETA(DisplayName= "fight"),
	Calm UMETA(DisplayName= "calm"),
	Default UMETA(DisplayName= "default"),
};
UCLASS()
class UNREALSTUDIES_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	USoundBase* soundCalm;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	USoundBase* soundstealth;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	USoundBase* soundFight;
	UAudioComponent* current;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	TArray<AActor*> EnemiesActors;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	TArray<AEnemy*> Enemies;
	UPROPERTY(VisibleAnywhere)
	bool allEnemiesInLevel;
	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<EgameStates> states;
	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<EgameStates> previousState=Default;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void RemoveifDead();
	void addActorsToEnemies();

};
