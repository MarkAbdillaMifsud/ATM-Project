#pragma once

#include <JuceHeader.h>
#include "../../Console ATM SM4659/userManager.h"

class ParentComponent;

class MainComponent  : public juce::Component,
                       public juce::Button::Listener

{
public:
    MainComponent(ParentComponent& parent, UserManager& userManager);
    ~MainComponent() override;
    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;

private:
    ParentComponent& parentComponent;
    UserManager& userManager;

    juce::Label titleLabel;
    juce::Label usernameLabel;
    juce::TextEditor usernameTextBox;
    juce::Label passwordLabel;
    juce::TextEditor passwordTextBox;
    juce::TextButton loginButton;
    juce::TextButton createAccountButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
