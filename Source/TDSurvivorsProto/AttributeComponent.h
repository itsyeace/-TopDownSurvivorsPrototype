#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, AActor*, DeadActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthChanged, float, MaxHealth, float, CurrentHealth, float, DamageAmount);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TDSURVIVORSPROTO_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float MaxHealth;

	float GetMaxHealth() const { return MaxHealth; }

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	void ProcessDamage(float Amount);
	float GetCurrentHealth() const { return CurrentHealth; }

	bool IsDead() const { return CurrentHealth <= 0.f; }
	bool IsInvincible() const;
	
private:
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth;

	bool bIsInvincible;
};
