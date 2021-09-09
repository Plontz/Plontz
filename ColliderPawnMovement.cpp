// Fill out your copyright notice in the Description page of Project Settings.


#include "ColliderPawnMovement.h"

void UColliderPawnMovement::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(!PawnOwner||!UpdatedComponent||ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	FVector DesireMovementThisFrame =ConsumeInputVector().GetClampedToMaxSize(1.0f);                           //Representa cuantos movimientos queremos en cualquier frame en particular.

	if(!DesireMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesireMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);	 //Significa que actualiza el componente y lo mueve, toma desde el vector.

		//if we bump into something, slide along of side of it.
		if(Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesireMovementThisFrame,1.f - Hit.Time, Hit.Normal, Hit); // Toma informacion del total de los movimientos que queremos hacer.
		}
	}
	
}
