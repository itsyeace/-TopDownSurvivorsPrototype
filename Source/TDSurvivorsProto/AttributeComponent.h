#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, AActor*, DeadActor);


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

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	float MaxHealth;

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;

	void TakeDamage(float Amount);
	float GetCurrentHealth() const { return CurrentHealth; }
	
private:

	float CurrentHealth;
};
