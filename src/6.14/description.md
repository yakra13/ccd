# 6.14 Given a specification for a stateful application or protocol, describe and/or draw a diagram of the possible states it can have

### Objectives

- [ ] Show or describe the conditions necessary to be in the initial state
- [ ] Show or describe the conditions necessary to get to the final state
- [ ] Show or describe the input/output generated (if any) during the change between each possible state
- [ ] Show or describe criteria necessary to change between each possible state
- [ ] Show or describe the relationship (if any) between each state in the program
- [ ] Account for any possible error conditions that may occur during state transitions


### Answers
**Overview**
> A small example of stateful code is provided written in C++ for the Unreal Engine.

**Show or describe the conditions necessary to be in the initial state**
> The initial state is the idle state. This is the default state that is given upon creation of a player. It derives from BaseState. The conditions in this case is effectively just starting the program/spawning a player.

**Show or describe the conditions necessary to get to the final state**
> While technically in this example there is no final state a rough equivalent would be the death state. The conditions to meet this state is that the player life attribute reaches 0. This value is retrieved thru PlayerRef (line 21 BaseState.h)

**Show or describe the input/output generated (if any) during the change between each possible state**
> The changing of states is handled by the state manager component assigned to a player (file not provided but excerpt included below). A call to SwitchStateByKey() performs the state transition. Note the calls to OnExitState() and OnEnterState() are where any input/output will be consumed/produced during a transition. Line 16/17 in WalkState.cpp shows output that occurs when switching (displaying the state name to the console for debugging purposes):

    void UStateManagerComponent::SwitchStateByKey(FString key)
    {
        UStateBase* newState = StateMap.FindRef(key);

        // If there is no state just enter the new state as the initial state.
        if (!CurrentState)
        {
            CurrentState = newState;
            CurrentState->IsValidEnterState(GetOwner());
        }
        else
        {
            ...

            // Determine if there are any state conditions that must be met prior to entering the state.
            if (!newState->IsValidEnterState(GetOwner()))
                return;

            // Cleanly exit the current state
            CurrentState->OnExitState();
            
            ...

            // Set the new state as current
            CurrentState = newState;
        }

        // Perform any enter state actions
        CurrentState->OnEnterState(GetOwner());
    }

**Show or describe criteria necessary to change between each possible state**
> Each state has its own criteria both for exiting and entering. A good example of this is DashState.cpp lines 32-46. This state can be entered either from idle or walk by pressing the 'dash button' but cannot exit until the dash timer expires. (TickState() line 32 is called 60 times per second)

**Show or describe the relationship (if any) between each state in the program**
> Each state in this example represents what a player is currently doing effectively. As such the states are non-linear generally and are connected more like a web. 

**Account for any possible error conditions that may occur during state transitions**
> This is generally handled by IsValidEnterState(), here conditions can be checked on a per state basis to prevent erroneous state transitions. In the examples all states always gurantee a reference to the player exists before allowing a transition. Additionally states could check the players condition here; for example the player could have an attribute like 'canDash' which must be true for the dash state transition to be valid. If not then the dash state can handle that in IsValidEnterState() by reporting that dashing is not possible and returning to the previous state. As opposed to doing this check in every state that can transition to a dash state.
