#include "MainComponent.h"
#include "ParentComponent.h"

//==============================================================================
MainComponent::MainComponent(ParentComponent& parent) : parentComponent(parent) {
    titleLabel.setText("Welcome to ATM", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    titleLabel.setFont(juce::Font(24.0f, juce::Font::bold));
    addAndMakeVisible(titleLabel);

    usernameLabel.setText("Username:", juce::dontSendNotification);
    addAndMakeVisible(usernameLabel);
    addAndMakeVisible(usernameTextBox);

    passwordLabel.setText("Password:", juce::dontSendNotification);
    addAndMakeVisible(passwordLabel);
    passwordTextBox.setPasswordCharacter('*');
    addAndMakeVisible(passwordTextBox);

    loginButton.setButtonText("Login");
    loginButton.addListener(this);
    addAndMakeVisible(loginButton);

    createAccountButton.setButtonText("Create Account");
    createAccountButton.addListener(this);
    addAndMakeVisible(createAccountButton);

    setSize(400, 300);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgrey);
}

void MainComponent::resized()
{
    auto area = getLocalBounds().reduced(20);
    auto headerArea = area.removeFromTop(40);
    titleLabel.setBounds(headerArea);

    auto fieldArea = area.removeFromTop(100);
    usernameLabel.setBounds(fieldArea.removeFromTop(25));
    usernameTextBox.setBounds(fieldArea.removeFromTop(25).reduced(10, 0));
    passwordLabel.setBounds(fieldArea.removeFromTop(25));
    passwordTextBox.setBounds(fieldArea.removeFromTop(25).reduced(10, 0));

    auto buttonArea = area.removeFromBottom(80);
    loginButton.setBounds(buttonArea.removeFromTop(40).reduced(10));
    createAccountButton.setBounds(buttonArea.removeFromTop(40).reduced(10));
}

void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &loginButton)
    {
        juce::String username = usernameTextBox.getText();
        juce::String password = passwordTextBox.getText();

        if (username.isEmpty() || password.isEmpty())
        {
            juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
                "Login Failed", "Please fill in all fields.");
        }
        else
        {
            // Logic to validate user credentials
        }
    }
    else if (button == &createAccountButton)
    {
        parentComponent.showAccountCreationScreen();
    }
}
