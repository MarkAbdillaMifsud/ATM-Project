#include "BankAccountCreationComponent.h"
#include "ParentComponent.h"
#include "../../Console ATM SM4659/SavingsAccount.h"
#include "../../Console ATM SM4659/CurrentAccount.h"

BankAccountCreationComponent::BankAccountCreationComponent(ParentComponent& parent, UserManager& userManager, BankAccountManager& bankAccountManager) : 
    parentComponent(parent), userManager(userManager), bankAccountManager(bankAccountManager) {

	titleLabel.setText("Create Bank Account", juce::dontSendNotification);
	titleLabel.setJustificationType(juce::Justification::centred);
	titleLabel.setFont(juce::Font(24.0f, juce::Font::bold));
	addAndMakeVisible(titleLabel);

    accountNumberLabel.setText("Enter an Account Number: ", juce::dontSendNotification);
    addAndMakeVisible(accountNumberLabel);

    accountNumberInput.setInputRestrictions(10, "0123456789");
    addAndMakeVisible(accountNumberInput);

	savingsButton.setButtonText("Create Savings Account");
	savingsButton.addListener(this);
	addAndMakeVisible(savingsButton);

	currentButton.setButtonText("Create Current Account");
	currentButton.addListener(this);
	addAndMakeVisible(currentButton);

	backButton.setButtonText("Back");
	backButton.addListener(this);
	addAndMakeVisible(backButton);

    submitButton.setButtonText("Submit");
    submitButton.addListener(this);
    addAndMakeVisible(submitButton);

    accountNumberLabel.setVisible(false);
    accountNumberInput.setVisible(false);
    submitButton.setVisible(false);

	setSize(400, 300);
}

BankAccountCreationComponent::~BankAccountCreationComponent() {}

void BankAccountCreationComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgrey);
}

void BankAccountCreationComponent::resized()
{
    auto area = getLocalBounds().reduced(20);

    auto headerArea = area.removeFromTop(40);
    titleLabel.setBounds(headerArea);

    const int buttonHeight = 40;
    accountNumberLabel.setBounds(area.removeFromTop(30).reduced(10));
    accountNumberInput.setBounds(area.removeFromTop(30).reduced(10));
    savingsButton.setBounds(area.removeFromTop(buttonHeight).reduced(10));
    currentButton.setBounds(area.removeFromTop(buttonHeight).reduced(10));
    backButton.setBounds(area.removeFromTop(buttonHeight).reduced(10));
    submitButton.setBounds(area.removeFromTop(buttonHeight).reduced(10));
}

void BankAccountCreationComponent::buttonClicked(juce::Button* button)
{
    if (button == &savingsButton) {
        isCreatingSavingsAccount = true;
        accountNumberLabel.setVisible(true);
        accountNumberInput.setVisible(true);
        submitButton.setVisible(true);
    }
    else if (button == &currentButton) {
        isCreatingSavingsAccount = false;
        accountNumberLabel.setVisible(true);
        accountNumberInput.setVisible(true);
        submitButton.setVisible(true);
    }
    else if (button == &submitButton) {
        if (isCreatingSavingsAccount) {
            handleSavingsAccountCreation();
        }
        else {
            handleCurrentAccountCreation();
        }
    }
    else if (button == &backButton) {
        parentComponent.showAccountManagementScreen(); // Navigate back to the main menu
    }
}

void BankAccountCreationComponent::handleSavingsAccountCreation() {
    User* user = userManager.getLoggedInUser();
    if (!user) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Error",
            "No user is logged in. Please log in first."
        );
        return;
    }

    juce::String accountNumberText = accountNumberInput.getText();

    if (accountNumberText.isEmpty()) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Error",
            "Account number cannot be empty."
        );
        return;
    }

    int accountNumber = accountNumberText.getIntValue();
    if (!bankAccountManager.isUniqueAccountNumber(accountNumber)) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Error",
            "Account number already exists. Please enter a unique account number."
        );
        return;
    }

    std::shared_ptr<BankAccount> newAccount = std::make_shared<SavingsAccount>(accountNumber, user->getUsername());
    user->addBankAccount(newAccount);
    bankAccountManager.addBankAccount(newAccount);
    bankAccountManager.saveAccounts();

    juce::AlertWindow::showMessageBoxAsync(
        juce::AlertWindow::InfoIcon,
        "Success",
        "Savings Account created successfully!"
    );
}

void BankAccountCreationComponent::handleCurrentAccountCreation()
{
    User* user = userManager.getLoggedInUser();
    if (!user) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Error",
            "No user is logged in. Please log in first."
        );
        return;
    }

    juce::String accountNumberText = accountNumberInput.getText();

    if (accountNumberText.isEmpty()) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Error",
            "Account number cannot be empty."
        );
        return;
    }

    int accountNumber = accountNumberText.getIntValue();
    if (!bankAccountManager.isUniqueAccountNumber(accountNumber)) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Error",
            "Account number already exists. Please enter a unique account number."
        );
        return;
    }

    std::shared_ptr<BankAccount> newAccount = std::make_shared<CurrentAccount>(accountNumber, user->getUsername());
    user->addBankAccount(newAccount);
    bankAccountManager.addBankAccount(newAccount);
    bankAccountManager.saveAccounts();

    juce::AlertWindow::showMessageBoxAsync(
        juce::AlertWindow::InfoIcon,
        "Success",
        "Current Account created successfully!"
    );
}

void BankAccountCreationComponent::handleSubmitAccountCreation() {
    User* user = userManager.getLoggedInUser();
    if (!user) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Error",
            "No user is logged in. Please log in first."
        );
        return;
    }

    juce::String accountNumberText = accountNumberInput.getText();

    if (accountNumberText.isEmpty()) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Error",
            "Account number cannot be empty."
        );
        return;
    }

    int accountNumber = accountNumberText.getIntValue();
    if (!bankAccountManager.isUniqueAccountNumber(accountNumber)) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Error",
            "Account number already exists. Please enter a unique account number."
        );
        return;
    }

    std::shared_ptr<BankAccount> newAccount;

    // Create the appropriate account based on the flag
    if (isCreatingSavingsAccount) {
        newAccount = std::make_shared<SavingsAccount>(accountNumber, user->getUsername());
    }
    else {
        newAccount = std::make_shared<CurrentAccount>(accountNumber, user->getUsername());
    }

    // Add the newly created account to the user's bank accounts
    bankAccountManager.addBankAccount(newAccount);
    bankAccountManager.saveAccounts();

    juce::AlertWindow::showMessageBoxAsync(
        juce::AlertWindow::InfoIcon,
        "Success",
        "Account created successfully!"
    );

    // Hide input fields and buttons after account creation
    accountNumberInput.clear();
    accountNumberLabel.setVisible(false);
    accountNumberInput.setVisible(false);
    submitButton.setVisible(false);
}
