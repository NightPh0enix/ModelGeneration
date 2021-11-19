# ModelGeneration
This code generates the X,Y,Z tool position which are calculated from the DDA output. 

Input : DDA debug data in the following order

                1. Total length of the move (not just for one axis but the total distance in hypercuboid space, which is not equal to the algebraic sum of the moves)
                2. Starting x co-ordinate for a move 
                3. Starting y co-ordinate for a move
                4. Starting z co-ordinate for a move 
                5. Amount moved in x direction 
                6. Amount moved in y direction
                7. Amount moved in z direction
                8. Acceleration stop time 
                9. Steady time (the amount of time the move moves with constant speed)
                10. Deceleration start time 
                11. Total move time 
                12. Start velocity 
                13. Top velocity 
                14. End velocity
                15. Direction of the move i.e. forward direction (1) and backward direction (0)
           
Output : The XYZ positions for every move

Run the graphing.py to generate the plot after running the C++ file.
