# ModelGeneration
This code generates the X,Y,Z tool position which are calculated from the DDA output. `Generate_FBS_input.cpp` should be the main file of interest. Also check out the `RPi_Subsystem` repo for real time XYZE values

Input : DDA debug data in a txt file. Data inside the text file is in the following order


                1. Identifier "N"
                2. Total length of the move (not just for one axis but the total distance in hypercuboid space, which is NOT equal to the algebraic sum of the moves)
                3. Starting x co-ordinate for a move 
                4. Starting y co-ordinate for a move
                5. Starting z co-ordinate for a move 
                6. Amount moved in x direction 
                7. Amount moved in y direction
                8. Amount moved in z direction
                9. Acceleration stop time 
                10. Steady time (the amount of time the move moves with constant speed)
                11. Deceleration start time 
                12. Total move time 
                13. Start velocity 
                14. Top velocity 
                15. End velocity
                16. Direction of the move i.e. forward direction (1) and backward direction (0)
           
Output : The XYZ positions for every move

Run the graphing.py to generate the plot after running the C++ file.
