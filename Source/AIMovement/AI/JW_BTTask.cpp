// Fill out your copyright notice in the Description page of Project Settings.
#include "JW_BTTask.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

/*
* 네비게이션 볼륨이 깔린곳 기준에서 랜덤 포인트를 찾아 리턴한다.
*/
UJWBTTask_RandomNavPoint::UJWBTTask_RandomNavPoint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Random Nav Point";

	// 블랙보드 키 값에 Vector만 허용한다
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UJWBTTask_RandomNavPoint, BlackboardKey));
}

EBTNodeResult::Type UJWBTTask_RandomNavPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(OwnerComp.GetAIOwner()->GetPawn()->GetWorld());
	if (IsValid(NavSystem))
	{
		FNavLocation DesiredTargetLocation = FNavLocation();
		FVector MyCharacterLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
		
		bool bFindNavPoint = NavSystem->GetRandomPointInNavigableRadius(MyCharacterLocation, RandomGoalPointRadius, DesiredTargetLocation);
		if (bFindNavPoint)
		{
			UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
			if (ensure(BlackboardComp))
			{
				//FVector KeyValue = BlackboardComp->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, DesiredTargetLocation);
			}
		}

		NodeResult = bFindNavPoint ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return NodeResult;
}

/*
* 태스크 호출시 Move To 중이라면 정지 시킨다.
*/
EBTNodeResult::Type UJWBTTask_MoveStop::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::Succeeded;

	OwnerComp.GetAIOwner()->StopMovement();

	return NodeResult;
}
