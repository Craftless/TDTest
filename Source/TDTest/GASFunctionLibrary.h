// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayEffectTypes.h"
#include "GameplayEffect.h"
#include "GASFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TDTEST_API UGASFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void AddConditionalEffectToSpec(UPARAM(ref) FGameplayEffectSpecHandle& SpecHandleToModify, FGameplayEffectSpecHandle SpecHandleToAdd);
	UFUNCTION(BlueprintCallable)
	static void AcquireAbility(class UAbilitySystemComponent* ASC, TSubclassOf<class UGameplayAbility> AbilityToAcquire, int32 AbilityLevel = 1);
};
