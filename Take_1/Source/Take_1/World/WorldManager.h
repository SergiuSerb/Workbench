// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FastNoiseWrapper.h"

#include "WorldManager.generated.h"

UCLASS()
class TAKE_1_API AWorldManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ConstructNoiseWrapper(const EFastNoise_NoiseType, const int32, const float,
		const EFastNoise_Interp, const EFastNoise_FractalType, const int32, const float,
		const float, const float, const EFastNoise_CellularDistanceFunction, const EFastNoise_CellularReturnType);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected: //fields
	UFastNoiseWrapper* fastNoiseWrapperObject = nullptr;


};
