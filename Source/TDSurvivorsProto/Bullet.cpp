#include "Bullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AttributeComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(15.f);
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
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileMovement->Velocity = Direction.GetSafeNormal() * Speed;
	ProjectileMovement->Activate();
}

void ABullet::Deactivate()
{
	SetActorHiddenInGame(true);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ProjectileMovement->StopMovementImmediately();
	ProjectileMovement->Deactivate();
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);
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
		Deactivate();
		UE_LOG(LogTemp, Warning, TEXT("Bullet hit the Player"));
	}
}

