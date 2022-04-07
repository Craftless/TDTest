// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerAttributeSetBase.h"
#include "Tower.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"



UTowerAttributeSetBase::UTowerAttributeSetBase() : AttackSpeed(1.f), Range(300.f)
{
    
}


ATower* UTowerAttributeSetBase::GetOwningTower() const
{
    return Cast<ATower>(GetOwningActor());
}

void UTowerAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData & Data) 
{
    Super::PostGameplayEffectExecute(Data);
    if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UTowerAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UTowerAttributeSetBase, AttackSpeed))) {
        OnAttackSpeedChanged.Broadcast(AttackSpeed.GetCurrentValue());
    }
    if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UTowerAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UTowerAttributeSetBase, AttackDamage))) {
        OnAttackDamageChanged.Broadcast(AttackDamage.GetCurrentValue());
    }
    if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UTowerAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UTowerAttributeSetBase, Range))) {
        OnRangeChanged.Broadcast(Range.GetCurrentValue());
    }
}

float UTowerAttributeSetBase::GetAttackTime() const
{
    ATower* Tower = GetOwningTower();
    float BaseAttackTime = Tower ? (Tower -> GetBaseAttackTime()) : 1.5f;
    return BaseAttackTime / (1 + (AttackSpeed.GetCurrentValue() / 10));
}

