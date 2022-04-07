// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TDGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TDTEST_API ATDGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable)
	void BuildNavMeshes();

protected:
	
};
