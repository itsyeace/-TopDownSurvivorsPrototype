#include "AttributeComponent.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	bIsInvincible = false;
}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
}

void UAttributeComponent::ProcessDamage(float Amount)
{
	if (IsDead()) return;
	if (Amount <= 0) return;
	if (IsInvincible()) return; 

	CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0.f, MaxHealth);
	OnHealthChanged.Broadcast(MaxHealth, CurrentHealth, Amount);
	
	if (IsDead())
	{
		OnDeath.Broadcast(GetOwner());
		UE_LOG(LogTemp, Warning, TEXT("Character Is Dead!"));
	}
}

bool UAttributeComponent::IsInvincible() const
{
	return bIsInvincible;
}

