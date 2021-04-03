# AIFA_PROJECT

## PROBLEM STATEMENT
Consider a warehouse and a set of robots which pick up items from designated places, deliver those in desired locations, and finally the robots go to the end location. Assume that the warehouse is represented as a 2-D grid of size n × m. Each location (Li) on warehouse floor can be denoted by a pair of integers 
Li = (xi, yi). 
Each cell on the grid can be categorized in one of the following ways (see diagram below) - source location (P1-P3), destination location (D1-D3), temporary storage location (TS1-TS4), obstacle (black square), normal (rest of the cells). Source & destination denote pick-up and drop locations respectively.

Temporary storage location denotes the place where robot can keep some items. Obstacle represents a location where no robot can move. Rest of the cells are considered as normal cell.

Let there be k number of robots and r number of tasks. The details of robot location and tasks are provided as per the following table.

![alt text](https://github.com/armedjuror/AIFA_PROJECT/blob/master/includes/tab_1.png?raw=true)

Assume that the a robot can move at most one cell (either vertically or horizontally) at a time step, a normal cell can be occupied by at most one robot. Source, destination, temporary storage locations can accommodate multiple robots simultaneously. Our target here is develop a work schedule that minimizes the time to complete all tasks. You need to develop both optimal as well as heuristic algorithms.

![alt text](https://github.com/armedjuror/AIFA_PROJECT/blob/master/includes/tab_2.png?raw=true)

## TEAM

1. Mohammad Asjad - 19ME10038
2. Ajwad Juman PC - 19AG10002

## ALGORITHM

### ASSUMPTIONS

1. A robot does a task at a time.
2. Two robots doesn't take tasks simultaneously

### SOME POINTS
1. A* is used for finding shortest path
2. After completing all tasks, we will move robots to their end position.
3. Each point of grid is represented as a pair of numbers where 
    - First number represents as follows :
      - Blocked - Can contain no bot at a time - **(0)** 
      - Normal - Can contain only one bot at a time - **(1)**
      - Special - Can contain more than one bot at a time - **(2)**
      
    - Second Number represents bot present in that cell where **(-1)** represent nil.
4. We have defined an object **bot** which contain start, end and current positions of the bot.
5. We have defined another object **task** which contains : 
    - Pick up location
    - Delivery location 
    - Bot assigned for that task 
        - j   : for jth bot
        - -1  : if tasks is not possible 
        - -2  : if no bot is assigned
6. We have defined heuristic value between two points as manhattan distance between those points

### ALGORITHM

1. Initiation
    - time = 0 
    - Initiate each bot with their current location to the start location.
    - Update **bot assigned** in task to **-2** for all tasks.
    - Update **second number** of grid point as **-1** for all location other than starting locations of bots
2. Check whether a task is remaining, if yes go with step three. else end.
3. Choose a task i from task list.
4. Check whether there is a path from pickup to delivery location, if yes go with step five. else mark **-1** for bot assigned of the task and goto step two.
5. Find cost A* for all bots from their current location to the pickup location of the task.
6. Assign bot with minimum cost to that task.
7. Find path from pickup to delivery location using A*.
8. Increment time by total cost from current position to pickup and pickup to delivery.
9. Update **second number** of grid for current location of the bot as **-1**
10. Update current location of bot to delivery location.
11. Update **second number** of grid for new current location of the bot as index of bot.
12. Print logs
13. Goto step two.
14. if there is a bot, got to step 15
15. Find path from current location of bot to its end point using A*.
16. Increment time by the cost for moving from current location to end point of the bot.
17. Update **second number** of grid for current location of the bot as **-1**
18. Update current position of bot to the end position.
19. Update **second number** of grid for new current location of the bot as index of bot.
20. Print logs
21. Goto step 14

## USER GUIDE
- Update ```in_grid``` variable with the input GRID array in ```app.cpp```.
- Update ```in_task``` variable with the input task list in ```app.cpp```.
- Update ```in_bot``` varible with input bot list in ```app.cpp```.
- Compile code and run it. :)

