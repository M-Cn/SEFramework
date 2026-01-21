#include "Mdp.h"
#include "Rng.h"

#include "Debug.h"
#include "GeneralUtil.h"

namespace rlib
{
    MDP::State::~State()
    {
        for (size_t i = 0; i < m_transitions.size(); ++i)
            delete m_transitions[i];
        
        m_transitions.clear();
    }

    MDP::StateTransition* MDP::State::getTransition(size_t index)
    {
        if (index < m_transitions.size())
            return m_transitions[index];

        REPORT_PANIC("MDP::State::getTransition: index out of range");
    }

    MDP::StateTransition* MDP::State::getTransitionToState(uint32_t nextStateID)
    {
        for (size_t i = 0; i < m_transitions.size(); ++i)
        {
            if (m_transitions[i]->getNextStateID() == nextStateID)
                return m_transitions[i];
        }

        return nullptr;
    }

    bool MDP::State::isTerminal() const
    {
        bool hasTransitionsToOtherStates = false;

        for (size_t i = 0; i < m_transitions.size(); ++i)
        {
            if (m_transitions[i]->getNextStateID() != m_id)
            {
                hasTransitionsToOtherStates = true;
                break;
            }
        }

        return !hasTransitionsToOtherStates;
    }
    
    void MDP::State::update() const
    {
        if (!areTransitionsValid())
            REPORT_PANIC("MDP::State::update: transition probabilities do not add up to 1.0");
      
        real_t randValue = DefaultRng::getInstance()->getRandomReal(0.f, 1.f);
        real_t cumulativeProb = 0.f;

        for (size_t i = 0; i < m_transitions.size(); ++i)
        {
            cumulativeProb += m_transitions[i]->getTransitProbability();

            if (randValue <= cumulativeProb)
            {
                m_owner->m_totalCost += m_transitions[i]->getCost();
                m_owner->m_currentState = m_transitions[i]->getNextStateID();

                LOG_DEBUG("MDP transitioning from state %u to state %u with cost %.3f\n", m_id, m_transitions[i]->getNextStateID(), m_transitions[i]->getCost());
                return;
            }
        }

        REPORT_PANIC("MDP::State::update: failed to determine next state for transition");
    }

    bool MDP::State::areTransitionsValid() const
    {
        real_t totalProb = 0.f;

        for (size_t i = 0; i < m_transitions.size(); ++i)
            totalProb += m_transitions[i]->getTransitProbability();

        return ARE_REALS_EQUAL(totalProb, 1.f);
    }

    MDP::MDP(int numStates)
    {
        m_states.reserve(numStates);

        for (int i = 0; i < numStates; i++)
            m_states.push_back(new State(this, i));

        m_currentState = 0;
    }

    MDP::~MDP()
    {
        finalize();
    }

    MDP::State* MDP::getState(const uint32_t id)
    {
        for (size_t i = 0; i < m_states.size(); i++)
        {
            if (m_states[i]->getId() == id)
                return m_states[i];
        }

        REPORT_PANIC("MDP::getState: state ID not found");
    }

    MDP::State* MDP::getStateAt(const uint32_t index)
    {
        if (index < static_cast<uint32_t>(m_states.size()))
            return m_states[index];

        REPORT_PANIC("MDP::getState: index out of range");
    }

    MDP::State* MDP::getCurrentState()
    {
        if (m_currentState < static_cast<uint32_t>(m_states.size()))
            return m_states[m_currentState];

        REPORT_PANIC("MDP::getCurrentState: current state index out of range");
    }

    void MDP::initialize()
    {
        reset();
    }

    void MDP::finalize()
    {
        for (size_t i = 0; i < getNumStates(); i++)
            delete m_states[i];
        
        m_states.clear();

        reset();
    }

    void MDP::update()
    {
        if (m_states.empty()) return;

        State* currentState = getCurrentState();

        currentState->update();
    }

    void MDP::reset()
    {
        m_currentState = 0;
        m_totalCost = 0.0;
    }
} // namespace rlib