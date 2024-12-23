#include "ParentComponent.h"
#include "MainComponent.h"
#include "AccountCreationComponent.h"
#include "AccountManagementComponent.h"


ParentComponent::ParentComponent() : userManager()
{
    // Initialize MainComponent
    mainComponent = std::make_unique<MainComponent>(*this, userManager);
    addAndMakeVisible(*mainComponent);

    // AccountCreationComponent will be created when needed
    accountCreationComponent = nullptr;

    //AccountManagementComponent will be created when needed
    accountManagementComponent = nullptr;

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
        accountCreationComponent->setBounds(getLocalBounds()); // Ensure proper bounds
}

void ParentComponent::showMainScreen()
{
    if (accountCreationComponent)
    {
        removeChildComponent(accountCreationComponent.get());
        accountCreationComponent.reset();
    }

    if (!mainComponent)
    {
        mainComponent = std::make_unique<MainComponent>(*this, userManager);
        addAndMakeVisible(*mainComponent);
    }
}

void ParentComponent::showAccountCreationScreen()
{
    if (mainComponent)
    {
        removeChildComponent(mainComponent.get());
        mainComponent.reset();
    }

    if (!accountCreationComponent)
    {
        accountCreationComponent = std::make_unique<AccountCreationComponent>(*this, userManager);
        addAndMakeVisible(*accountCreationComponent);
    }
}

void ParentComponent::showAccountManagementScreen() {
    if (mainComponent) {
        removeChildComponent(mainComponent.get());
        mainComponent.reset();
    }

    if (!accountCreationComponent) {
        accountManagementComponent = std::make_unique<AccountManagementComponent>(*this, userManager);
        addAndMakeVisible(*accountManagementComponent);
    }

    accountManagementComponent->setBounds(getLocalBounds());
}