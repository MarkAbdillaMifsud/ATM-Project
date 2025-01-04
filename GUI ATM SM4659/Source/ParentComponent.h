#pragma once

#include <JuceHeader.h>
#include "../../Console ATM SM4659/userManager.h"
#include "../../Console ATM SM4659/BankAccountManager.h"

class MainComponent;
class AccountCreationComponent;
class AccountManagementComponent;
class BankAccountCreationComponent;

class ParentComponent : public juce::Component
{
public:
    ParentComponent();
    ~ParentComponent() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void showMainScreen();
    void showAccountCreationScreen();
    void showAccountManagementScreen();
    void showBankAccountCreationScreen();

private:
    std::unique_ptr<MainComponent> mainComponent;
    std::unique_ptr<AccountCreationComponent> accountCreationComponent;
    std::unique_ptr<AccountManagementComponent> accountManagementComponent;
    std::unique_ptr<BankAccountCreationComponent> bankAccountCreationComponent;

    UserManager userManager;
    BankAccountManager bankAccountManager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParentComponent)
};