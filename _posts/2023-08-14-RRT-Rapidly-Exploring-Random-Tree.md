---
layout: post
category: blog
title: Rapidly-Exploring Random Tree (RRT)
snippet: Explain the RRT and some its variation.
tags: [motion planing, robotics]
---

The Rapidly Exploring Random Tree (RRT) algorithm is a popular path planning algorithm used in robotics. It efficiently searches nonconvex, high-dimensional spaces by randomly building a space-filling tree. 

<div class="row">
  <div class="col">
    {% include image.html url="../assets/RRT/RRT.png" description="RRT Algorithms" width="100%" %}
  </div>
  <div class="col">
     {% include image.html url="../assets/RRT/RRT_star.png" description="RRT* Algorithms" width="100%" %}
  </div>
</div>

<div class="row">
  <div class="col">
    {% include image.html url="../assets/RRT/RRT_dark.gif" description="RRT Algorithms in 3D" width="100%" %}
  </div>
  <div class="col">
     {% include image.html url="../assets/RRT/RRT_star_dark.gif description="RRT* Algorithms in 3D" width="100%" %}
  </div>
</div>



0. Intialize a __Graph(Vertex, Edge)__  with containing edges and vertices, initialized as (start_pos, end_pos).
1. Randomly generate points (vertex) in the space.
2. Check if the newly created vertex lies outside of an obstacle.
3. Find the nearest vertex to the closest available vertices in the tree.
4. Steering vertex to avoid obstacles when chaining the vertex to its closest neighbor.
5. Add new vertex and edge with nearest vertex into Graph
6. Repeat steps 1-5 until a node is generated within the goal region or a limit is reached.

Variations of the RRT algorithm have been developed to improve its performance and convergence to an optimal solution. Some notable variations include:

- **RRT**: Rapidly-Exploring Random Tree, which is an algorithm designed to efficiently search nonconvex, high-dimensional spaces by randomly building a space-filling tree. The tree is constructed incrementally from samples drawn randomly from the search space and is inherently biased to grow towards large unsearched areas of the problem. RRTs were developed by Steven M. LaValle and James J. Kuffner Jr [pdf](http://msl.cs.uiuc.edu/~lavalle/papers/Lav98c.pdf)

Snippet code of __RRT__ in Python:

RRT.py
{:.filename}
```python
def RRT(startpos, endpos, n_iter, radius, stepSize, goal_radius, obstacles):
    G = Graph(startpos, endpos)
    for _ in range(n_iter):
        # 1. Sample a random Vertice
        randvex = G.randomPos()

        # 2. Check vertex inside the Obstacles (if inside -> True, otherwise: False)
        if isInObstacle(randvex, obstacles): 
            continue

        # 3. Find the near vertices
        nearvex, nearidx = nearest(G, randvex, obstacles)
        if nearvex is None:
            continue

        # 4. Steer steerVertex
        newvex = steerVertex(randvex, nearvex, stepSize)

        # 5. Add vertex and edge with nearest vertex
        newidx = G.add_vertex(newvex)
        dist = distance(newvex, nearvex)
        G.add_edge(newidx, nearidx, dist)

        #6. check if the point reach the goal
        dist = distance(newvex, G.endpos)
        if dist < 2 * goal_radius:
            endidx = G.add_vertex(G.endpos)
            G.add_edge(newidx, endidx, dist)
            G.success = True
            # print('Found Goadl!')
            # break
    end = timer()
    print("Execution time RRT:", end - start, "seconds")
    return G
```

- **RRT***: is a variant of the Rapidly Exploring Random Tree (RRT) algorithm, which is designed for efficiently searching nonconvex, high-dimensional spaces by randomly building a space-filling tree. While RRT gives a valid path but not necessarily the shortest path, RRT* is an optimized version of RRT that aims to achieve a shortest path by rewiring the tree in a way that a given such radius and always tries to find a shorter path from the randomly sampled node back to the start in the tree. This makes RRT* to give an optimal solution and makes it even more feasible for high dimensional problems. RRT* is particularly suitable for path planning problems that involve obstacles and differential constraints, but it is not suitable for non-holonomic vehicles. RRT* was developed by Sertac Karaman in paper Sampling-based Algorithms for Optimal Motion Planning [pdf](https://arxiv.org/pdf/1105.1186.pdf)

Snippet code of __RRT*__ in Python:

RRT_star.py
{:.filename}
```python
def RRT_star(startpos, endpos, n_iter, radius, goal_radius, stepSize, obstacles):
    start = timer()
    G = Graph(startpos, endpos)

    for _ in range(n_iter):
        # 1. Sample a random Vertice
        randvex = G.randomPos()
        if isInObstacle(randvex, obstacles): #check vertex inside the Sphere Obstacles
            continue
        # 2. Find the near vertices
        nearvex, nearidx = nearest(G, randvex, obstacles)
        if nearvex is None:
            continue
        
        # 3. Steer steerVertex
        newvex = steerVertex(randvex, nearvex, stepSize)
        
        #4. Add vertex and edge with nearest vertex
        newidx = G.add_vertex(newvex)
        dist = distance(newvex, nearvex)
        G.add_edge(newidx, nearidx, dist)
        G.distances[newidx] = G.distances[nearidx] + dist

        # 5. Rewire step: update nearby vertices distance (if shorter)
        for vex in G.vertices:
            if vex == newvex:
                continue

            dist = distance(vex, newvex)
            line = Line(vex, newvex)

            if isThruObstacle(line, obstacles):
                continue

            if dist > radius:
                continue
            
            # When dist < radius implement this code
            idx = G.vex2idx[vex]
            if G.distances[newidx] + dist < G.distances[idx]:
                G.add_edge(idx, newidx, dist)
                G.distances[idx] = G.distances[newidx] + dist


        # 6. Check the goal
        dist = distance(newvex, G.endpos)  
        if dist < 2 * goal_radius:
            endidx = G.add_vertex(G.endpos)
            G.add_edge(newidx, endidx, dist)
            try:
                G.distances[endidx] = min(G.distances[endidx], G.distances[newidx]+dist)
            except:
                G.distances[endidx] = G.distances[newidx]+dist

            G.success = True
            print('success')
            break
    return G

```


## References
1. Depth First Search (DFS) Explained: Algorithm, Examples, and Code [link](https://www.youtube.com/watch?v=PMMc4VsIacU)
2. Depth First Search Wiki [link](https://en.wikipedia.org/wiki/Depth-first_search)
3. Depth First Search (DFS) in Python [link](https://www.scaler.com/topics/dfs-python/)
4. Udemy course the introduction sampling based motion planning algorithms [link](https://www.udemy.com/course/an-introduction-to-sampling-based-motion-planning-algorithms/l)
5. TreeNode - Nonlinear Data Structure [Link](https://www.codecademy.com/learn/nonlinear-data-structures-python/modules/trees-python/cheatsheet)
6. Useful Python Implementation of Rapidly-exploring random tree (RRT) Path-planning Algorithm from Fanjin Zeng [link](https://gist.github.com/Fnjn/58e5eaa27a3dc004c3526ea82a92de80)
