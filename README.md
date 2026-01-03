Code for quantifier elimination in Real Algebraic Geometry. All results are exact, which is achieved by using FLINT (Fast Library for Number Theory).

# What is this code for?

In short, I want to use it for solving problems in Quantum Information Theory. Now the not so short answer. Many sets in Quantum Information Theory are semialgebraic sets. Quantifier elimination can then be used to determine if such a semialgebraic set is empty or not. We may want more information than that, but it already gives a constraint for some problems to have a solution. With such constraint, we can then narrow down the search space, discarding candidates that aren't solutions to a problem. With less candidates, it may then be possible to solve the problem with other techniques.
