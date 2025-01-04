#pragma once

#include <JuceHeader.h>
#include "../../Console ATM SM4659/userManager.h"
#include "../../Console ATM SM4659/BankAccount.h"
#include "../../Console ATM SM4659/BankAccountManager.h"

class AccountManagementComponent;

class TransferComponent : public juce::Component,
	public juce::Button::Listener
{
public:
	TransferComponent(AccountManagementComponent* parentComponent, UserManager& userManager, BankAccountManager& bankAccountManager);
	~TransferComponent() override;

	void paint(juce::Graphics& g) override;
	void resized() override;

	void buttonClicked(juce::Button* button) override;

private:
	juce::ComboBox sourceAccountComboBox;
	juce::ComboBox destinationAccountComboBox;
	juce::TextEditor amountTextBox;
	juce::Label sourceAccountLabel;
	juce::Label destinationAccountLabel;
	juce::Label amountLabel;
	juce::TextButton confirmButton;
	juce::TextButton cancelButton;

	AccountManagementComponent* parentComponent;
	UserManager& userManager;
	BankAccountManager& bankAccountManager;

	void populateAccountComboBoxes();
	void performTransfer();
};