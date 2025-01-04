#pragma once

#include <JuceHeader.h>
#include "ParentComponent.h"
#include "../../Console ATM SM4659/userManager.h"
#include "../../Console ATM SM4659/BankAccountManager.h"
#include "../../Console ATM SM4659/BankAccount.h"

class DepositComponent : public juce::Component,
						 public juce::Button::Listener
{
public:
	DepositComponent(ParentComponent& parentComponent, UserManager& userManager, BankAccountManager& bankAccountManager);
	~DepositComponent() override;

	void paint(juce::Graphics& g) override;
	void resized() override;

	void buttonClicked(juce::Button* button) override;

private:
	juce::TextButton confirmButton;
	juce::TextButton cancelButton;
	juce::ComboBox accountComboBox;
	juce::TextEditor amountTextBox;
	juce::Label accountLabel;
	juce::Label amountLabel;

	UserManager& userManager;
	BankAccountManager& bankAccountManager;
	ParentComponent& parentComponent;

	void populateAccountComboBox();
	void performDeposit();

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DepositComponent)
};
