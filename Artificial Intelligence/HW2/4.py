# The code implements the AND-OR search algorithm for the vacuum world problem.

from print_color import print

condition = []
flag = 0

# Define the vacuum world class
class vacum_world:
    def __init__(self, initial_state):
        self.INITIAL = initial_state

    def ACTIONS(self, state):
        actions = []

        # In the vacuum world, we can have different actions according to the state

        if state[0] == 'Dirty' and state[2] == "Left":
            actions.append('Suck')

        if state[1] == 'Dirty' and state[2] == "Right":
            actions.append('Suck')

        if state[2] == "Left" and state[0] == "Clean":
            actions.append('Suck')

        if state[2] == "Right" and state[1] == "Clean":
            actions.append('Suck')

        if state[2] == 'Left':
            actions.append('Right')

        if state[2] == 'Right':
            actions.append('Left')

        return actions

    def RESULTS(self, state, action):
        states = []

        # According to the current state and action, what states can we go to

        if state[2] == "Left":
            if action == "Suck":

                if state[0] == "Dirty" and state[1] == "Dirty":
                    states.append(("Clean", "Clean", "Left"))

                if state[0] == "Dirty":
                    states.append(("Clean", state[1], "Left"))
                
                if state[0] == "Clean":
                    states.append(("Dirty", "Dirty", "Left"))
                    states.append(state)

            elif action == "Right":
                states.append((state[0], state[1], "Right"))
                
            else:
                states.append(state)
        else:
            if action == "Suck":

                if state[1] == "Dirty" and state[0] == "Dirty":
                    states.append(("Clean", "Clean", "Right"))

                if state[1] == "Dirty":
                    states.append((state[0], "Clean", "Right"))
                
                if state[1] == "Clean":
                    states.append(("Dirty", "Dirty", "Right"))
                    states.append(state)

            elif action == "Left":
                states.append((state[0], state[1], "Left"))

            else:
                states.append(state)

        return states

    def IS_GOAL(self, state): # Checking to see if we have reached the goal (both rooms are clean)
        return state[0] == state[1] == "Clean"

    def IS_CYCLE(self, state, path): # Don't create a loop, let's check if we haven't seen this state before
        return state in path
    
# Define the AND-OR search algorithm
# The main function AND_OR_SEARCH calls the OR_SEARCH function -
# on the initial state, and if it fails, then it returns the string "failure". 
def AND_OR_SEARCH(problem):
    return OR_SEARCH(problem, problem.INITIAL, [])

def OR_SEARCH(problem, state, path):
    #  These conditions are used for when we reach 2 answers
    #  (for example, if we are in the left house and both houses are dirty, we have 2 answers)
    #  and we keep a state that if we do not go to it, we can reach another answer
    #  (for a better understanding of this Run the code and look at the output.)
    if problem.IS_GOAL(state):
        global flag
        global condition
        if not flag:
            if len(path):
                condition.append(state)
                condition.append(path[0])
        flag=flag+1    # Increase flag for check condition

        # If we have reached a goal, we add the path we have taken so far to the state and return it.
        return [path + [state]]
    # If a loop is created, we return failure (we've seen this before).
    if problem.IS_CYCLE(state, path):
        return "failure"
    # According to the current state, we get all the actions we can do and use them in the next step in the RESULTS function.
    for action in problem.ACTIONS(state):
        # Here are the inputs to the and function,
        # the problem, the states we can go to (using the action),
        #  the path we've traveled so far, plus the current state.
        plan = AND_SEARCH(problem, problem.RESULTS(state, action), path + [state])
        if plan != "failure":
            return plan # If there was no failure, we will return the plan
    return "failure"

# The AND_SEARCH function gets a list of states and calls the OR_SEARCH function on each state. 
# If it returns "failure" for any state, then the function returns "failure". 
# Otherwise, the function returns a list of plan
def AND_SEARCH(problem, states, path):
    plans = []
    for si in states:
        plan_i = OR_SEARCH(problem, si, path)
        if plan_i == "failure":
            return "failure"
        plans += plan_i
    return plans



initial_state = ('Dirty', 'Dirty', 'Left')
vacuum_problem = vacum_world(initial_state)
# We give the initial node to this function
conditional_plan = AND_OR_SEARCH(vacuum_problem)

if conditional_plan!= "failure":
    for i in range(len(conditional_plan)):
        if not i:
           
           print(conditional_plan[i], tag="We reached the goal" , tag_color="green",color='b')
           if len(conditional_plan) > 1: # These are written for answers that have more than one way to achieve a goal
               print('\nor\n') 

        else:
            # These are written for answers that have more than one way to achieve a goal

            print("if",condition[1]," does not go to ",condition[0],
                  " by suction action!",", Our other path to achieve the goal with this condition :" , color="red")
            
            print(conditional_plan[i] , tag="We reached the goal with the above condition",tag_color="green", color='b')    
# If no answer is found            
else:
    print("We did not reach the goal" , tag="Failure" , tag_color="red",color="yellow")