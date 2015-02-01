    Construct the implication graph of the instance, and find its strongly 
connected components using any of the known linear-time algorithms for strong connectivity analysis.
    Check whether any strongly connected component contains both a variable 
and its negation. If so, report that the instance is not satisfiable and halt.
    Construct the condensation of the implication graph, a smaller graph that 
has one vertex for each strongly connected component, and an edge from 
component i to component j whenever the implication graph contains an 
edge uv such that u belongs to component i and v belongs to component j. 
The condensation is automatically a directed acyclic graph and, like the 
implication graph from which it was formed, it is skew-symmetric.
    Topologically order the vertices of the condensation; the order 
in which the components are generated by Kosaraju's algorithm is 
automatically a topological ordering.
    For each component in this order, if its variables do not already have 
truth assignments, set all the terms in the component to be false. 
This also causes all of the terms in the complementary component to be set to true.

