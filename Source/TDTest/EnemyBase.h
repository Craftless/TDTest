// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "EnemyBase.generated.h"

UCLASS()
class TDTEST_API AEnemyBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyBase();
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const { return SystemComp; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UAbilitySystemComponent* SystemComp = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UEnemyAttributeSetBase* EnemyAttributeSetBase;



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
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnMovementSpeedChanged"))
	void BP_OnMovementSpeedChanged(float NewSpeed);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnFinishedBeginPlay"))
	void BP_FinishedBeginPlay();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* TargetComp = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* EnemyMesh = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* RootComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SpawningOffset = FVector(0, 0, -80);

	UFUNCTION()
	void OnHealthChanged(float Health, float MaxHealth, bool FullHealth, float PreviousHealth, AActor* EffectInstigator);
	UFUNCTION()
	void OnExperienceChanged(float Experience, float MaxExperience);
	UFUNCTION()
	void OnMovementSpeedChanged(float NewSpeed);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 GoldBounty = 0;
	

};
