// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Collider.generated.h"

UCLASS()
class FIRSTPROJECT_API ACollider : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere,Category="Mesh") // crear componente
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category="Mesh")  // crear esfera componente
	class USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, Category="Mesh")  // crear camara 
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, Category="Mesh")
	class USpringArmComponent* SpringArm; // help with the camera Motion

	UPROPERTY (VisibleAnywhere, Category="Movement")
	class UColliderPawnMovement* OurMovementComponent; // se crea el componente del movimiento.
	FVector2D CameraInput;


	virtual UPawnMovementComponent* GetMovementComponent() const override; // usando el comando sobreescribir ya que se esta utilizando para crear upawnmovementcomponent y lo retorna.
	
	FORCEINLINE UStaticMeshComponent* GetMeshComponent() {return MeshComponent;} // get component
    FORCEINLINE void SetMeshComponent (UStaticMeshComponent* Mesh){MeshComponent=Mesh;} // set component
	FORCEINLINE USphereComponent* GetSphereComponent() {return SphereComponent;} // getsphere component
	FORCEINLINE void SetSphereComponent (UStaticMeshComponent* Sphere){MeshComponent=Sphere;} // set sphere component
	
	FORCEINLINE UCameraComponent* GetCameraComponent() {return Camera;} // get camera component
	FORCEINLINE void SetCameraComponent (UCameraComponent* InCamera){Camera = InCamera;} // set camera component
	FORCEINLINE USpringArmComponent* GetSpringArmComponent() {return SpringArm;} // get springarmcomponent
	FORCEINLINE void SetSpringArmComponent (USpringArmComponent* InSpringArm){SpringArm =InSpringArm;} // set springarmcomponent

	private:
	void MoveForward(float Input);
	void MoveRight(float Input);
	void YawCamera(float Axisvalue);
	void PitchCamera(float Axisvalue);
};
