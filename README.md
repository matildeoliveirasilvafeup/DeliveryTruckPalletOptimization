# Individual Route Planning Tool  
### Design of Algorithms (L.EIC016) — FEUP/FCUP — Spring 2025  

This project consists of the development of a C++ route planning tool that models an urban environment as a weighted undirected graph.  
It implements greedy shortest-path algorithms to calculate the best and alternative routes, including restricted paths and eco-friendly mixed routes (driving + walking).

---

## Project Overview

The goal of this assignment was to apply algorithmic design techniques, particularly greedy approaches, to realistic shortest-path problems.  
The tool simulates a simplified GPS-like system, supporting multiple functionalities:

- Driving route planning  
- Alternative route computation (disjoint paths)  
- Restricted routing — avoiding specific nodes or segments  
- Environmentally-friendly routes combining driving and walking with parking constraints  
- Batch mode using `input.txt` and `output.txt`  
- Full documentation and time complexity analysis (via Doxygen)

---

## Data and Representation

The urban environment is represented as a graph:

- Nodes (vertices): street intersections or locations  
- Edges: street segments, each with driving and walking times  
- Attributes: parking availability, restricted areas  

Input files:
- `Locations.csv` — location data (ID, name, parking availability)  
- `Distances.csv` — pairwise connections with driving and walking times  

---

## Functionalities Implemented

| Task | Description | Algorithms / Techniques |
|------|--------------|--------------------------|
| **T1.1** | Command-line interface & menu system | C++ I/O, menu design |
| **T1.2** | CSV parsing and graph construction | File handling, adjacency lists |
| **T1.3** | Documentation and complexity analysis | Doxygen, Big-O analysis |
| **T2.1** | Best and alternative independent routes | Dijkstra’s algorithm, disjoint path logic |
| **T2.2** | Restricted route planning (avoid/exclude/include) | Graph pruning, shortest path recalculation |
| **T3.1** | Mixed route (driving + walking) planning | Multi-stage shortest path, constraints handling |
| **T3.2** | Approximate alternative solutions | Heuristic adjustment of constraints |

---

## Implementation Details

- Language: C++17  
- Paradigm: Object-Oriented Programming  
- Graph structure: custom class based on course-provided template  
- Input/Output: menu mode and batch mode  
- Documentation: generated using Doxygen  
- Error handling: robust parsing and validation of input data  

---

## Example Input/Output

**Example input (`input.txt`):**
```text
Mode:driving
Source:1
Destination:5
