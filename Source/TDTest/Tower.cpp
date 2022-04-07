// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "TowerAttributeSetBase.h"
#include "Components/DecalComponent.h"

// Sets default values
ATower::ATower()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(FName("SystemComponent"));
	TowerAttributeSetBase = CreateDefaultSubobject<UTowerAttributeSetBase>(FName("TowerAttributeSetBase"));
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

	if (ensure(TowerAttributeSetBase)) {
		TowerAttributeSetBase -> OnHealthChanged.AddDynamic(this, &ATower::OnHealthChanged);
		TowerAttributeSetBase -> OnExperienceChanged.AddDynamic(this, &ATower::OnExperienceChanged);
		TowerAttributeSetBase -> OnAttackSpeedChanged.AddDynamic(this, &ATower::OnAttackSpeedChanged);
		TowerAttributeSetBase -> OnAttackDamageChanged.AddDynamic(this, &ATower::OnAttackDamageChanged);
		TowerAttributeSetBase -> OnRangeChanged.AddDynamic(this, &ATower::OnRangeChanged);
	}
	TotalGoldCost = GoldCost;
	
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATower::AddGameplayTag(const FGameplayTag& Tag) 
{
	GetAbilitySystemComponent() -> AddLooseGameplayTag(Tag);
	GetAbilitySystemComponent() -> SetTagMapCount(Tag, 1);
}

void ATower::RemoveGameplayTag(const FGameplayTag& Tag) 
{
	GetAbilitySystemComponent() -> RemoveLooseGameplayTag(Tag);
}

void ATower::OnHealthChanged(float Health, float MaxHealth, bool FullHealth, float PreviousHealth, AActor* EffectInstigator) 
{
	if (bIsDead) return;
	if (FullHealth) {
		AddGameplayTag(FullHealthTag);
	}
	else {
		RemoveGameplayTag(FullHealthTag);
	}
	BP_OnHealthChanged(Health, MaxHealth, FullHealth, PreviousHealth, EffectInstigator);


	if (Health <= 0.f) {
		BP_OnDeath();
		bIsDead = true;
	}
}
void ATower::OnExperienceChanged(float Experience, float MaxExperience) 
{
	BP_OnExperienceChanged(Experience, MaxExperience);
}

void ATower::OnAttackSpeedChanged(float NewAttackSpeed) 
{
	BP_OnAttackSpeedChanged(NewAttackSpeed);
}


void ATower::OnAttackDamageChanged(float NewAttackDamage) 
{
	BP_OnAttackDamageChanged(NewAttackDamage);
}

void ATower::OnRangeChanged(float NewRange) 
{	
	if (RangeDecalComp) {
		UE_LOG(LogTemp, Warning, TEXT("RangeDecalComp"));
		RangeDecalComp -> SetVisibility(false);
		RangeDecalComp -> DecalSize = FVector(20, NewRange, NewRange);
		RangeDecalComp -> SetVisibility(true);

	}
	BP_OnRangeChanged(NewRange);
}




void ATower::AcquireAbility(TSubclassOf<class UGameplayAbility> AbilityToAcquire, int32 AbilityLevel) 
{
	if (!SystemComp) return;
	if (HasAuthority() && AbilityToAcquire) {
		FGameplayAbilitySpecDef SpecDef = FGameplayAbilitySpecDef();
		SpecDef.Ability = AbilityToAcquire;
		FGameplayAbilitySpec Spec = FGameplayAbilitySpec(SpecDef, AbilityLevel);
		SystemComp -> GiveAbility(Spec);
	}
	SystemComp -> InitAbilityActorInfo(this, this);

}

void ATower::SetupRangeDecal(class UDecalComponent* DecalComp) 
{
	if (!TowerAttributeSetBase) return;
	DecalComp -> SetVisibility(false);
	float Range = TowerAttributeSetBase -> Range.GetCurrentValue();
	DecalComp -> DecalSize = FVector(20, Range, Range);
	RangeDecalComp = DecalComp;
}