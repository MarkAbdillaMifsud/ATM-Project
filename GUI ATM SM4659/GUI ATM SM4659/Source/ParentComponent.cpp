#include "ParentComponent.h"
#include "MainComponent.h"
#include "AccountCreationComponent.h"


ParentComponent::ParentComponent() : userManager()
{
    // Initialize MainComponent
    mainComponent = std::make_unique<MainComponent>(*this);
    addAndMakeVisible(*mainComponent);

    // AccountCreationComponent will be created when needed
    accountCreationComponent = nullptr;

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
        mainComponent = std::make_unique<MainComponent>(*this);
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