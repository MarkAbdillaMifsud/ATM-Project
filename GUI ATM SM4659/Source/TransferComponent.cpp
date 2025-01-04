#include "TransferComponent.h"
#include "AccountManagementComponent.h"

TransferComponent::TransferComponent(AccountManagementComponent* parentComponent, UserManager& userManager, BankAccountManager& bankAccountManager) :
	parentComponent(parentComponent), userManager(userManager), bankAccountManager(bankAccountManager)
{
    sourceAccountLabel.setText("Source Account:", juce::dontSendNotification);
    sourceAccountLabel.attachToComponent(&sourceAccountComboBox, true);
    addAndMakeVisible(sourceAccountLabel);
    addAndMakeVisible(sourceAccountComboBox);

    destinationAccountLabel.setText("Destination Account:", juce::dontSendNotification);
    destinationAccountLabel.attachToComponent(&destinationAccountComboBox, true);
    addAndMakeVisible(destinationAccountLabel);
    addAndMakeVisible(destinationAccountComboBox);

    amountLabel.setText("Transfer Amount (EUR):", juce::dontSendNotification);
    amountLabel.attachToComponent(&amountTextBox, true);
    addAndMakeVisible(amountLabel);
    addAndMakeVisible(amountTextBox);

    amountTextBox.setInputRestrictions(10, "0123456789.");
    amountTextBox.setText("0.0");

    confirmButton.setButtonText("Confirm");
    confirmButton.addListener(this);
    addAndMakeVisible(confirmButton);

    cancelButton.setButtonText("Cancel");
    cancelButton.addListener(this);
    addAndMakeVisible(cancelButton);

    populateAccountComboBoxes();

    setSize(400, 250);
}

TransferComponent::~TransferComponent() {
    confirmButton.removeListener(this);
    cancelButton.removeListener(this);
}

void TransferComponent::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::lightgrey);
    g.setColour(juce::Colours::black);
    g.drawRect(getLocalBounds(), 1);
}

void TransferComponent::resized() {
    auto area = getLocalBounds().reduced(20);

    sourceAccountComboBox.setBounds(area.removeFromTop(30));
    destinationAccountComboBox.setBounds(area.removeFromTop(30));
    amountTextBox.setBounds(area.removeFromTop(30));

    auto buttonArea = area.removeFromTop(50);
    confirmButton.setBounds(buttonArea.removeFromLeft(buttonArea.getWidth() / 2 - 10));
    cancelButton.setBounds(buttonArea.removeFromLeft(buttonArea.getWidth()));
}

void TransferComponent::populateAccountComboBoxes() {
    sourceAccountComboBox.clear();
    destinationAccountComboBox.clear();

    User* user = userManager.getLoggedInUser();

    const auto& bankAccounts = user->getAllBankAccounts();

    for (const auto& pair : bankAccounts) {
        auto account = pair.second;
        juce::String accountInfo = "Account Number: " + juce::String(account->getAccountNumber()) +
            " | Balance: EUR " + juce::String(account->getBalance());
        sourceAccountComboBox.addItem(accountInfo, sourceAccountComboBox.getNumItems() + 1);
    }

    for (const auto& pair : bankAccounts) {
        auto account = pair.second;
        juce::String accountInfo = "Account Number: " + juce::String(account->getAccountNumber()) +
            " | Balance: EUR " + juce::String(account->getBalance());
        destinationAccountComboBox.addItem(accountInfo, destinationAccountComboBox.getNumItems() + 1);
    }

    sourceAccountComboBox.setSelectedItemIndex(0);
    destinationAccountComboBox.setSelectedItemIndex(0);
}

void TransferComponent::buttonClicked(juce::Button* button) {
    if (button == &confirmButton) {
        performTransfer();
    }
    else if (button == &cancelButton) {
        if (parentComponent) {
            parentComponent->removeTransferComponent(this);
        }
    }
}

void TransferComponent::performTransfer() {
    User* user = userManager.getLoggedInUser();
    if (!user) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "No User",
            "No user is currently logged in."
        );
        return;
    }

    int sourceIndex = sourceAccountComboBox.getSelectedItemIndex();
    int destinationIndex = destinationAccountComboBox.getSelectedItemIndex();

    if (sourceIndex < 0 || destinationIndex < 0) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Invalid Selection",
            "Please select both source and destination accounts."
        );
        return;
    }

    juce::String amountText = amountTextBox.getText();
    double transferAmount = amountText.getDoubleValue();

    if (transferAmount <= 0) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Invalid Amount",
            "Please enter a positive amount."
        );
        return;
    }

    const auto& bankAccounts = user->getAllBankAccounts();
    if (sourceIndex >= bankAccounts.size() || destinationIndex >= bankAccounts.size()) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Invalid Selection",
            "Selected account index is out of range."
        );
        return;
    }

    auto sourceAccountIt = std::next(bankAccounts.begin(), sourceIndex);
    auto destinationAccountIt = std::next(bankAccounts.begin(), destinationIndex);

    auto sourceAccount = sourceAccountIt->second;
    auto destinationAccount = destinationAccountIt->second;

    if (sourceAccount->getAccountNumber() == destinationAccount->getAccountNumber()) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Same Account",
            "Source and destination accounts cannot be the same."
        );
        return;
    }

    if (transferAmount > sourceAccount->getBalance()) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Insufficient Funds",
            "You do not have enough balance in the source account."
        );
        return;
    }

    // Perform the transfer
    sourceAccount->withdrawMoney(transferAmount);
    destinationAccount->depositMoney(transferAmount);
    bankAccountManager.saveAccounts();

    // Notify the user
    juce::AlertWindow::showMessageBoxAsync(
        juce::AlertWindow::InfoIcon,
        "Success",
        juce::String("Transfer successful!\n") +
        "Source Account Balance: EUR " + juce::String(sourceAccount->getBalance()) + "\n" +
        "Destination Account Balance: EUR " + juce::String(destinationAccount->getBalance())
    );
    amountTextBox.setText("0.0", juce::dontSendNotification);

    if (parentComponent) {
        parentComponent->removeTransferComponent(this);
    }
}
