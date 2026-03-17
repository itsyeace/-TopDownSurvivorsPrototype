#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletPool.generated.h"

class ABullet;

UCLASS()
class TDSURVIVORSPROTO_API ABulletPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletPool();

	UFUNCTION(BlueprintCallable)
	ABullet* GetBullet();

	void ReturnBullet(ABullet* Bullet);

	UPROPERTY(EditDefaultsOnly, Category = "Pool")
	TSubclassOf<ABullet> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = "Pool")
	int32 PoolSize = 30;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TArray<ABullet*> AvailableBullets;

	void ExpandPool();
};
