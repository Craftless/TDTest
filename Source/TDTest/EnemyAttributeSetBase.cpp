// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttributeSetBase.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"


UEnemyAttributeSetBase::UEnemyAttributeSetBase() : MovementSpeed(100.f)
{
    
}

void UEnemyAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData & Data) 
{
    Super::PostGameplayEffectExecute(Data);
    if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UEnemyAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UEnemyAttributeSetBase, MovementSpeed))) {
        
        OnMovementSpeedChanged.Broadcast(MovementSpeed.GetCurrentValue());
    }
}
