#include "AccountManagementComponent.h"
#include "ParentComponent.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"

AccountManagementComponent::AccountManagementComponent(ParentComponent& parent, UserManager& userManager) : parentComponent(parent), userManager(userManager)
{
	titleLabel.setText("Account Management", juce::dontSendNotification);
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
        // Logic for withdrawing money
    } else if (button == &depositButton) {
        // Logic for depositing money
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
    else if (button == &transferButton) {
        //Logic for transfer
    } else if (button == &logoutButton) {
        parentComponent.showMainScreen();
    }
}

void AccountManagementComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgrey);
}

void AccountManagementComponent::resized()
{
    auto area = getLocalBounds().reduced(20);

    auto headerArea = area.removeFromTop(40);
    titleLabel.setBounds(headerArea);

    auto buttonArea = area.removeFromTop(200);
    withdrawButton.setBounds(buttonArea.removeFromTop(40).reduced(10));
    depositButton.setBounds(buttonArea.removeFromTop(40).reduced(10));
    balanceButton.setBounds(buttonArea.removeFromTop(40).reduced(10));
    transferButton.setBounds(buttonArea.removeFromTop(40).reduced(10));
    logoutButton.setBounds(buttonArea.removeFromTop(40).reduced(10));
}