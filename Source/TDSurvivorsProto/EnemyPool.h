#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyPool.generated.h"

class AEnemy;

UCLASS()
class TDSURVIVORSPROTO_API AEnemyPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyPool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	AEnemy* GetEnemy(FVector Location);

	void ReturnEnemy(AEnemy* Enemy);

	int32 EnemyPoolSize = 50;

	TSubclassOf<AEnemy> EnemyClass;

private:

	TArray<AEnemy*> AvailableEnemies;

	void ExpandPool();

};
