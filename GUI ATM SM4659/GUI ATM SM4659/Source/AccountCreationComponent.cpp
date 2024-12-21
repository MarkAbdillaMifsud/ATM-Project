#include "AccountCreationComponent.h"
#include "ParentComponent.h"

AccountCreationComponent::AccountCreationComponent(ParentComponent& parent) : parentComponent(parent) {
    // Title
    titleLabel.setText("Create a New Account", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    titleLabel.setFont(juce::Font(24.0f, juce::Font::bold));
    addAndMakeVisible(titleLabel);

    // Username Field
    usernameLabel.setText("Username:", juce::dontSendNotification);
    addAndMakeVisible(usernameLabel);
    addAndMakeVisible(usernameTextBox);

    // Password Field
    passwordLabel.setText("Password:", juce::dontSendNotification);
    addAndMakeVisible(passwordLabel);
    passwordTextBox.setPasswordCharacter('*');
    addAndMakeVisible(passwordTextBox);
    DBG("Password Text Box added to the component hierarchy.");

    // Confirm Password Field
    confirmPasswordLabel.setText("Confirm Password:", juce::dontSendNotification);
    addAndMakeVisible(confirmPasswordLabel);
    confirmPasswordTextBox.setPasswordCharacter('*');
    addAndMakeVisible(confirmPasswordTextBox);
    DBG("Confirm Password Text Box added to the component hierarchy.");

    // Buttons
    createAccountButton.setButtonText("Create Account");
    createAccountButton.addListener(this);
    addAndMakeVisible(createAccountButton);

    backButton.setButtonText("Back");
    backButton.addListener(this);
    addAndMakeVisible(backButton);

    setSize(400, 300);
}

AccountCreationComponent::~AccountCreationComponent() {}

void AccountCreationComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgrey);
}

void AccountCreationComponent::resized() {
    auto area = getLocalBounds().reduced(20);

    auto headerArea = area.removeFromTop(40);
    titleLabel.setBounds(headerArea);

    auto fieldArea = area.removeFromTop(120);
    usernameLabel.setBounds(fieldArea.removeFromTop(25));
    usernameTextBox.setBounds(fieldArea.removeFromTop(25).reduced(10, 0));
    passwordLabel.setBounds(fieldArea.removeFromTop(25));
    passwordTextBox.setBounds(fieldArea.removeFromTop(25).reduced(10, 0));
    confirmPasswordLabel.setBounds(fieldArea.removeFromTop(25)); // Confirm Password Label
    confirmPasswordTextBox.setBounds(fieldArea.removeFromTop(25).reduced(10, 0)); // Confirm Password Text Field

    auto buttonArea = area.removeFromBottom(80);
    createAccountButton.setBounds(buttonArea.removeFromTop(40).reduced(10));
    backButton.setBounds(buttonArea.removeFromTop(40).reduced(10));
}


void AccountCreationComponent::buttonClicked(juce::Button* button)
{
    if (button == &createAccountButton)
    {
        juce::String username = usernameTextBox.getText();
        juce::String password = passwordTextBox.getText();
        juce::String confirmPassword = confirmPasswordTextBox.getText();

        if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty())
        {
            juce::AlertWindow::showMessageBoxAsync(
                juce::AlertWindow::WarningIcon,
                "Error",
                "Please fill in all fields."
            );
            return;
        }

        if (password != confirmPassword)
        {
            juce::AlertWindow::showMessageBoxAsync(
                juce::AlertWindow::WarningIcon,
                "Error",
                "Passwords do not match."
            );
            return;
        }

        // Add account creation logic here
        // Example:
        // if (userManager.createUser(username.toStdString(), password.toStdString())) {
        //     juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::InfoIcon,
        //                                            "Success",
        //                                            "Account created successfully!");
        //     // Navigate back to login screen
        // } else {
        //     juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
        //                                            "Error",
        //                                            "Username already exists.");
        // }
    }
    else if (button == &backButton)
    {
        parentComponent.showMainScreen();
    }
}
