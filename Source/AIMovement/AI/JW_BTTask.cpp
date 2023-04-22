// Fill out your copyright notice in the Description page of Project Settings.
#include "JW_BTTask.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

/*
* �׺���̼� ������ �򸰰� ���ؿ��� ���� ����Ʈ�� ã�� �����Ѵ�.
*/
UJWBTTask_RandomNavPoint::UJWBTTask_RandomNavPoint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Random Nav Point";

	// ������ Ű ���� Vector�� ����Ѵ�
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
* �½�ũ ȣ��� Move To ���̶�� ���� ��Ų��.
*/
EBTNodeResult::Type UJWBTTask_MoveStop::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::Succeeded;

	OwnerComp.GetAIOwner()->StopMovement();

	return NodeResult;
}
