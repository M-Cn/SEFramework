#ifndef MDP_H
#define MDP_H

#include "../mocc/mocc.hpp"
#include "Parameter.h"

namespace rlib
{
    class MDP
    {
    public:
        class StateTransition
        {
        protected:
            uint32_t m_id;
            uint32_t m_nextStateID;
            real_t m_transitProbability;
            real_t m_cost;

        public:
            StateTransition(uint32_t id, uint32_t nextStateID, real_t prob, real_t cost) : m_id(id), m_nextStateID(nextStateID), m_transitProbability(prob), m_cost(cost) {}
            ~StateTransition() = default;

            uint32_t getId() const { return m_id; }
            uint32_t getNextStateID() const { return m_nextStateID; }
            real_t getTransitProbability() const { return m_transitProbability; }
            real_t getCost() const { return m_cost; }
        };

        class State
        {
        private:
            MDP* m_owner;
            uint32_t m_id;
            std::vector<StateTransition*> m_transitions;
        public:
            State(MDP* owner, uint32_t id) : m_owner(owner), m_id(id) {}
            ~State();

            uint32_t getId() const { return m_id; }
            
            size_t getNumTransitions() const { return m_transitions.size(); }
            StateTransition* getTransition(size_t index);
            StateTransition* getTransitionToState(uint32_t nextStateID);

            void addTransition(StateTransition* transition) { m_transitions.push_back(transition); }

            bool isTerminal() const;
            void update() const;

            bool areTransitionsValid() const;
        };

    protected:
        std::vector<State*> m_states;
        uint32_t m_currentState;
        real_t m_totalCost;
    public:
        MDP() : m_currentState(-1), m_totalCost(0.0) {}
        MDP(int numStates);

        ~MDP();

        /*
        Initializes the MDP.
        */
        void initialize();

        /*
        Finalizes the MDP.
        */
        void finalize();

        /*
        Updates the MDP by transitioning to the next state based on transition probabilities.
        */
        void update();

        /*
        Returns a pointer to the state with the given ID.
        Parameters:
        - id: The ID of the state to retrieve.
        Returns:
        - A pointer to the State object.
        */
        State* getState(const uint32_t id);

        /*
        Returns a pointer to the state at the given index.
        Parameters:
        - index: The index of the state to retrieve.
        Returns:
        - A pointer to the State object.
        */
        State* getStateAt(const uint32_t index);

        /*
        Returns a pointer to the current state.
        */
        State* getCurrentState();
        
        size_t getNumStates() const { return m_states.size(); }
        uint32_t getCurrentStateIndex() const { return m_currentState; }
        real_t getTotalCost() const { return m_totalCost; }

        /*
        Adds a new state to the MDP.
        Parameters:
        - state: The state to be added.
        */
        void addState(State* state) { m_states.push_back(state); }

        /*
        Checks if the current state is terminal.
        Returns:
        - true if the current state is terminal, false otherwise.
        */
        bool isTerminal() { return getCurrentState()->isTerminal(); }

        /*
        Resets the MDP to its initial state.
        */
        void reset();
    };
} // namespace rlib

#endif // MDP_H