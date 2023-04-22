// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AIMovement/AI/OPMoveTo/BTTask_OPMoveTo.h"
#include "JW_BTTask.generated.h"

/**
 * JW BTTaskNode 베이스 클래스
 */
UCLASS()
class AIMOVEMENT_API UJW_BTTaskNode_Base : public UBTTaskNode
{
	GENERATED_BODY()

};

/**
 * JW BlackboardBase 클래스
 */
UCLASS()
class AIMOVEMENT_API UJW_BTTask_BlackboardBase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

};



/*
* 네비게이션 볼륨이 깔린곳 기준에서 랜덤 포인트를 찾아 리턴한다.
*/
UCLASS()
class AIMOVEMENT_API UJWBTTask_RandomNavPoint : public UJW_BTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UJWBTTask_RandomNavPoint(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(EditAnywhere)
	float RandomGoalPointRadius = 500.f;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};

/*
* 태스크 호출시 Move To 중이라면 정지 시킨다.
*/
UCLASS()
class AIMOVEMENT_API UJWBTTask_MoveStop : public UJW_BTTaskNode_Base
{
	GENERATED_BODY()

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};

