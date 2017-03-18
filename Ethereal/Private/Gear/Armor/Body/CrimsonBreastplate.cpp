// © 2014 - 2016 Soverance Studios
// http://www.soverance.com

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Ethereal.h"
#include "CrimsonBreastplate.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
ACrimsonBreastplate::ACrimsonBreastplate(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_CrimsonBreastplate.ArmorIcon_CrimsonBreastplate'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_CrimsonBreastplate-small.ArmorIcon_CrimsonBreastplate-small'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmorMeshObject(TEXT("SkeletalMesh'/Game/EtherealParty/Morgan/Clothes/CrimsonArmor/CrimsonBreastplate/CrimsonBreastplate.CrimsonBreastplate'"));

	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_ArmorMesh = ArmorMeshObject.Object;
	ArmorMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("ArmorMesh"));
	ArmorMesh->SetSkeletalMesh(SK_ArmorMesh);
	ArmorMesh->SetupAttachment(RootComponent);
	UCommonLibrary::SetupSKComponentsWithCollision(ArmorMesh);
	
	// Set Default Values
	Name = EMasterGearList::GL_CrimsonBreastplate;
	NameText = LOCTEXT("CrimsonBreastplateName", "Crimson Heart");
	Type = EMasterGearTypes::GT_Body;
	TypeText = LOCTEXT("CrimsonBreastplateType", "Body");
	Description = "Armor of Ethereal Regents.";
	Price = 35000;
	MPCost = 0;
	ATK = 10;
	DEF = 15;
	SPD = 8;
	HP = 100;
	MP = 50;
	SpecialEffectText = LOCTEXT("CrimsonBreastplateSpecialEffect", "+ Reraise Effect");
}

// Called when the game starts or when spawned
void ACrimsonBreastplate::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	OnBindGear.AddDynamic(this, &ACrimsonBreastplate::DoSpecialEffect);
	OnRemoveGear.AddDynamic(this, &ACrimsonBreastplate::RemoveSpecialEffect);
}

// Custom code for Special Effect
void ACrimsonBreastplate::DoSpecialEffect()
{
	OwnerReference->HasReraise = true;
	OwnerReference->EtherealPlayerController->ActivateStatus_Reraise();
}

// Custom code for Special Effect
void ACrimsonBreastplate::RemoveSpecialEffect()
{
	OwnerReference->HasReraise = true;
	OwnerReference->EtherealPlayerController->RemoveStatus_Reraise();
}

#undef LOCTEXT_NAMESPACE
