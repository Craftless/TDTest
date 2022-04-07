// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnHealthChangedDelegate, float, CurrentHealth, float, MaxHealth, bool, FullHealth, float, PreviousHealth, AActor*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnExperienceChangedDelegate, float, CurrentExperience, float, MaxExperience);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelChangedDelegate, float, CurrentLevel, float, PreviousLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributePointsChangedDelegate, float, CurrentAttributePoints);


// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class TDTEST_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAttributeSetBase();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Health)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxHealth)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData HealthRegen;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, HealthRegen)
	float PreviousHealth;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData Experience;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Experience)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MaxExperience;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxExperience)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Level)
	float PreviousLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData AttributePoints;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, AttributePoints)

	
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData & Data) override;
	FOnHealthChangedDelegate OnHealthChanged;
	FOnExperienceChangedDelegate OnExperienceChanged;
	FOnLevelChangedDelegate OnLevelChanged;
	FOnAttributePointsChangedDelegate OnAttributePointsChanged;


};
