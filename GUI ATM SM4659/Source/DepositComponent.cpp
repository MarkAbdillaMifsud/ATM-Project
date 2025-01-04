#include "DepositComponent.h"

DepositComponent::DepositComponent(ParentComponent& parentComponent, UserManager& userManager, BankAccountManager& bankAccountManager) : parentComponent(parentComponent), userManager(userManager), bankAccountManager(bankAccountManager) {
    accountLabel.setText("Select Account:", juce::dontSendNotification);
    accountLabel.attachToComponent(&accountComboBox, true);
    addAndMakeVisible(accountLabel);
    addAndMakeVisible(accountComboBox);

    amountLabel.setText("Deposit Amount (EUR):", juce::dontSendNotification);
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

    populateAccountComboBox();

    setSize(350, 200);
}

DepositComponent::~DepositComponent()
{
    confirmButton.removeListener(this);
    cancelButton.removeListener(this);
}

void DepositComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgrey);

    g.setColour(juce::Colours::black);
    g.drawRect(getLocalBounds(), 1);
}

void DepositComponent::resized()
{
    auto area = getLocalBounds().reduced(20);

    accountComboBox.setBounds(area.removeFromTop(30));
    amountTextBox.setBounds(area.removeFromTop(30));

    auto buttonArea = area.removeFromTop(40);
    confirmButton.setBounds(buttonArea.removeFromLeft(buttonArea.getWidth() / 2 - 10));
    cancelButton.setBounds(buttonArea.removeFromLeft(buttonArea.getWidth()));
}

void DepositComponent::populateAccountComboBox()
{
    accountComboBox.clear();
    User* user = userManager.getLoggedInUser();

    const auto& bankAccounts = user->getAllBankAccounts();

    for (const auto& pair : bankAccounts) {
        auto account = pair.second;
        juce::String accountInfo = "Account Number: " + juce::String(account->getAccountNumber()) +
            " | Balance: EUR " + juce::String(account->getBalance());
        accountComboBox.addItem(accountInfo, accountComboBox.getNumItems() + 1);
    }

    accountComboBox.setSelectedItemIndex(0);
}

void DepositComponent::buttonClicked(juce::Button* button)
{
    if (button == &confirmButton) {
        performDeposit();
    }
    else if (button == &cancelButton) {
        // Notify parent to remove this component
        parentComponent.removeChildComponent(this);
        delete this;
    }
}

void DepositComponent::performDeposit()
{
    User* user = userManager.getLoggedInUser();
    if (!user) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "No User",
            "No user is currently logged in."
        );
        return;
    }

    int selectedAccountIndex = accountComboBox.getSelectedItemIndex();
    if (selectedAccountIndex < 0) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Invalid Selection",
            "Please select a valid account."
        );
        return;
    }

    juce::String depositAmountText = amountTextBox.getText();
    float depositAmount = depositAmountText.getFloatValue();

    if (depositAmount <= 0) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Invalid Amount",
            "Please enter a positive amount."
        );
        return;
    }

    const auto& bankAccounts = user->getAllBankAccounts();
    auto selectedAccountIt = std::next(bankAccounts.begin(), selectedAccountIndex);
    auto selectedAccount = selectedAccountIt->second;

    // Perform the deposit
    selectedAccount->depositMoney(depositAmount);
    bankAccountManager.saveAccounts();

    // Notify the user
    juce::AlertWindow::showMessageBoxAsync(
        juce::AlertWindow::InfoIcon,
        "Success",
        "Deposit successful!\nUpdated Balance: EUR " + juce::String(selectedAccount->getBalance())
    );

    // Reset the amount text box
    amountTextBox.setText("0.0", juce::dontSendNotification);
}
