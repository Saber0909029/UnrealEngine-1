// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "SceneOutlinerPrivatePCH.h"

#include "WorldTreeItem.h"
#include "LevelEditor.h"

#define LOCTEXT_NAMESPACE "SceneOutliner_WorldTreeItem"

namespace SceneOutliner
{

FWorldTreeItem::FWorldTreeItem(UWorld* InWorld)
	: World(InWorld)
{

}

FTreeItemPtr FWorldTreeItem::FindParent(const FTreeItemMap& ExistingItems) const
{
	return nullptr;
}

FTreeItemPtr FWorldTreeItem::CreateParent() const
{
	return nullptr;
}

void FWorldTreeItem::Visit(const ITreeItemVisitor& Visitor) const
{
	Visitor.Visit(*this);
}

void FWorldTreeItem::Visit(const IMutableTreeItemVisitor& Visitor)
{
	Visitor.Visit(*this);
}

FTreeItemID FWorldTreeItem::GetID() const
{
	return FTreeItemID(World);
}

FString FWorldTreeItem::GetDisplayString() const
{
	if (UWorld* WorldPtr = World.Get())
	{
		return World->GetName();
	}
	return FString();
}

int32 FWorldTreeItem::GetTypeSortPriority() const
{
	return ETreeItemSortOrder::World;
}

bool FWorldTreeItem::CanInteract() const
{
	return !Flags.bIsFilteredOut;
}

void FWorldTreeItem::GenerateContextMenu(FMenuBuilder& MenuBuilder, SSceneOutliner& Outliner)
{
	const FSlateIcon WorldSettingsIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.WorldProperties.Tab");

	MenuBuilder.AddMenuEntry(LOCTEXT("OpenWorldSettings", "World Settings"), FText(), WorldSettingsIcon, FExecuteAction::CreateSP(this, &FWorldTreeItem::OpenWorldSettings));
}

FDragValidationInfo FWorldTreeItem::ValidateDrop(FDragDropPayload& DraggedObjects, UWorld& World) const
{
	return FDragValidationInfo::Invalid();
}

void FWorldTreeItem::OpenWorldSettings() const
{
	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>( TEXT("LevelEditor") );
	LevelEditorModule.GetLevelEditorTabManager()->InvokeTab(FName("WorldSettingsTab"));	
}

}		// namespace SceneOutliner

#undef LOCTEXT_NAMESPACE