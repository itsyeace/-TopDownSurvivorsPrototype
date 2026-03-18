#include "BulletPool.h"
#include "Bullet.h"

// Sets default values
ABulletPool::ABulletPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

ABullet* ABulletPool::GetBullet()
{
	if (AvailableBullets.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Pool is Empty. Expand"));
		ExpandPool();
	}

	ABullet* Bullet = AvailableBullets.Last();
	AvailableBullets.Pop();
	ActiveBulletCount++;
	return Bullet;
}

void ABulletPool::ReturnBullet(ABullet* Bullet)
{
	if (!Bullet) return;
	Bullet->Deactivate();
	AvailableBullets.Add(Bullet);
	ActiveBulletCount--;
}

int32 ABulletPool::GetActiveBulletCount() const
{
	UE_LOG(LogTemp, Warning, TEXT("Active Bullets: %d"), ActiveBulletCount);
	return ActiveBulletCount;
	
}

// Called when the game starts or when spawned
void ABulletPool::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < PoolSize; i++)
	{
		ExpandPool();
	}
	
}

// Called every frame
void ABulletPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABulletPool::ExpandPool()
{
	if (!BulletClass) return;

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);
	
	if (Bullet)
	{
		Bullet->Deactivate();
		AvailableBullets.Add(Bullet);
	}
}

