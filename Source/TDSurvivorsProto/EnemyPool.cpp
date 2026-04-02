#include "EnemyPool.h"
#include "Enemy.h"

// Sets default values
AEnemyPool::AEnemyPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyPool::BeginPlay()
{
	Super::BeginPlay();

	ExpandPool();
	
}

// Called every frame
void AEnemyPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AEnemy* AEnemyPool::GetEnemy(FVector Location)
{
	if (AvailableEnemies.IsEmpty())
	{
		ExpandPool();
	}
	AEnemy* Enemy = AvailableEnemies.Last();
	AvailableEnemies.Pop();
	Enemy->Activate(Location);
	return Enemy;
}

void AEnemyPool::ReturnEnemy(AEnemy* Enemy)
{
	if (!Enemy) return;
	Enemy->Deactivate();
	AvailableEnemies.Add(Enemy);
}

void AEnemyPool::ExpandPool()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AEnemy* Enemy = GetWorld()->SpawnActor<AEnemy>(EnemyClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

	if (!Enemy) return;

	Enemy->SetOwner(this);
	Enemy->Deactivate();
	AvailableEnemies.Add(Enemy);
}

