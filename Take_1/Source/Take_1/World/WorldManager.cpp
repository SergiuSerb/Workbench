// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldManager.h"

// Sets default values
AWorldManager::AWorldManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; //should be reworked later

	//calculate noise
	ConstructNoiseWrapper(EFastNoise_NoiseType::SimplexFractal, 69, 0.02, EFastNoise_Interp::Quintic,
		EFastNoise_FractalType::FBM, 5, 2.f, 0.5f, 0.45f,
		EFastNoise_CellularDistanceFunction::Euclidean, EFastNoise_CellularReturnType::CellValue);

	//construct triangle array
	FillTriangleArray();



}

// Called when the game starts or when spawned
void AWorldManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorldManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldManager::ConstructNoiseWrapper(const EFastNoise_NoiseType noiseType, const int32 seed, const float frequency,
			const EFastNoise_Interp interpolationMethod, const EFastNoise_FractalType fractalType, const int32 octaves, const float lacunarity,
			const float gain , const float cellularJitter, const EFastNoise_CellularDistanceFunction cellularDistanceFunction, const EFastNoise_CellularReturnType cellularReturnType)
{
	fastNoiseWrapperObject = CreateDefaultSubobject<UFastNoiseWrapper>(TEXT("FastNoiseWrapper"));

	fastNoiseWrapperObject->SetupFastNoise(noiseType, seed, frequency, interpolationMethod,
								fractalType, octaves, lacunarity, gain,
								cellularJitter, cellularDistanceFunction, cellularReturnType);


}

FVector AWorldManager::Make3DVector(const float X, const float Y, const float Z)
{
	FVector ToReturn;

	ToReturn.X = X;
	ToReturn.Y = Y;
	ToReturn.Z = Z;

	return ToReturn;
}

int AWorldManager::GetFlattenedArrayIndex(int matrixSize, int i, int j)
{
	return (matrixSize * i) + j;
}

void AWorldManager::FillTriangleArray()
{
	int bottomLeftIndex, topLeftIndex, bottomRightIndex, topRightIndex;

	for (int i = 0; i < 20 - 1; i++)
	{
		for (int j = 0; j < 20 - 1; j++)
		{
			topLeftIndex = GetFlattenedArrayIndex(20, i, j);
			topRightIndex = GetFlattenedArrayIndex(20, i, j + 1);
			bottomLeftIndex = GetFlattenedArrayIndex(20, i + 1, j);
			bottomRightIndex = GetFlattenedArrayIndex(20, i + 1, j + 1);

			Triangles.Add(bottomLeftIndex);
			Triangles.Add(topLeftIndex);
			Triangles.Add(topRightIndex);
			Triangles.Add(bottomLeftIndex);
			Triangles.Add(topRightIndex);
			Triangles.Add(bottomRightIndex);
		}
	}
}

TArray<FVector> AWorldManager::GetNoiseForChunk(FVector startingLocation)
{
	TArray<FVector> resultArray;

	int xCoord = startingLocation.X;
	int yCoord = startingLocation.Y;

	while (xCoord <= (startingLocation.X + 20))
	{
		while (yCoord <= (startingLocation.Y + 19))
		{
			resultArray.Add(Make3DVector(xCoord*50, yCoord*50, fastNoiseWrapperObject->GetNoise2D(xCoord, yCoord) * Amplitude));

			yCoord++;
		}

		xCoord ++;
		yCoord = startingLocation.Y;
	}


	return resultArray;
}
