// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSetBase.h"
#include "TowerAttributeSetBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackSpeedChangedDelegate, float, NewAttackSpeed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackDamageChangedDelegate, float, NewAttackDamage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRangeChangedDelegate, float, NewRange);


/**
 * 
 */
UCLASS()
class TDTEST_API UTowerAttributeSetBase : public UAttributeSetBase
{
	GENERATED_BODY()

public:
	UTowerAttributeSetBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData AttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData Range;
	
	UFUNCTION(BlueprintPure)
	float GetAttackTime() const;

	UFUNCTION(BlueprintPure)
	ATower* GetOwningTower() const;


	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData & Data) override;
	FOnAttackSpeedChangedDelegate OnAttackSpeedChanged;
	FOnAttackSpeedChangedDelegate OnAttackDamageChanged;
	FOnRangeChangedDelegate OnRangeChanged;

};
