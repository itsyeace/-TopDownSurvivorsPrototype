#include "Bullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AttributeComponent.h"
#include "BulletPool.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(15.f);
	CollisionSphere->SetNotifyRigidBodyCollision(true);
	CollisionSphere->BodyInstance.bUseCCD = true;
	RootComponent = CollisionSphere;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = Speed;
	ProjectileMovement->MaxSpeed = Speed;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.f;

}

void ABullet::Activate(FVector Location, FVector Direction)
{
	SetActorLocation(Location);
	SetActorHiddenInGame(false);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ProjectileMovement->Velocity = Direction.GetSafeNormal() * Speed;
	ProjectileMovement->Activate();
	IsActive = true;

	GetWorldTimerManager().SetTimer(BulletTimerHandle, this, &ABullet::OnTimerExpired, 2.0f, false);
}

void ABullet::Deactivate()
{
	SetActorHiddenInGame(true);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ProjectileMovement->StopMovementImmediately();
	ProjectileMovement->Deactivate();
	IsActive = false;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);
	CollisionSphere->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == GetOwner()) return;

	if (UAttributeComponent* AttributeComponent = OtherActor->FindComponentByClass<UAttributeComponent>())
	{
		AttributeComponent->TakeDamage(Damage);
	}

	if (GetOwner() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("I HAVE NO OWNER! I am a stray bullet!"));
	}

	if (ABulletPool* BulletPool = Cast<ABulletPool>(GetOwner()))
	{
		BulletPool->ReturnBullet(this);
	}

	GetWorldTimerManager().ClearTimer(BulletTimerHandle);
}

void ABullet::OnTimerExpired()
{
	ABulletPool* BulletPool = Cast<ABulletPool>(GetOwner());
	if (BulletPool)
	{
		BulletPool->ReturnBullet(this);
	}
}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor || OtherActor == GetOwner()) return;

	if (GetOwner() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("I HAVE NO OWNER! I am a stray bullet!"));
	}

	if (ABulletPool* BulletPool = Cast<ABulletPool>(GetOwner()))
	{
		BulletPool->ReturnBullet(this);
	}

	GetWorldTimerManager().ClearTimer(BulletTimerHandle);
}

