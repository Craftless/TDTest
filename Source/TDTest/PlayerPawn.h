// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class TDTEST_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite)
	APlayerController* PlayerController;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly)
	class ATile* LastHoveredTile = nullptr;

	UPROPERTY(BlueprintReadWrite)
	int32 Gold = 0;

	UFUNCTION(BlueprintPure)
	bool CheckEnoughGold(int32 GoldToCheck) const;

	UFUNCTION(BlueprintCallable)
	bool SpendGold(int32 AmountToSpend);
	UFUNCTION(BlueprintCallable)
	bool AddGold(int32 AmountToAdd);

	UFUNCTION(BlueprintCallable)
	ATile* GetHoveredTile();

private:
	bool GetMouseLocationInWorld(FHitResult& OutHitResult);
	void OnMouseClicked();
	void RebuildNavMesh();

};
