This code put ‘1’ on a certain line, and check all the possible spots to put ‘1’ on the rest of the line. If it can’t find spots on each line, then this code go back to the certain line and change the place of ‘1’. By keep doing this, this function finds the solution and print it.



gcc -o 8queens-one-soln 8queens-one-soln.c
./8queens-one-soln

gcc -o 8queens-all-solns 8queens-all-solns.c
./8queens-all-solns