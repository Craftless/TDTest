// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "AbilitySystemComponent.h"
#include "EnemyAttributeSetBase.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TargetComp = CreateDefaultSubobject<USceneComponent>(FName("TargetComponent"));
	TargetComp -> SetupAttachment(GetRootComponent());
	SystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(FName("ASC"));
	EnemyAttributeSetBase = CreateDefaultSubobject<UEnemyAttributeSetBase>(FName("AttributeSetBase"));

}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if (EnemyAttributeSetBase) {
		EnemyAttributeSetBase -> OnHealthChanged.AddDynamic(this, &AEnemyBase::OnHealthChanged);
		EnemyAttributeSetBase -> OnExperienceChanged.AddDynamic(this, &AEnemyBase::OnExperienceChanged);
		EnemyAttributeSetBase -> OnMovementSpeedChanged.AddDynamic(this, &AEnemyBase::OnMovementSpeedChanged);
	}

	BP_FinishedBeginPlay();
	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AEnemyBase::AddGameplayTag(const FGameplayTag& Tag) 
{
	GetAbilitySystemComponent() -> AddLooseGameplayTag(Tag);
	GetAbilitySystemComponent() -> SetTagMapCount(Tag, 1);
}

void AEnemyBase::RemoveGameplayTag(const FGameplayTag& Tag) 
{
	GetAbilitySystemComponent() -> RemoveLooseGameplayTag(Tag);
}


void AEnemyBase::OnHealthChanged(float Health, float MaxHealth, bool FullHealth, float PreviousHealth, AActor* EffectInstigator) 
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

void AEnemyBase::OnExperienceChanged(float Experience, float MaxExperience) 
{
	BP_OnExperienceChanged(Experience, MaxExperience);
}

void AEnemyBase::OnMovementSpeedChanged(float NewSpeed) 
{
	BP_OnMovementSpeedChanged(NewSpeed);
}

