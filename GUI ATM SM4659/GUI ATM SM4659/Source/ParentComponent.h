#pragma once

#include <JuceHeader.h>
#include "userManager.h"


class MainComponent;
class AccountCreationComponent;

class ParentComponent : public juce::Component
{
public:
    ParentComponent();
    ~ParentComponent() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void showMainScreen();
    void showAccountCreationScreen();

private:
    std::unique_ptr<MainComponent> mainComponent;
    std::unique_ptr<AccountCreationComponent> accountCreationComponent;

    UserManager userManager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParentComponent)
};