#include "Enemy.h"
#include "AttributeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComponent"));

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(RootComponent);

	GetCharacterMovement()->MaxWalkSpeed = 300.f;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	AttributeComponent->OnDeath.AddDynamic(this, &AEnemy::HandleDeath);
	PlayerPawn = Cast<ACharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn) return;
	FVector Direction = (PlayerPawn->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	AddMovementInput(Direction, MoveSpeed);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::HandleDeath(AActor* DeadActor)
{
	UE_LOG(LogTemp, Warning, TEXT("The enemy %s has died!"), *GetName());
}

void AEnemy::Activate(FVector Location)
{
	SetActorHiddenInGame(false);
	SetActorLocation(Location);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void AEnemy::Deactivate()
{
	SetActorHiddenInGame(true);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();
}

void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	if (OtherActor == PlayerPawn)
	{
		if (UAttributeComponent* PlayerAttributeComponent = OtherActor->FindComponentByClass<UAttributeComponent>())
		{
			PlayerAttributeComponent->TakeDamage(AttackDamage);
		}
	}
}

