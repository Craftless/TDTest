// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTextActor.generated.h"

UCLASS()
class TDTEST_API ADamageTextActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageTextActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void SetText(const FText& InText);
	UFUNCTION(BlueprintImplementableEvent)
	FText GetText();
	UFUNCTION(BlueprintImplementableEvent)
	void AddAmount(int32 InAmount);
	UFUNCTION(BlueprintImplementableEvent)
	int32 GetAmount();
	UFUNCTION(BlueprintImplementableEvent)
	void SetFontSize(int32 Size);

	UPROPERTY()
	AActor* SpawnTarget = nullptr;

	FVector InitialLocation;

};
