#include "ParentComponent.h"
#include "MainComponent.h"
#include "AccountCreationComponent.h"
#include "AccountManagementComponent.h"
#include "BankAccountCreationComponent.h"


ParentComponent::ParentComponent() : bankAccountManager(userManager)
{
    // Initialize MainComponent
    mainComponent = std::make_unique<MainComponent>(*this, userManager);
    addAndMakeVisible(*mainComponent);

    // AccountCreationComponent will be created when needed
    accountCreationComponent = nullptr;
    accountManagementComponent = nullptr;
    bankAccountCreationComponent = nullptr;

    userManager.loadUsers();
    bankAccountManager.loadAccounts();

    setSize(400, 300);
}

ParentComponent::~ParentComponent() {}

void ParentComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgrey);
}

void ParentComponent::resized()
{
    if (mainComponent)
        mainComponent->setBounds(getLocalBounds());

    if (accountCreationComponent)
        accountCreationComponent->setBounds(getLocalBounds());

    if (accountManagementComponent)
        accountManagementComponent->setBounds(getLocalBounds());

    if (bankAccountCreationComponent)
        bankAccountCreationComponent->setBounds(getLocalBounds());
}

void ParentComponent::showMainScreen()
{
    if (accountCreationComponent)
    {
        removeChildComponent(accountCreationComponent.get());
        accountCreationComponent.reset();
    }

    if (accountManagementComponent)
    {
        removeChildComponent(accountManagementComponent.get());
        accountManagementComponent.reset();
    }

    if (bankAccountCreationComponent)
    {
        removeChildComponent(bankAccountCreationComponent.get());
        bankAccountCreationComponent.reset();
    }

    if (!mainComponent)
    {
        mainComponent = std::make_unique<MainComponent>(*this, userManager);
        addAndMakeVisible(*mainComponent);
    }

    resized();
}

void ParentComponent::showAccountCreationScreen()
{
    if (mainComponent)
    {
        removeChildComponent(mainComponent.get());
        mainComponent.reset();
    }

    if (accountManagementComponent)
    {
        removeChildComponent(accountManagementComponent.get());
        accountManagementComponent.reset();
    }

    if (bankAccountCreationComponent)
    {
        removeChildComponent(bankAccountCreationComponent.get());
        bankAccountCreationComponent.reset();
    }

    if (!accountCreationComponent)
    {
        accountCreationComponent = std::make_unique<AccountCreationComponent>(*this, userManager);
        addAndMakeVisible(*accountCreationComponent);
    }

    resized();
}

void ParentComponent::showAccountManagementScreen()
{
    if (mainComponent)
    {
        removeChildComponent(mainComponent.get());
        mainComponent.reset();
    }

    if (accountCreationComponent)
    {
        removeChildComponent(accountCreationComponent.get());
        accountCreationComponent.reset();
    }

    if (bankAccountCreationComponent)
    {
        removeChildComponent(bankAccountCreationComponent.get());
        bankAccountCreationComponent.reset();
    }

    if (!accountManagementComponent)
    {
        accountManagementComponent = std::make_unique<AccountManagementComponent>(*this, userManager, bankAccountManager);
        addAndMakeVisible(*accountManagementComponent);
    }

    accountManagementComponent->setBounds(getLocalBounds());
    resized();
}

void ParentComponent::showBankAccountCreationScreen()
{
    if (mainComponent)
    {
        removeChildComponent(mainComponent.get());
        mainComponent.reset();
    }

    if (accountCreationComponent)
    {
        removeChildComponent(accountCreationComponent.get());
        accountCreationComponent.reset();
    }

    if (accountManagementComponent)
    {
        removeChildComponent(accountManagementComponent.get());
        accountManagementComponent.reset();
    }

    if (!bankAccountCreationComponent)
    {
        bankAccountCreationComponent = std::make_unique<BankAccountCreationComponent>(*this, userManager, bankAccountManager);
        addAndMakeVisible(*bankAccountCreationComponent);
    }

    bankAccountCreationComponent->setBounds(getLocalBounds());
    resized();
}