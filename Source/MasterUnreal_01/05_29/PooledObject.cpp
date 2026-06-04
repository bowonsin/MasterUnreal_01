#include "PooledObject.h"

void UPooledObject::Init(class AMyObjectPool* Owner)
{
	bIsPoolActive = false;
	ObjectPool = Owner;
}

void UPooledObject::RecycleSelf()
{
}

void UPooledObject::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}
