// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Dialogue/Nodes/Formattable/SingleFormattableStatement.h"

FDialogueResult USingleFormattableStatement::GetResult(const FGameDialogueContext& DialogueContext)
{
	if (!DataGetter)
	{
		UE_LOG(LogTemp, Error, TEXT("USingleFormattableStatement::GetResult DataGetter is null"));
		return Super::GetResult(DialogueContext);
	}

	const FText FormatText = DataGetter->GetText(DialogueContext);
	FText Message = FText::Format(Text, FormatText);

	return FDialogueResult{
		EDialogueFlowType::End, EDialogueResultType::Statement, SpeakerTag, DoCloseDialogue, false, Message, {}
	};
}
