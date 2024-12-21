#pragma once

#include <JuceHeader.h>


class ParentComponent;

class MainComponent  : public juce::Component,
                       public juce::Button::Listener

{
public:
    MainComponent(ParentComponent& parent);
    ~MainComponent() override;
    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;

private:
    ParentComponent& parentComponent;

    juce::Label titleLabel;
    juce::Label usernameLabel;
    juce::TextEditor usernameTextBox;
    juce::Label passwordLabel;
    juce::TextEditor passwordTextBox;
    juce::TextButton loginButton;
    juce::TextButton createAccountButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
