#include "AccountCreationComponent.h"
#include "ParentComponent.h"
#include "../../Console ATM SM4659/userManager.h"

AccountCreationComponent::AccountCreationComponent(ParentComponent& parent, UserManager& userManager) : parentComponent(parent), userManager(userManager) {
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
    addAndMakeVisible(passwordTextBox); // Ensure this is correct

    // Confirm Password Field
    confirmPasswordLabel.setText("Confirm Password:", juce::dontSendNotification);
    addAndMakeVisible(confirmPasswordLabel);
    confirmPasswordTextBox.setPasswordCharacter('*');
    addAndMakeVisible(confirmPasswordTextBox); // Ensure this is correct


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

void AccountCreationComponent::resized()
{
    auto area = getLocalBounds().reduced(20);

    auto headerArea = area.removeFromTop(40);
    titleLabel.setBounds(headerArea);

    auto fieldArea = area.removeFromTop(150); // Ensure enough height is reserved for fields
    usernameLabel.setBounds(fieldArea.removeFromTop(25));
    usernameTextBox.setBounds(fieldArea.removeFromTop(25).reduced(10, 0));
    passwordLabel.setBounds(fieldArea.removeFromTop(25));
    passwordTextBox.setBounds(fieldArea.removeFromTop(25).reduced(10, 0));
    confirmPasswordLabel.setBounds(fieldArea.removeFromTop(25));
    confirmPasswordTextBox.setBounds(fieldArea.removeFromTop(25).reduced(10, 0)); // Ensure height > 0

    auto buttonArea = area.removeFromBottom(80);
    createAccountButton.setBounds(buttonArea.removeFromTop(40).reduced(10));
    backButton.setBounds(buttonArea.removeFromTop(40).reduced(10));
}



void AccountCreationComponent::buttonClicked(juce::Button* button) {
    if (button == &createAccountButton) {
        juce::String username = usernameTextBox.getText();
        juce::String password = passwordTextBox.getText();
        juce::String confirmPassword = confirmPasswordTextBox.getText();

        if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
            juce::AlertWindow::showMessageBoxAsync(
                juce::AlertWindow::WarningIcon,
                "Error",
                "Please fill in all fields."
            );
            return;
        }

        if (password != confirmPassword) {
            juce::AlertWindow::showMessageBoxAsync(
                juce::AlertWindow::WarningIcon,
                "Error",
                "Passwords do not match."
            );
            return;
        }

        if (!userManager.isUniqueUsername(username.toStdString()))
        {
            juce::AlertWindow::showMessageBoxAsync(
                juce::AlertWindow::WarningIcon,
                "Error",
                "Username already exists."
            );
            return;
        }

        if (!userManager.validatePassword(password.toStdString()))
        {
            juce::AlertWindow::showMessageBoxAsync(
                juce::AlertWindow::WarningIcon,
                "Error",
                "Password does not meet complexity requirements."
            );
            return;
        }

        // Save user data
        if (userManager.createUser(username.toStdString(), password.toStdString()))
        {
            userManager.saveUsers();
            juce::AlertWindow::showMessageBoxAsync(
                juce::AlertWindow::InfoIcon,
                "Success",
                "Account created successfully!"
            );
            parentComponent.showMainScreen(); // Navigate back to main screen
        }
        else
        {
            juce::AlertWindow::showMessageBoxAsync(
                juce::AlertWindow::WarningIcon,
                "Error",
                "Failed to save account. Please try again."
            );
        }
    }
    else if (button == &backButton) {
        parentComponent.showMainScreen(); // Navigate back to the main screen
    }
}
