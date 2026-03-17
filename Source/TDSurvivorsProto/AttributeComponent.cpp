#include "AttributeComponent.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
}

void UAttributeComponent::TakeDamage(float Amount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0.f, MaxHealth);
	
	if (CurrentHealth <= 0.f)
	{
		OnDeath.Broadcast(GetOwner());
		UE_LOG(LogTemp, Warning, TEXT("Character Is Dead!"));
	}
}

