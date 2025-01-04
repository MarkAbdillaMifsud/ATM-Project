#pragma once

#include <JuceHeader.h>
#include "../../Console ATM SM4659/userManager.h"
#include "../../Console ATM SM4659/BankAccountManager.h"

class ParentComponent;

class BankAccountCreationComponent : public juce::Component,
									 public juce::Button::Listener
{
public:
	BankAccountCreationComponent(ParentComponent& parent, UserManager& userManager, BankAccountManager& bankAccountManager);
	~BankAccountCreationComponent() override;

	void paint(juce::Graphics& g) override;
	void resized() override;
	void buttonClicked(juce::Button* button) override;

private:
	ParentComponent& parentComponent;
	UserManager& userManager;
	BankAccountManager& bankAccountManager;

	juce::Label titleLabel;
	juce::TextButton savingsButton;
	juce::TextButton currentButton;
	juce::TextButton backButton;

	juce::Label accountNumberLabel;
	juce::TextEditor accountNumberInput;
	juce::TextButton submitButton;

	bool isCreatingSavingsAccount = false;

	void handleSubmitAccountCreation();
	void handleSavingsAccountCreation();
	void handleCurrentAccountCreation();

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BankAccountCreationComponent);
};