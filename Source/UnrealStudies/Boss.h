// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Boss.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnemyState);

UCLASS()
class UNREALSTUDIES_API ABoss : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABoss();
	UPROPERTY(BlueprintAssignable)
	FEnemyState CalmState1;
	UPROPERTY(BlueprintAssignable)
	FEnemyState CalmState2;
	UPROPERTY(BlueprintAssignable)
	FEnemyState fireball;
	UPROPERTY(BlueprintAssignable)
	FEnemyState MeteorRainEvent;

	UPROPERTY(EditAnywhere)
	int fireDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;
	UFUNCTION(BlueprintCallable, Category = "Health")
	FORCEINLINE class UHealthComponent* GetHealthComponent() const { return HealthComponent; }
	void Fire();
	void MeteorRain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
