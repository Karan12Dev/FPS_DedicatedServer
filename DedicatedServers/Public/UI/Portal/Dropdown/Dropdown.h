// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Dropdown.generated.h"

/**
 * 
 */
UCLASS()
class DEDICATEDSERVERS_API UDropdown : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock_ButtonExpander;
	
	
private:
	void SetStyleTransparent();
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWidgetSwitcher> WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> ExpandedWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> CollapsedWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Expander;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FSlateColor HoveredTextColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FSlateColor UnhoveredTextColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FSlateBrush Triangle_Up;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FSlateBrush Triangle_Down;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_Triangle;

	UFUNCTION()
	void ToggleDropdown();

	bool bIsExpanded;

	void Expand();
	void Collapse();

	UFUNCTION()
	void Hover();

	UFUNCTION()
	void Unhover();	
};
