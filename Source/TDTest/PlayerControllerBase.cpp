// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"


void APlayerControllerBase::BeginPlay() 
{
    Super::BeginPlay();
    bShowMouseCursor = true;
    UE_LOG(LogTemp, Warning, TEXT("FIRSt"));
}
