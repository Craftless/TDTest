// Fill out your copyright notice in the Description page of Project Settings.


#include "GASFunctionLibrary.h"
#include "AbilitySystemComponent.h"

void UGASFunctionLibrary::AddConditionalEffectToSpec(UPARAM(ref) FGameplayEffectSpecHandle& SpecHandleToModify, FGameplayEffectSpecHandle SpecHandleToAdd) 
{
    if (ensure(SpecHandleToModify.Data.Get())) {
        SpecHandleToModify.Data.Get() -> TargetEffectSpecs.Add(SpecHandleToAdd);
    }
}


void UGASFunctionLibrary::AcquireAbility(UAbilitySystemComponent* ASC, TSubclassOf<class UGameplayAbility> AbilityToAcquire, int32 AbilityLevel) 
{
	if (!ASC) return;
	if (AbilityToAcquire) {
		FGameplayAbilitySpecDef SpecDef = FGameplayAbilitySpecDef();
		SpecDef.Ability = AbilityToAcquire;
		FGameplayAbilitySpec Spec = FGameplayAbilitySpec(SpecDef, AbilityLevel);
		ASC -> GiveAbility(Spec);
	}
	ASC -> InitAbilityActorInfo(ASC -> GetOwnerActor(), ASC -> GetOwnerActor());

}
