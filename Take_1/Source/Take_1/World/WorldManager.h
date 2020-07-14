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

	UFUNCTION(BlueprintCallable, Category = "ChunkGeneration")
		TArray<FVector> GetNoiseForChunk(const int inCoordsX, const int inCoordsY);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ChunkGeneration")
		TArray<FVector2D> CalculateUVForChunk(const TArray<FVector> inVertexArray);

	//Propriety to multiply Z by - a.k.a how tall you want the terrain to be
	UPROPERTY(BlueprintReadWrite, Category = "ChunkGeneration")
		int Amplitude;

	//Vertex indeces array that form triangles ( 1st + 2nd + 3rd entry == first traingle and so on)
	UPROPERTY(BlueprintReadOnly, Category = "ChunkGeneration")
		TArray<int> Triangles;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector  Make3DVector(const float, const float, const float);

	FVector2D Make2DVector(const float, const float);

	void FillTriangleArray();

	int GetFlattenedArrayIndex(int, int, int);

	void ConstructNoiseWrapper(const EFastNoise_NoiseType, const int32, const float,
		const EFastNoise_Interp, const EFastNoise_FractalType, const int32, const float,
		const float, const float, const EFastNoise_CellularDistanceFunction, const EFastNoise_CellularReturnType);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected: //fields
	UFastNoiseWrapper* fastNoiseWrapperObject = nullptr;


};
