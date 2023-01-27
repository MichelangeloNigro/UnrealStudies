// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Meteor.generated.h"

UCLASS()
class UNREALSTUDIES_API AMeteor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMeteor();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeteorModel;
	UBoxComponent* collider;
	UFUNCTION()
	void OnTriggerEnter(AActor* overlappedActor, AActor* overlappingActor);   
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= Gameplay)
	float damage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	UFUNCTION(BlueprintCallable, Category = "Health")
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return MeteorModel; }

};
