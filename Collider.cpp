#include "Collider.h"

#include "ColliderPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

float CameraLagSpeed;
bool bEnableCameraLag;
// Sets default values
ACollider::ACollider()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	 
	SphereComponent=CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
    SetRootComponent(SphereComponent); //La componente Esfera es el root.
	SphereComponent->InitSphereRadius(40.f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

    MeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshComponentAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if(MeshComponentAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshComponentAsset.Object);
		MeshComponent->SetRelativeLocation(FVector{0.f,0.f,-40.f});
		MeshComponent->SetWorldScale3D(FVector{0.8f,	 0.8f, 0.8f});
	}
    SpringArm=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator{-45.f, 0.f, 0.f});
	SpringArm->TargetArmLength=400.f;
	SpringArm->bEnableCameraLag=true;
	SpringArm->CameraLagSpeed=3.0f;
	
	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	OurMovementComponent=CreateDefaultSubobject<UColliderPawnMovement>(TEXT("OurMovementComponent"));
	OurMovementComponent->UpdatedComponent=RootComponent;                             //Ese comando aplica moviemiento del componente.

	CameraInput= FVector2D(0.f,0.f);
	AutoPossessPlayer=EAutoReceiveInput::Player0;//commando para seleccionar jugadores. 
	
}

// Called when the game starts or when spawned
void ACollider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACollider::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveFoward"), this,&ACollider::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACollider::MoveRight);

	
}

 

void ACollider::MoveForward(float Input) // eso para personalizar nuestro movimiento
{

	FVector Forward =GetActorForwardVector();
	if (OurMovementComponent)
	{
		OurMovementComponent->AddInputVector(Forward* Input);
	}
	
}
void ACollider::MoveRight(float Input)
{
	FVector Right = GetActorRightVector();
	if (OurMovementComponent)
	{
		OurMovementComponent->AddInputVector(Right* Input);
	}
}
 void ACollider::YawCamera(float Axisvalue)
{
	CameraInput.X = Axisvalue;
}

void ACollider::PitchCamera(float Axisvalue)
{
	CameraInput.Y =Axisvalue;
}

UPawnMovementComponent* ACollider::GetMovementComponent() const
{
 return OurMovementComponent;
}
