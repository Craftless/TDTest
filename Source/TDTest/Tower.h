// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "Tower.generated.h"

UENUM(BlueprintType)
enum class ETargetingMode : uint8 {
	Normal,
	Closest,
	Weakest,
	First = Normal,
	Last = Weakest
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNewAttackSpeed, float, NewAttackSpeed, float, NewAttackTime);

UCLASS()
class TDTEST_API ATower : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATower();

	UFUNCTION(BlueprintPure)
	float GetBaseAttackTime() const { return BaseAttackTime; }
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const { return SystemComp; }

	UFUNCTION(BlueprintCallable)
	void AcquireAbility(TSubclassOf<class UGameplayAbility> AbilityToAcquire, int32 AbilityLevel = 1);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Attack(AActor* TargetedActor);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Sell();

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnNewAttackSpeed OnNewAttackSpeedDelegate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 GoldCost = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 TotalGoldCost = 0;

	UPROPERTY(BlueprintReadWrite)
	class APlayerPawn* OwnerPlayer = nullptr;

	UFUNCTION(BlueprintCallable)
	void SetupRangeDecal(class UDecalComponent* DecalComp);

	UPROPERTY(BlueprintReadWrite)
	ETargetingMode TargetingMode = ETargetingMode::Normal;

	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	// TArray<FGameplayEffectSpecHandle> Modifiers;


	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UAbilitySystemComponent* SystemComp = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UTowerAttributeSetBase* TowerAttributeSetBase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag FullHealthTag;

	UFUNCTION(BlueprintCallable)
	void AddGameplayTag(const struct FGameplayTag& Tag);
	UFUNCTION(BlueprintCallable)
	void RemoveGameplayTag(const FGameplayTag& Tag);

	UPROPERTY(BlueprintReadWrite)
	bool bIsDead = false;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnDeath"))
	void BP_OnDeath();
	

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnHealthChanged"))
	void BP_OnHealthChanged(float Health, float MaxHealth, bool FullHealth, float PreviousHealth, AActor* EffectInstigator);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnExperienceChanged"))
	void BP_OnExperienceChanged(float Experience, float MaxExperience);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnAttackSpeedChanged"))
	void BP_OnAttackSpeedChanged(float AttackSpeed);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnAttackDamageChanged"))
	void BP_OnAttackDamageChanged(float AttackDamage);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnRangeChanged"))
	void BP_OnRangeChanged(float Range);
	UPROPERTY()
	class UDecalComponent* RangeDecalComp = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float BaseAttackTime = 1.5f;

	UFUNCTION()
	void OnHealthChanged(float Health, float MaxHealth, bool FullHealth, float PreviousHealth, AActor* EffectInstigator);
	UFUNCTION()
	void OnExperienceChanged(float Experience, float MaxExperience);
	UFUNCTION()
	void OnAttackSpeedChanged(float NewAttackSpeed);
	UFUNCTION()
	void OnAttackDamageChanged(float NewAttackDamage);
	UFUNCTION()
	void OnRangeChanged(float NewRange);

};
