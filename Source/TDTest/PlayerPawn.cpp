// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Tile.h"
#include "NavMesh/NavMeshBoundsVolume.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* Controller = GetController<APlayerController>();
	if (Controller) {
		PlayerController = Controller;
	}
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetHoveredTile();

	// FHitResult HitResult;
	// if (GetMouseLocationInWorld(HitResult)) {
	// 	if (HitResult.GetActor()) {
	// 		ATile* Tile = Cast<ATile>(HitResult.GetActor());
	// 		if (Tile) {
	// 			if (LastHoveredTile) {
	// 				if (LastHoveredTile == Tile);
	// 				else {
	// 					LastHoveredTile -> OnMouseStopHovered();
	// 					LastHoveredTile = nullptr;
	// 				}
	// 			}
	// 			else {
	// 				LastHoveredTile = Tile;
	// 				Tile->OnMouseStartHovered();
	// 			}
	// 		}
	// 	}
	// }
	// else {
	// 	if (LastHoveredTile) {
	// 		LastHoveredTile -> OnMouseStopHovered();
	// 		LastHoveredTile = nullptr;
	// 	}
	// }
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent -> BindAction(FName("LeftClick"), IE_Pressed, this, &APlayerPawn::OnMouseClicked);
	PlayerInputComponent -> BindAction(FName("RebuildNavMesh"), IE_Pressed, this, &APlayerPawn::RebuildNavMesh);

}

bool APlayerPawn::CheckEnoughGold(int32 GoldToCheck) const 
{
	return Gold >= GoldToCheck;
}

bool APlayerPawn::SpendGold(int32 AmountToSpend) 
{
	if (CheckEnoughGold(AmountToSpend)) {
		AddGold(-AmountToSpend);
		return true;
	}
	return false;
}

bool APlayerPawn::AddGold(int32 AmountToAdd) 
{
	Gold += AmountToAdd;
	return true;
}

ATile* APlayerPawn::GetHoveredTile() 
{
	FHitResult HitResult;
	if (GetMouseLocationInWorld(HitResult)) {
		if (HitResult.GetActor()) {
			ATile* Tile = Cast<ATile>(HitResult.GetActor());
			if (Tile) {
				if (LastHoveredTile) {
					if (LastHoveredTile == Tile) return LastHoveredTile;
					else {
						LastHoveredTile -> OnMouseStopHovered();
						LastHoveredTile = nullptr;

						LastHoveredTile = Tile;
						Tile->OnMouseStartHovered();
						return Tile;
					}
				}
				else {
					LastHoveredTile = Tile;
					Tile->OnMouseStartHovered();
					return Tile;
				}
			}
		}
	}
	else {
		if (LastHoveredTile) {
			LastHoveredTile -> OnMouseStopHovered();
			LastHoveredTile = nullptr;
		}
		return nullptr;
	}
	return nullptr;
}

bool APlayerPawn::GetMouseLocationInWorld(FHitResult& OutHitResult) 
{
	if (!PlayerController) return false;

	FVector WorldLoc;
	FVector WorldDir;
	PlayerController -> DeprojectMousePositionToWorld(WorldLoc, WorldDir);
	FCollisionQueryParams Params;
	Params. AddIgnoredActor(this);
	return GetWorld() -> LineTraceSingleByChannel(OutHitResult, WorldLoc, WorldLoc + WorldDir * 10000, ECollisionChannel::ECC_GameTraceChannel2, Params);

}

void APlayerPawn::OnMouseClicked() 
{
	FHitResult HitResult;
	if (GetMouseLocationInWorld(HitResult)) {
		ATile* Tile = Cast<ATile>(HitResult.GetActor());
		if (Tile) {
			Tile -> OnMouseClicked();
		}
	}
}

void APlayerPawn::RebuildNavMesh() 
{
	FNavigationSystem::Build(*GetWorld());
}


