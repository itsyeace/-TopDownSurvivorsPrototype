// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDSurvivorsProtoCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UAttributeComponent;
class ABulletPool;

/**
 *  A controllable top-down perspective character
 */
UCLASS(abstract)
class ATDSurvivorsProtoCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UAttributeComponent* AttributeComp;

public:

	/** Constructor */
	ATDSurvivorsProtoCharacter();

	/** Initialization */
	virtual void BeginPlay() override;

	/** Update */
	virtual void Tick(float DeltaSeconds) override;

	/** Returns the camera component **/
	UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent.Get(); }

	/** Returns the Camera Boom component **/
	USpringArmComponent* GetCameraBoom() const { return CameraBoom.Get(); }

private:

	ABulletPool* BulletPool;

	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRate = 0.2f;

	FTimerHandle FireRateTimerHandle;
};

