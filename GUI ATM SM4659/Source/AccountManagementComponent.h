#pragma once

#include <JuceHeader.h>
#include "DepositComponent.h"
#include "WithdrawComponent.h"
#include "TransferComponent.h"
#include "../../Console ATM SM4659/userManager.h"
#include "../../Console ATM SM4659/BankAccountManager.h"

class ParentComponent;

class AccountManagementComponent : public juce::Component,
    public juce::Button::Listener
{
public:
    AccountManagementComponent(ParentComponent& parent, UserManager& userManager, BankAccountManager& bankAccountManager);
    ~AccountManagementComponent() override;

    void paint(juce::Graphics& g) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;
    void handleDepositResponse();
    void removeWithdrawComponent(WithdrawComponent* wComponent);
    void removeTransferComponent(TransferComponent* tComponent);

private:
    ParentComponent& parentComponent;
    UserManager& userManager;
    BankAccountManager& bankAccountManager;

    juce::Label titleLabel;
    juce::TextButton withdrawButton;
    juce::TextButton depositButton;
    juce::TextButton balanceButton;
    juce::TextButton creationButton;
    juce::TextButton transferButton;
    juce::TextButton logoutButton;

    std::unique_ptr<juce::AlertWindow> alertWindow;
    DepositComponent* depositComponent = nullptr;
    WithdrawComponent* withdrawComponent = nullptr;
    TransferComponent* transferComponent = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AccountManagementComponent)
};