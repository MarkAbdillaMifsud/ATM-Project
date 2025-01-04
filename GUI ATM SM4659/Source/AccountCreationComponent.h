#pragma once

#include <JuceHeader.h>
#include "../../Console ATM SM4659/userManager.h"

class ParentComponent;

class AccountCreationComponent : public juce::Component,
								 public juce::Button::Listener

{
public:
	AccountCreationComponent(ParentComponent& parent, UserManager& userManager);
	~AccountCreationComponent() override;

	void paint(juce::Graphics& g) override;
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
    juce::Label confirmPasswordLabel;
    juce::TextEditor confirmPasswordTextBox;

    juce::TextButton createAccountButton;
    juce::TextButton backButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AccountCreationComponent)
};
