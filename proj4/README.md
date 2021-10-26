Project 04: Path Finding
========================

This project implements a [Dijkstra's Algorithm] to perform rudimentary path
finding on a 2D tile-based map.

[Dijkstra's Algorithm]: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm


Input
-----

    TILES_N
    TILE_NAME_0	TILE_COST_0
    ...
    TILE_NAME_N-1	TILE_COST_N-1

    MAP_ROWS MAP_COLUMNS
    TILE_0_0    ...
    ...

    TRAVELER_START_ROW TRAVELER_START_COL
    TRAVELER_END_ROW   TRAVELER_END_COL

Output
------

    Cost
    [(ROW_0, COL_0), ...]


Benchmarking Table

| N             | Elapsed Time  | Memory Usage          |
|---------------|---------------|-----------------------|
| 10            | .002          |92656 bytes            |
| 20            | .003          |123280 bytes           |
| 50            | .005          |350 064 bytes          |
| 100           | .012          |1,149,072 bytes        |
| 200           | .036          |4,340,400 bytes        |
| 500           | .221          |24,300,624 bytes       |
| 1000          | .915          |96,907,392 bytes       |
|---------------|---------------|-----------------------|

1. How did you represent the map as a graph?
I used a vector to cin and manipulate some parts of the map, later during my dijkstras I used a multimap of <int,Node*> to represent the map. The values were keyed by their weights originally and later keyed to their distance as I filled the multimap. The Nodes held their backedges as well as their distances, I used my one dimensional vector to determine which nodes were adjacent.


2. What is complexity of your implementation of Dijkstra's Algorithm?
My dijkstra's implementation should have a complexity of O(n^2+logN) because my cin to vector loop has complextiy O(n^2), and inserting into a multimap is O(logN) which I do in each loop.


3. How well does your implementation scale?
My implementation scales pretty well as far as time goes in my opinion. I'm not sure how good my numbers for memory usage are, but it scales just slightly worse than my time does as N increases.





