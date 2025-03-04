// Fill out your copyright notice in the Description page of Project Settings.


#include "TravelMode.h"

void ATravelMode::Travel()
{
	GetWorld()->SeamlessTravel(TEXT("/Game/FantasyBundle/Maps/Demonstration_Cave"));
	//GetWorld()->ServerTravel(TEXT("/Game/FantasyBundle/Maps/Demonstration_Cave?listen"), true);
}
