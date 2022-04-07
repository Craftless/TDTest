// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSetBase.h"
#include "EnemyAttributeSetBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovementSpeedChangedDelegate, float, NewSpeed);

/**
 * 
 */
UCLASS()
class TDTEST_API UEnemyAttributeSetBase : public UAttributeSetBase
{
	GENERATED_BODY()

public:
	UEnemyAttributeSetBase();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData & Data) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MovementSpeed;

	FOnMovementSpeedChangedDelegate OnMovementSpeedChanged;
	
};
