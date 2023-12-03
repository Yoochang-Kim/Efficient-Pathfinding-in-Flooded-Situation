# FloodPathfinder

## Introduction
The C program simulates a pathfinding robot in a flood scenario. It uses Dijkstra and A* algorithms to find the shortest path to reach the destination.

## Features
- Simulates a city map with impassable buildings and walls, and navigable water and roads.
- Uses two pathfinding algorithms, each producing different results and efficiencies.
- The robot can move up, down, left, or right, but not diagonally.
- Configurable map dimensions (recommended to keep under 20x20).

## Pseudocode
The following images show the pseudocode for the algorithms used:

<div align="center">
  <table>
    <tr>
      <td align="center">
        <img src="https://github.com/Yoochang-Kim/FloodPathfinder/blob/main/srcs/img/astar_pseudocode.png" width="380" alt="A* Pseudocode"><br>
        <b>A* Pseudocode</b>
      </td>
      <td align="center">
        <img src="https://github.com/Yoochang-Kim/FloodPathfinder/blob/main/srcs/img/dijkstra_pseudocode.png" width="480" alt="Dijkstra Pseudocode"><br>
        <b>Dijkstra's Pseudocode</b>
      </td>
    </tr>
  </table>
</div>

## Pathfinding Results
Here are the results from both pathfinding algorithms on a sample city map:

<div align="center">
  <table>
    <tr>
      <td align="center">
        <img src="https://github.com/Yoochang-Kim/FloodPathfinder/blob/main/srcs/img/original%20city%20map.png" width="250" alt="Original City Map"><br>
        <b>Original City Map</b>
      </td>
      <td align="center">
        <img src="https://github.com/Yoochang-Kim/FloodPathfinder/blob/main/srcs/img/Dijkstra%20result.png" width="250" alt="Dijkstra Result"><br>
        <b>Dijkstra's Algorithm Result</b>
      </td>
      <td align="center">
        <img src="https://github.com/Yoochang-Kim/FloodPathfinder/blob/main/srcs/img/a%20star%20result.png" width="250" alt="A* Result"><br>
        <b>A* Algorithm Result</b>
      </td>
    </tr>
  </table>
</div>
