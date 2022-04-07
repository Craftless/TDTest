// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"

UAttributeSetBase::UAttributeSetBase() : Health(200.f), MaxHealth(200.f), Level(0.f), AttributePoints(0.f)
{
    
}

void UAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData & Data) 
{
    Super::PostGameplayEffectExecute(Data);

    Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));
    Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.f, MaxHealth.GetCurrentValue()));
    if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Health))) {
        OnHealthChanged.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue(), Health.GetCurrentValue() == MaxHealth.GetCurrentValue(), PreviousHealth, Data.EffectSpec.GetContext().GetInstigator());
        AActor* Instigator = Data.EffectSpec.GetContext().GetInstigator();
        if (Instigator) {UE_LOG(LogTemp, Warning, TEXT("[%s] is the instigator"), *Instigator -> GetName());}
        else {UE_LOG(LogTemp, Warning, TEXT("Instigator is null"));}
        PreviousHealth = Health.GetCurrentValue();
    }
    if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, MaxHealth))) {
        OnHealthChanged.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue(), Health.GetCurrentValue() == MaxHealth.GetCurrentValue(), PreviousHealth, Data.EffectSpec.GetContext().GetInstigator());
        PreviousHealth = Health.GetCurrentValue();
    }

    if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Experience))) {
        OnExperienceChanged.Broadcast(Experience.GetCurrentValue(), MaxExperience.GetCurrentValue());
    }

    if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, AttributePoints))) {
        OnAttributePointsChanged.Broadcast(AttributePoints.GetCurrentValue());
    }

    if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Level))) {
        OnLevelChanged.Broadcast(Level.GetCurrentValue(), PreviousLevel);
        PreviousLevel = Level.GetCurrentValue();
    }


}

