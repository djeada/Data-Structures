#include "bfs.h"
#include "gtest/gtest.h"

TEST(TestBfs, nonEmptyGraph)
{
    Graph graph;
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 4, 1);
    graph.addEdge(1, 0, 1);
    graph.addEdge(1, 3, 1);
    graph.addEdge(1, 4, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 3, 1);
    graph.addEdge(2, 1, 1);
    graph.addEdge(3, 1, 1);
    graph.addEdge(3, 2, 1);
    graph.addEdge(3, 4, 1);

    EXPECT_EQ(breadthFirstSearch(graph, Vertex(2), Vertex(0)), 2);
    EXPECT_EQ(breadthFirstSearch(graph, Vertex(2), Vertex(1)), 1);
    EXPECT_EQ(breadthFirstSearch(graph, Vertex(2), Vertex(2)), 0);
    EXPECT_EQ(breadthFirstSearch(graph, Vertex(2), Vertex(3)), 1);
    EXPECT_EQ(breadthFirstSearch(graph, Vertex(2), Vertex(4)), 2);
}

TEST(TestBfs, nonExistentVertices)
{
    Graph graph;

    EXPECT_EQ(breadthFirstSearch(graph, Vertex(1), Vertex(1)), -1);
    EXPECT_EQ(breadthFirstSearch(graph, Vertex(1), Vertex(2)), -1);
    EXPECT_EQ(breadthFirstSearch(graph, Vertex(1), Vertex(3)), -1);
    EXPECT_EQ(breadthFirstSearch(graph, Vertex(1), Vertex(4)), -1);
    EXPECT_EQ(breadthFirstSearch(graph, Vertex(1), Vertex(5)), -1);
}