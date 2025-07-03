// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AccountDropdown_Expanded.generated.h"

class UDSLocalPlayerSubsystem;
/**
 * 
 */
UCLASS()
class DEDICATEDSERVERS_API UAccountDropdown_Expanded : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	
private:
	void SetSignOutButtonStyleTransparent();
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_SignOut;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock_SignOut;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock_Email;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FSlateColor HoveredTextColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FSlateColor UnhoveredTextColor;

	UFUNCTION()
	void SignOutButton_Hover();

	UFUNCTION()
	void SignOutButton_Unhover();

	UFUNCTION()
	void SignOutButton_OnClicked();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UPortalManager> PortalManagerClass;
	
	UPROPERTY()
	TObjectPtr<UPortalManager> PortalManager;

	UDSLocalPlayerSubsystem* GetDSLocalPlayerSubsystem();
};
