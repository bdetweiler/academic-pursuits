package com.codeeval.cycle_detection;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class cycle_detection {
    
    private int index = 0;

    private ArrayList<Node> stack = new ArrayList<Node>();

    private ArrayList<ArrayList<Node>> stronglyConnectedComponents = new ArrayList<ArrayList<Node>>();
    
    public static void main(String[] args) throws IOException {
        File file = new File(args[0]);
        BufferedReader in = new BufferedReader(new FileReader(file));
        String line;
        while ((line = in.readLine()) != null) {
            String[] lineArr = line.split("\\s");
            if (lineArr.length > 0) {
                Node prev = null;
                AdjacencyList G = new AdjacencyList();
                // Edge e = null;
                for(String element : lineArr) {
                    Node curr = new Node(Integer.parseInt(element));
                    
                    if(prev != null)
                        G.addEdge(prev, curr, 0);
                     
                    prev = curr;
                }
                
                System.out.println(G);
                
                cycle_detection CD = new cycle_detection();
                ArrayList<ArrayList<Node>> set = CD.executeTarjan(G);
                System.out.println(set);
            }
        }
    }

    /* The function tarjan has to be called for every unvisited node of the graph */
    public ArrayList<ArrayList<Node>> executeTarjan(AdjacencyList graph) {
        stronglyConnectedComponents.clear();
        
        index = 0;
        stack.clear();
        
        if(graph == null)
            return stronglyConnectedComponents;
        
        List<Node> nodeList = new ArrayList<Node>(graph.getSourceNodeSet());
        for (Node node : nodeList)
            if (node.index == -1)
                tarjan(node, graph);
        
        return stronglyConnectedComponents;
    }
    
    /*
     * algorithm tarjan is
  input: graph G = (V, E)
  output: set of strongly connected components (sets of vertices)

  index := 0
  stack := empty
  for each v in V do
    if (v.index is undefined) then
      strongconnect(v)
    end if
  repeat

  function strongconnect(v)
    // Set the depth index for v to the smallest unused index
    v.index := index
    v.lowlink := index
    index := index + 1
    stack.push(v)

    // Consider successors of v
    for(Node v : w) in E do
      if (w.index is undefined) then
        // Successor w has not yet been visited; recurse on it
        strongconnect(w)
        v.lowlink := min(v.lowlink, w.lowlink)
      else if (w is in stack) then
        // Successor w is in stack and hence in the current SCC
        v.lowlink := min(v.lowlink, w.index)
      end if
    repeat

    // If v is a root node, pop the stack and generate an SCC
    if (v.lowlink = v.index) then
      start a new strongly connected component
      repeat
        w := stack.pop()
        add w to current strongly connected component
      until (w = v)
      output the current strongly connected component
    end if
  end function
     */

    private ArrayList<ArrayList<Node>> tarjan(Node v, AdjacencyList list) {
            v.index = index;
            v.lowlink = index;
            ++index;
            stack.add(0, v);
            try {
                for (Edge edge : list.getAdjacent(v)) {
                    // e -> n
                    Node node = edge.to;
                    if(node.index == -1) {
                        tarjan(node, list);
                        v.lowlink = Math.min(v.lowlink, node.lowlink);
                    } else if(stack.contains(node)) {
                        v.lowlink = Math.min(v.lowlink, node.index);
                    }
                }
            } catch(Exception e) {
                System.out.println(e);
            }
            if (v.lowlink == v.index) {
                Node n;
                ArrayList<Node> component = new ArrayList<Node>();
                do {
                    n = stack.remove(0);
                    component.add(n);
                } while (n != v);
                stronglyConnectedComponents.add(component);
            }
            return stronglyConnectedComponents;
        }
    }

    class AdjacencyList {

        private Map<Node, List<Edge>> adjacencies = new HashMap<Node, List<Edge>>();

        public void addEdge(Node source, Node target, int weight) {
            List<Edge> list;
            if (!adjacencies.containsKey(source)) {
                list = new ArrayList<Edge>();
                adjacencies.put(source, list);
            } else {
                list = adjacencies.get(source);
            }
            list.add(new Edge(source, target, weight));
        }

        public List<Edge> getAdjacent(Node source) {
            return adjacencies.get(source);
        }

        public void reverseEdge(Edge e) {
            adjacencies.get(e.from).remove(e);
            addEdge(e.to, e.from, e.weight);
        }

        public void reverseGraph() {
            adjacencies = getReversedList().adjacencies;
        }

        public AdjacencyList getReversedList() {
            AdjacencyList newlist = new AdjacencyList();
            for (List<Edge> edges : adjacencies.values()) {
                for (Edge e : edges) {
                    newlist.addEdge(e.to, e.from, e.weight);
                }
            }
            return newlist;
        }

        public Set<Node> getSourceNodeSet() {
            return adjacencies.keySet();
        }

        public Collection<Edge> getAllEdges() {
            List<Edge> edges = new ArrayList<Edge>();
            for (List<Edge> e : adjacencies.values()) {
                edges.addAll(e);
            }
            return edges;
        }
        
        @Override
        public String toString() {
            return adjacencies.toString();
        }
    }

    class Node implements Comparable<Node> {

        final int name;

        boolean visited = false; // used for Kosaraju's algorithm and Edmonds's algorithm

        int lowlink = -1; // used for Tarjan's algorithm

        int index = -1; // used for Tarjan's algorithm

        public Node(final int argName) {
            name = argName;
        }

        public int compareTo(final Node argNode) {
            return argNode == this ? 0 : -1;
        }
        
        @Override
        public String toString() {
            return name + "";
        }
    }

    class Edge implements Comparable<Edge> {

        final Node from, to;

        final int weight;

        public Edge(final Node argFrom, final Node argTo, final int argWeight) {
            from = argFrom;
            to = argTo;
            weight = argWeight;
        }

        public int compareTo(final Edge argEdge) {
            return weight - argEdge.weight;
        }
       
        @Override
        public String toString() {
            return from + " --(" + weight + ")--> " + to;
        }
    }
