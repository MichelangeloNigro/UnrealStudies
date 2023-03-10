// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Boss.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "RealMeteor.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMeteorEvent);

UCLASS()
class UNREALSTUDIES_API ARealMeteor : public AActor
{
	GENERATED_BODY()
public:
    // Sets default values for this character's properties
	ARealMeteor();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeteorModel;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= Gameplay)
	float damage;
	FTimerHandle handle2;
	FMeteorEvent onSoil;
	UPROPERTY(BlueprintReadWrite)
	ABoss* spawner;
	void Death();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* coll; 
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void OnTriggerEnter(AActor* overlappedActor, AActor* overlappingActor);
	
	// Called to bind functionality to input
	UFUNCTION(BlueprintCallable, Category = "meshes")
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return MeteorModel; }
	UFUNCTION(BlueprintCallable, Category = "boss")
	FORCEINLINE class ABoss* GetSpawner() const { return spawner; }
	
};
