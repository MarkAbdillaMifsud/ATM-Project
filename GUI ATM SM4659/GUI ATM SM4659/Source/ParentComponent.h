#pragma once

#include <JuceHeader.h>
#include "userManager.h"


class MainComponent;
class AccountCreationComponent;
class AccountManagementComponent;

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

private:
    std::unique_ptr<MainComponent> mainComponent;
    std::unique_ptr<AccountCreationComponent> accountCreationComponent;
    std::unique_ptr<AccountManagementComponent> accountManagementComponent;

    UserManager userManager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParentComponent)
};