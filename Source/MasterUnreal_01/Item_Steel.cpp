// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Steel.h"

void AItem_Steel::OnFireDected_Implementation(float Temperature, FVector HitLocation)
{
	//Super::OnFireDected(Temperature, HitLocation);
	// 만약 Implementation을 사용하게 될 경우 
	// 함수 안에 어떠한 코드를 무조건 넣어둬야한다.
	// 안그러면 게임 진행시 강제 종료가 되어 버린다.
	UE_LOG(LogTemp, Warning, TEXT("철제 아이템이 불에 반응합니다! 온도: "));
}
