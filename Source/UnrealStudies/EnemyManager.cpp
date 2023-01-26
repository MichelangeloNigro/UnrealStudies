// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"

#include "EnemyAIController.h"
#include "HealthComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	if(allEnemiesInLevel)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), EnemiesActors);
	}else
	{
		for (auto enem : Enemies)
		{
			EnemiesActors.Add(Cast<AActor>(enem));
		}
	}
	previousState=Default;
}

void AEnemyManager::addActorsToEnemies()
{
	Enemies.Empty();
	for (auto enem : EnemiesActors)
	{
		Enemies.Add(Cast<AEnemy>(enem));
	}
}

void AEnemyManager::RemoveifDead()
{
	for (auto* Element : Enemies)
	{
		if (Element->GetHealthComponent()->dead)
		{
			EnemiesActors.Remove(Cast<AActor>(Element));
		}
	}
	addActorsToEnemies();
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RemoveifDead();
	for (auto enem : Enemies)
	{
		if (Cast<AEnemyAIController>(enem->GetController()))
		{
			if (Cast<AEnemyAIController>(enem->GetController())->GetBlackboardComponent()->GetValueAsBool("SeePlayer"))
			{
				previousState=states;
				states = Fighting;
				if (previousState!=states)
				{
					if (current->IsValidLowLevel())
					{
						current->Stop();

					}
					current=UGameplayStatics::SpawnSound2D(GetWorld(), soundFight);
				}
				return;
			}
		}
	}
	if (Enemies.Num() > 0)
	{
		states = Stealth;
		// FString prev= UEnum::GetValueAsString(previousState);
		// FString cur= UEnum::GetValueAsString(states);
		if (previousState!=states)
		{
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("stealt eral!"));
			if (current->IsValidLowLevel())
			{
				current->Stop();

			}
			current=UGameplayStatics::SpawnSound2D(GetWorld(), soundstealth);
		}
		previousState=states;
	}
	else
	{
		previousState=states;
		states = Calm;
		if (previousState!=states)
		{
			if (current->IsValidLowLevel())
			{
				current->Stop();

			}
			current=UGameplayStatics::SpawnSound2D(GetWorld(), soundCalm);
			OnEnemyAllDeath.Broadcast();
		}
	}
}
