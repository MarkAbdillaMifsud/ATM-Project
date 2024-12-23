#pragma once

#include <JuceHeader.h>
#include "userManager.h"

class ParentComponent;

class AccountManagementComponent : public juce::Component,
    public juce::Button::Listener
{
public:
    AccountManagementComponent(ParentComponent& parent, UserManager& userManager);
    ~AccountManagementComponent() override;

    void paint(juce::Graphics& g) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;

private:
    ParentComponent& parentComponent;
    UserManager& userManager;

    juce::Label titleLabel;
    juce::TextButton withdrawButton;
    juce::TextButton depositButton;
    juce::TextButton balanceButton;
    juce::TextButton transferButton;
    juce::TextButton logoutButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AccountManagementComponent)
};