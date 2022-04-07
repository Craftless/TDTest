// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class TDTEST_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnMouseStartHovered();
	UFUNCTION(BlueprintImplementableEvent)
	void OnMouseStopHovered();

	UFUNCTION(BlueprintImplementableEvent)
	void OnMouseClicked();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnKeyPressedWhileHovering(const FKey& KeyPressed, class APlayerPawn* Player);


};
