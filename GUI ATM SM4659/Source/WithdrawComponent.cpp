#include "WithdrawComponent.h"
#include "AccountManagementComponent.h"
#include "../../Console ATM SM4659/SavingsAccount.h"
#include "../../Console ATM SM4659/CurrentAccount.h"

WithdrawComponent::WithdrawComponent(AccountManagementComponent* parentComponent, UserManager& userManager, BankAccountManager& bankAccountManager)
    : parentComponent(parentComponent), userManager(userManager), bankAccountManager(bankAccountManager) 
{
    accountLabel.setText("Select Account:", juce::dontSendNotification);
    accountLabel.attachToComponent(&accountComboBox, true);
    addAndMakeVisible(accountLabel);
    addAndMakeVisible(accountComboBox);

    amountLabel.setText("Withdraw Amount (EUR):", juce::dontSendNotification);
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

WithdrawComponent::~WithdrawComponent() {
    confirmButton.removeListener(this);
    cancelButton.removeListener(this);
}

void WithdrawComponent::paint(juce::Graphics& g) {
    // Fill background
    g.fillAll(juce::Colours::lightgrey);

    // Draw a border around the component
    g.setColour(juce::Colours::black);
    g.drawRect(getLocalBounds(), 1);
}

void WithdrawComponent::resized() {
    auto area = getLocalBounds().reduced(20);

    // Layout Labels and Inputs
    accountComboBox.setBounds(area.removeFromTop(30));
    amountTextBox.setBounds(area.removeFromTop(30));

    // Layout Buttons
    auto buttonArea = area.removeFromTop(40);
    confirmButton.setBounds(buttonArea.removeFromLeft(buttonArea.getWidth() / 2 - 10));
    cancelButton.setBounds(buttonArea.removeFromLeft(buttonArea.getWidth()));
}

void WithdrawComponent::populateAccountComboBox() {
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

void WithdrawComponent::buttonClicked(juce::Button* button)
{
    if (button == &confirmButton) {
        performWithdraw();
    }
    else if (button == &cancelButton) {
        if (parentComponent) {
            parentComponent->removeWithdrawComponent(this);
        }
    }
}

void WithdrawComponent::performWithdraw()
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

    juce::String withdrawAmountText = amountTextBox.getText();
    double withdrawAmount = withdrawAmountText.getDoubleValue();

    if (withdrawAmount <= 0) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Invalid Amount",
            "Please enter a positive amount."
        );
        return;
    }

    const auto& bankAccounts = user->getAllBankAccounts();
    if (selectedAccountIndex >= bankAccounts.size()) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Invalid Selection",
            "Selected account index is out of range."
        );
        return;
    }

    auto selectedAccountIt = std::next(bankAccounts.begin(), selectedAccountIndex);
    auto selectedAccount = selectedAccountIt->second;

    // Determine the account type
    std::string accountType = selectedAccount->getAccountType(); // Assuming getAccountType() returns "Current" or "Savings"

    try {
        if (withdrawAmount > selectedAccount->getBalance()) {
            if (accountType == "Current") {
                // Apply 10% fee on the withdrawal amount
                double fee = withdrawAmount * 0.10;
                double totalWithdrawal = withdrawAmount + fee;

                // Perform withdrawal with fee
                selectedAccount->withdrawMoney(totalWithdrawal); // Allows negative balance

                // Notify the user
                juce::AlertWindow::showMessageBoxAsync(
                    juce::AlertWindow::InfoIcon,
                    "Success",
                    juce::String("Withdrawal successful!\nOverdraft Fee: EUR " + juce::String(fee) + "\n" +
                        "Updated Balance: EUR " + juce::String(selectedAccount->getBalance()))
                );
            }
            else {
                // SavingsAccount: insufficient funds
                selectedAccount->withdrawMoney(withdrawAmount); // Will throw an exception
            }
        }
        else {
            // Sufficient funds, proceed normally
            selectedAccount->withdrawMoney(withdrawAmount);

            // Notify the user
            juce::AlertWindow::showMessageBoxAsync(
                juce::AlertWindow::InfoIcon,
                "Success",
                "Withdrawal successful!\nUpdated Balance: EUR " + juce::String(selectedAccount->getBalance())
            );
        }
    }
    catch (const std::runtime_error& e) {
        // Handle insufficient funds for SavingsAccount
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Insufficient Funds",
            e.what()
        );
        return;
    }

    // Save the updated account data
    bankAccountManager.saveAccounts();

    // Reset the amount text box
    amountTextBox.setText("0.0", juce::dontSendNotification);

    // Refresh the account ComboBox to reflect the updated balance
    populateAccountComboBox();

    // Notify the parent component to remove this WithdrawComponent
    if (parentComponent) {
        parentComponent->removeWithdrawComponent(this);
    }
}