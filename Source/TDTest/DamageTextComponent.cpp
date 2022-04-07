// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTextComponent.h"
#include "DamageTextActor.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/UserInterfaceSettings.h"

// Sets default values for this component's properties
UDamageTextComponent::UDamageTextComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageTextComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetOwner<APawn>() -> GetController<APlayerController>();
	
}


// Called every frame
void UDamageTextComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!GetOwner<APawn>() -> IsLocallyControlled()) return;
	if (!PlayerController) return;

	const FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(this);
	if (ViewportSize.X <= 0.f || ViewportSize.Y <= 0.f) return;

	const int32 ViewportX = FGenericPlatformMath::FloorToInt(ViewportSize.X);
	const int32 ViewportY = FGenericPlatformMath::FloorToInt(ViewportSize.Y);

	float ViewportScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass()) -> GetDPIScaleBasedOnSize(FIntPoint(ViewportX, ViewportY));

	if (ViewportScale <= 0.f) return;

	FVector CameraLocation = PlayerController -> PlayerCameraManager -> GetCameraLocation();

	for (int32 i = 1; i < ActiveDIActors.Num(); ++i) {
		ADamageTextActor* DIActor = ActiveDIActors[i];
		if (ensure(DIActor)) {
			float Distance = FVector::Dist(CameraLocation, DIActor -> InitialLocation);

			float TextVerticalOffset = Distance / (ViewportSize.X / ViewportScale);
			DIActor -> SetActorLocation(DIActor -> InitialLocation + FVector(0, 0, i * TextVerticalOffset * TextSpacing));
		}
	}
}

void UDamageTextComponent::OnTextDestroyed(AActor* DestroyedActor) 
{
	ActiveDIActors.Pop();
	UE_LOG(LogTemp, Warning, TEXT("Destroyed"));
}

void UDamageTextComponent::AddDamageIndicatorText_CLIENT_Implementation(TSubclassOf<ADamageTextActor> ActorClassToSpawn, const FText& InText, const FVector& SpawnLocation, AActor* SpawnTarget) 
{
	if (!ensure(ActorClassToSpawn)) return;

	int32 AmountToAdd = 0;

	if (ensure(SpawnTarget)) {
		for (ADamageTextActor* DIActor : ActiveDIActors) {
			if (DIActor -> SpawnTarget == SpawnTarget && DIActor -> GetText().ToString() == InText.ToString()) {
				AmountToAdd += DIActor -> GetAmount();
				DIActor -> Destroy();
				break;
				// DIActor -> AddAmount(1);
			}
		}
	}

	FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, SpawnLocation + FVector(FMath::RandRange(0.f, 25.f), FMath::RandRange(0.f, 25.f), VerticalOffset));
	ADamageTextActor* SpawnedActor = GetWorld() -> SpawnActorDeferred<ADamageTextActor>(ActorClassToSpawn, SpawnTransform, GetOwner());
	if (!ensure(SpawnedActor)) return;
	SpawnedActor -> SetText(InText);
	int32 Size = FCString::Atoi(*InText.ToString());
	SpawnedActor -> SetFontSize(Size);
	SpawnedActor -> AddAmount(AmountToAdd);
	SpawnedActor -> SpawnTarget = SpawnTarget;
	SpawnedActor -> OnDestroyed.AddDynamic(this, &UDamageTextComponent::OnTextDestroyed);
	UGameplayStatics::FinishSpawningActor(SpawnedActor, SpawnTransform);
	ActiveDIActors.Insert(SpawnedActor, 0);
	
}


