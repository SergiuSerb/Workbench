// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "RuntimeMesh.h"

#include "WorldChunk.generated.h"

UCLASS()
class TAKE_1_API AWorldChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldChunk();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ChunkGeneration")
		void BuildMesh(const TArray<FVector> &inVertexArray, const TArray<int> &inTriangleArray, const TArray<FVector2D> &inUVArray);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected: //fields

};
