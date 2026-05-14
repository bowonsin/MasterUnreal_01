// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTochlight.h"
#include "TestMyInterface.h"
#include "Kismet/KismetSystemLibrary.h"
// Sets default values
AMyTochlight::AMyTochlight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyTochlight::BeginPlay()
{
	Super::BeginPlay();
	
	//시작할 떄
	for (const TWeakObjectPtr<AActor>& Item : Items)
	{
		/*
		// 로컬 변수로 만듦 Item을 
		// #include "TestMyIterface 호출해야 사용할수 있따.
		//Get() 함수의 역할
		//스마트 포인터는 실제 객체를 감싸고 있는 '껍데기'와 같습니다.
		//메모리 관리(참조 횟수 계산 등)를 대신 해주지만,
		//Cast나 다른 일반 포인터를 받는 함수에 넣으려면 안에 들어있는 실제 주소값이 필요합니다.
		// 이렇게 가져오면 CPP 에서 밖에 사용하지 못한다.
		 ITestMyInterface* MyInterface = Cast<ITestMyInterface>(Item.Get()); 
		if (MyInterface)
		{
			MyInterface->OnFireDected(100.0f,FVector::ZeroVector);
		}
		 */
		if (Item.IsValid())
		{
			//does임플리먼트 interface
			// UTestMyInterface U플렉션에 등록된 Interface를 가져와야한다.
			// 해당 클레스에 UClass 가 입력이 되어있냐 물어보는 것이다.
			//그래서 if문으로 써야한다.
			if (UKismetSystemLibrary::DoesImplementInterface(Item.Get(), UTestMyInterface::StaticClass()))
			{
				//OnFireDetected를 호출할것인데,
				// 블루프린트에서 사용하고자 한다면 Excute를 사용하는것이 맞긴한데
				// 블루 프린트에서 사용하겠다고 정의 를 해야한다.
				ITestMyInterface::Execute_OnFireDected(Item.Get(),100.0f,FVector::ZeroVector);
			}
		}
	}
	
}

// Called every frame
void AMyTochlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

