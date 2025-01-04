#pragma once

#include <JuceHeader.h>
#include "../../Console ATM SM4659/userManager.h"
#include "../../Console ATM SM4659/BankAccountManager.h"
#include "../../Console ATM SM4659/BankAccount.h"

class AccountManagementComponent;

class WithdrawComponent : public juce::Component,
	public juce::Button::Listener 
{
public:
	WithdrawComponent(AccountManagementComponent* parentComponent, UserManager& userManager, BankAccountManager& bankAccountManager);
	~WithdrawComponent() override;

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
    AccountManagementComponent* parentComponent;

    void populateAccountComboBox();
    void performWithdraw();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WithdrawComponent)
};