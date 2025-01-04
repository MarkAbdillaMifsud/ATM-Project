#include "AccountManagementComponent.h"
#include "TransferComponent.h"
#include "../../Console ATM SM4659/SavingsAccount.h"
#include "../../Console ATM SM4659/CurrentAccount.h"

AccountManagementComponent::AccountManagementComponent(ParentComponent& parent, UserManager& userManager, BankAccountManager& bankAccountManager) : parentComponent(parent), userManager(userManager), bankAccountManager(bankAccountManager)
{
	titleLabel.setText("Welcome " + userManager.getLoggedInUser()->getUsername(), juce::dontSendNotification);
	titleLabel.setJustificationType(juce::Justification::centred);
	titleLabel.setFont(juce::Font(24.0f, juce::Font::bold));
	addAndMakeVisible(titleLabel);

	withdrawButton.setButtonText("Withdraw");
	withdrawButton.addListener(this);
	addAndMakeVisible(withdrawButton);

    depositButton.setButtonText("Deposit");
    depositButton.addListener(this);
    addAndMakeVisible(depositButton);

    balanceButton.setButtonText("View Balance");
    balanceButton.addListener(this);
    addAndMakeVisible(balanceButton);

    creationButton.setButtonText("Create an Account");
    creationButton.addListener(this);
    addAndMakeVisible(creationButton);

    transferButton.setButtonText("Transfer Funds");
    transferButton.addListener(this);
    addAndMakeVisible(transferButton);

    logoutButton.setButtonText("Logout");
    logoutButton.addListener(this);
    addAndMakeVisible(logoutButton);

    setSize(400, 300);
}

AccountManagementComponent::~AccountManagementComponent(){}

void AccountManagementComponent::buttonClicked(juce::Button* button) {
    if (button == &withdrawButton) {
        User* user = userManager.getLoggedInUser();

        if (!user || user->isZeroBankAccounts()) {
            juce::AlertWindow::showMessageBoxAsync(
                juce::AlertWindow::WarningIcon,
                "No Accounts",
                "You do not have any accounts linked. Please create one first."
            );
            return;
        }
        if (withdrawComponent == nullptr) {
            withdrawComponent = new WithdrawComponent(this, userManager, bankAccountManager);
            addAndMakeVisible(withdrawComponent);
            withdrawComponent->toFront(true);
        }
    } else if (button == &depositButton) {
        User* user = userManager.getLoggedInUser();

        if (!user || user->isZeroBankAccounts()) {
            juce::AlertWindow::showMessageBoxAsync(
                juce::AlertWindow::WarningIcon,
                "No Accounts",
                "You do not have any accounts linked. Please create one first."
            );
            return;
        }

        if (depositComponent == nullptr) {
            depositComponent = new DepositComponent(parentComponent, userManager, bankAccountManager);
            addAndMakeVisible(depositComponent);
            depositComponent->toFront(true);
        }
    } else if (button == &balanceButton) {
        User* user = userManager.getLoggedInUser();
        if (!user || user->isZeroBankAccounts()) {
            juce::AlertWindow::showMessageBoxAsync(
                juce::AlertWindow::WarningIcon,
                "No Accounts",
                "You do not have any accounts linked. Please create one first."
            );
            return;
        }

        std::stringstream balances;
        balances << "Your Account Balances:\n\n";
        for (const auto& accountPair : user->getAllBankAccounts()) {
            auto account = accountPair.second;

            std::string accountType = dynamic_cast<SavingsAccount*>(account.get()) ? "Savings Account" :
                dynamic_cast<CurrentAccount*>(account.get()) ? "Current Account" :
                "Bank Account";

            balances << "Account Number: " << account->getAccountNumber() << "\n"
                << "Account Type: " << accountType << "\n"
                << "Balance: EUR " << account->getBalance() << "\n\n";
        }

        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::InfoIcon,
            "Account Balances",
            balances.str()
        );
    }
    else if (button == &creationButton) {
        parentComponent.showBankAccountCreationScreen();
    } else if (button == &transferButton) {
        User* user = userManager.getLoggedInUser();
        if (!user || user->isZeroBankAccounts()) {
            juce::AlertWindow::showMessageBoxAsync(
                juce::AlertWindow::WarningIcon,
                "No Accounts",
                "You do not have any accounts linked. Please create one first."
            );
            return;
        }

        if (transferComponent == nullptr) {
            transferComponent = new TransferComponent(this, userManager, bankAccountManager);
            addAndMakeVisible(transferComponent);
            transferComponent->toFront(true);
       }
    } else if (button == &logoutButton) {
        parentComponent.showMainScreen();
    }
}

void AccountManagementComponent::handleDepositResponse() {
    if (!alertWindow) return;

    int selectedAccountIndex = alertWindow->getComboBoxComponent("accountList")->getSelectedItemIndex();
    if (selectedAccountIndex < 0) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Invalid Selection",
            "Please select a valid account."
        );
        alertWindow.reset();
        return;
    }

    auto depositAmountText = alertWindow->getTextEditor("depositAmount")->getText();
    float depositAmount = depositAmountText.getFloatValue();

    if (depositAmount <= 0) {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Invalid Amount",
            "Please enter a positive amount."
        );
        alertWindow.reset();
        return;
    }

    const auto& bankAccounts = userManager.getLoggedInUser()->getAllBankAccounts();
    auto selectedAccountIt = std::next(bankAccounts.begin(), selectedAccountIndex);
    auto selectedAccount = selectedAccountIt->second;

    selectedAccount->depositMoney(depositAmount);

    juce::AlertWindow::showMessageBoxAsync(
        juce::AlertWindow::InfoIcon,
        "Success",
        "Deposit successful! Updated balance: EUR " + juce::String(selectedAccount->getBalance())
    );

    alertWindow.reset();
}

void AccountManagementComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgrey);
}

void AccountManagementComponent::resized()
{
    auto area = getLocalBounds().reduced(20);

    // Reserve space for the title label
    auto headerArea = area.removeFromTop(40);
    titleLabel.setBounds(headerArea);

    // Dynamically calculate the button height and spacing
    const int buttonHeight = (area.getHeight() - 50) / 6; // 6 buttons total

    // Set bounds for each button, ensuring all fit within the area
    withdrawButton.setBounds(area.removeFromTop(buttonHeight).reduced(5));
    depositButton.setBounds(area.removeFromTop(buttonHeight).reduced(5));
    balanceButton.setBounds(area.removeFromTop(buttonHeight).reduced(5));
    creationButton.setBounds(area.removeFromTop(buttonHeight).reduced(5));
    transferButton.setBounds(area.removeFromTop(buttonHeight).reduced(5));
    logoutButton.setBounds(area.removeFromTop(buttonHeight).reduced(5));
}

void AccountManagementComponent::removeWithdrawComponent(WithdrawComponent* wComponent) {
    if (wComponent == withdrawComponent) {
        removeChildComponent(withdrawComponent);
        delete withdrawComponent;
        withdrawComponent = nullptr;
        repaint();
    }
}

void AccountManagementComponent::removeTransferComponent(TransferComponent* tComponent) {
    if (tComponent == transferComponent) {
        removeChildComponent(transferComponent);
        delete transferComponent;
        transferComponent = nullptr;
        repaint();
    }
}