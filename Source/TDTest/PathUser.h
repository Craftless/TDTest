// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PathUser.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPathUser : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TDTEST_API IPathUser
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	void AddPathToUI(BP_Path)

};
