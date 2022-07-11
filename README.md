## DA_T12_G37 - Travelling Groups

> **2021/2022** - 2nd Year, 2nd Semester
> 
> **Course** - DA (Desenho de Algoritmos)
> 
> **Project developed by**
> - Guilherme Moreira (up202007036)
> - Isabel Amaral (up202006677)
> - Milena Gouveia (up202008862)

### Project Description

A travel agency owns several vehicles which perform one single route between two locations and have a certain capacity each. Groups with different sizes may resort to the agency in order to plan which vehicles to use during their travel. Groups may want to always travel together or may be open to separate before getting to the final destination.

The purpose of this project was to implement a series of algorithms to calculate different paths for the groups according to different scenarios, in order to help the travel agency manage all the transportation requests. 

### Implemented Scenarios

The different scenarios were described in the project's description (pt) - [here](./docs/project-description.pdf):

- **Groups that travel together**:
    - **Maximum capacity path** - find the path between a given source and destination with the highest capacity.
    - **Minimum Transhipments** - find the path between a given source and destination with the lowest number of transhipments.

- **Groups that may separate**:
    - **Maximum flow** - find the maximum size of the group that's able to travel between a given source and destination, knowing that separations are possible.
    - **Find one or more paths** - find a path between a given source and destination, or more than one path if the group's capacity is higher than the maximum capacity between that source and destination.
    - **Correct the path for a bigger group** - given a number of extra people to the group being considered above, correct the previous path(s) in order to accomodate the higher group dimension.
    - **Earliest Meeting Spot** - knowing the group separates and, therefore, different elements travel through different paths, find the earliest spot where all the group elements are able to reunite before travelling together until the final destination. Worst case, the group only reunites at the final destination.
    - **Waiting Time** - knowing the group reunites at a certain spot and the travel time of each route, calculate which subgroup is the last to arrive to the meeting spot and how much time all the other subgroups must wait for the last one.

Other implemented features:

- **Interactive Menu** - In order to test and demonstrate the different scenarios, we created a simple menu.
- **Code documentation** - All the implemented classes were documented using doxygen. The complete generated documentation can be checked in the [docs directory](./docs/output/html/). Alternatively just open the [index.html](./docs/output/html/index.html) in your browser.

### Program Development State

Overall all the scenarios implemented seemed to be working properly. We learned in which contexts it makes sense to use some commonly used graph algorithms, such as Ford-Fulkerson / Edmons-Karp Algorithm, Critical Path Method etc.

For each scenario, we used one single graph for the network being considered. The graph's nodes correspond to the spots where it's possible to board one of the available vehicles. The graph's edges correspond to the route performed by a certain vehicle. All the edges are associated to a certain capacity (maximum capacity of the vehicle traveling that route), flow (number of people currently using that vehicle, never higher than the capacity) and travel time.

For a more detailed project report (pt), check out ppt presentation [here](./docs/presentation.pdf).
