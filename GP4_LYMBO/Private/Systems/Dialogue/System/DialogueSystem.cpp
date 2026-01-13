// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Dialogue/System/DialogueSystem.h"

void UDialogueSystem::SetDialogueDataSystem(TScriptInterface<IDialogueDataInterface> SomeDialogueDataSystem)
{
	DialogueDataSystem = SomeDialogueDataSystem;
}

void UDialogueSystem::ResetDialogueSystem()
{
	ExitDialogue();
	PreviousDialoguesIndicesMap.Reset();
	CurrentNodeIndex = 0;
}

void UDialogueSystem::InitiateDialogue(UDialogueDataAsset* SomeDialogueAsset, APlayerController* PlayerController)
{
	if (DialogueAsset != SomeDialogueAsset)
	{
		if (DialogueAsset != nullptr)
		{
			PreviousDialoguesIndicesMap.Add(DialogueAsset, CurrentNodeIndex);
		}
		
		DialogueAsset = SomeDialogueAsset;

		bool bHasPreviousIndex = PreviousDialoguesIndicesMap.Contains(DialogueAsset);
		CurrentNodeIndex = bHasPreviousIndex ? PreviousDialoguesIndicesMap[DialogueAsset] : 0;
		
		SetUpLabels();

		OnDialogueSet.Broadcast();
	}

	DialogueContext = FGameDialogueContext{this, DialogueDataSystem, PlayerController, GetWorld()};
	OnDialogueInitiated.Broadcast();

	// Automatically progress to the first node
	ProgressDialogue();
}

void UDialogueSystem::ExitDialogue()
{
	OnDialogueExited.Broadcast();
}

FDialogueResult UDialogueSystem::ProgressDialogue()
{
	FDialogueResult DialogueResult;
	DialogueResult.FlowType = EDialogueFlowType::Continue;

	do
	{
		if (!DialogueAsset || !DialogueAsset->Nodes.IsValidIndex(CurrentNodeIndex))
		{
			// checkf(false, TEXT("DialogueAsset is null or CurrentNodeIndex is out of bounds."));
			UE_LOG(LogTemp, Warning, TEXT("DialogueAsset is null or CurrentNodeIndex is out of bounds."));

			OnDialogueExited.Broadcast();


			return FDialogueResult{
				EDialogueFlowType::End,
				EDialogueResultType::None,
				FGameplayTag::EmptyTag,
				true,
				true,
				FText::GetEmpty(),
				{}
			};
		}

		if (DialogueAsset->Nodes[CurrentNodeIndex]->CanExecute(DialogueContext))
		{
			DialogueAsset->Nodes[CurrentNodeIndex]->ExecuteNode(DialogueContext);
			DialogueResult = DialogueAsset->Nodes[CurrentNodeIndex]->GetResult(DialogueContext);

			if (DialogueResult.FlowType == EDialogueFlowType::Jump)
			{
				if (const int* FoundIndex = LabelToIndexMap.Find(DialogueResult.TargetLabel))
				{
					CurrentNodeIndex = *FoundIndex;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Label '%s' not found in LabelToIndexMap."),
					       *DialogueResult.Text.ToString());
					CurrentNodeIndex++;
				}
			}
			else if (DialogueResult.FlowType == EDialogueFlowType::Continue)
			{
				CurrentNodeIndex++;
			}
		}
		else
		{
			CurrentNodeIndex++;
			continue;
		}
	}
	while (DialogueResult.FlowType == EDialogueFlowType::Continue || DialogueResult.FlowType == EDialogueFlowType::Jump)
	;

	OnDialogueProgressed.Broadcast(DialogueResult);
	CurrentNodeIndex++;

	return DialogueResult;
}

void UDialogueSystem::SelectOption(int OptionIndex)
{
	// Access the previous node, since the node has already progressed.
	if (!DialogueAsset || !DialogueAsset->Nodes.IsValidIndex(CurrentNodeIndex - 1))
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogueAsset is null or CurrentNodeIndex is out of bounds."));
		return;
	}

	DialogueAsset->Nodes[CurrentNodeIndex - 1]->PickOption(DialogueContext, OptionIndex);
	ProgressDialogue();
}

FOnDialogueSet& UDialogueSystem::GetOnDialogueSetHandle()
{
	return OnDialogueSet;
}

FOnDialogueInitiated& UDialogueSystem::GetOnDialogueInitiatedHandle()
{
	return OnDialogueInitiated;
}

FOnDialogueProgressed& UDialogueSystem::GetOnDialogueProgressedHandle()
{
	return OnDialogueProgressed;
}

FOnDialogueExited& UDialogueSystem::GetOnDialogueExitedHandle()
{
	return OnDialogueExited;
}

void UDialogueSystem::SetUpLabels()
{
	LabelToIndexMap.Reset();

	const auto& Nodes = DialogueAsset->Nodes;
	const auto NumNodes = Nodes.Num();
	for (int i = 0; i < NumNodes; ++i)
	{
		if (Nodes[i]->Label.IsSet())
		{
			LabelToIndexMap.Add(Nodes[i]->Label.GetValue(), i);
		}
	}
}
