// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageTextComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TDTEST_API UDamageTextComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageTextComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Client, Unreliable)
	void AddDamageIndicatorText_CLIENT(TSubclassOf<class ADamageTextActor> ActorClassToSpawn, const FText& InText, const FVector& SpawnLocation, AActor* SpawnTarget);

	UPROPERTY(EditDefaultsOnly)
	float VerticalOffset = 0;
	UPROPERTY(EditDefaultsOnly)
	float TextSpacing = 75;

private:
	UPROPERTY()
	APlayerController* PlayerController = nullptr;

	UPROPERTY()
	TArray<class ADamageTextActor*> ActiveDIActors;

	UFUNCTION()
	void OnTextDestroyed(AActor* DestroyedActor);
		
};
