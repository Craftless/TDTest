// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTextActor.h"

// Sets default values
ADamageTextActor::ADamageTextActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADamageTextActor::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();
	
}

// Called every frame
void ADamageTextActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

