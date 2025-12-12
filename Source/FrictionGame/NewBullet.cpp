// Fill out your copyright notice in the Description page of Project Settings.


#include "NewBullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/OverlapResult.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
ANewBullet::ANewBullet()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Component"));

	CollisionComponent->SetSphereRadius(16.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionComponent->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	// create the projectile movement component. No need to attach it because it's not a Scene Component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bShouldBounce = true;

}


void ANewBullet::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->IgnoreActorWhenMoving(GetInstigator(), true);
	
}


void ANewBullet::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(DestructionTimer);
}

void ANewBullet::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bHit)
	{
		return;
	}
	bHit = true;
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ProcessHit(Other, OtherComp, Hit.ImpactPoint, -Hit.ImpactNormal);
	BP_OnProjectileHit(Hit);
	if (DeferredDestructionTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(DestructionTimer, this, &ANewBullet::OnDeferredDestruction, DeferredDestructionTime, false);
	}
	else
	{
		Destroy();
	}
}

void ANewBullet::ProcessHit(AActor* HitActor, UPrimitiveComponent* HitComp, const FVector& HitLocation, const FVector& HitDirection)
{
	if (HitComp && HitComp->IsSimulatingPhysics())
	{
		HitComp->AddImpulseAtLocation(HitDirection*PhysicsForce, HitLocation);
		HitComp->SetPhysMaterialOverride(PhysicalMat);
	}
}

void ANewBullet::OnDeferredDestruction()
{
	Destroy();
}
