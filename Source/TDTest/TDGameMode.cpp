// Fill out your copyright notice in the Description page of Project Settings.


#include "TDGameMode.h"
#include "NavMesh/NavMeshBoundsVolume.h"

void ATDGameMode::BuildNavMeshes() 
{
    FNavigationSystem::Build(*GetWorld());
}
