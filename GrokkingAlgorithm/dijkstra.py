# shortest algrithom--dijkstra
# 首先要搞清楚图的表示方式

# the graph
graph = {}
graph["start"] = {}
graph["start"]["a"] = 6
graph["start"]["b"] = 2

graph["a"] = {}
graph["a"]["fin"] = 1

graph["b"] = {}
graph["b"]["a"] = 3
graph["b"]["fin"] = 5

graph["fin"] = {}

# the costs table, store the cost from start to others
infinity = float("inf") #
costs = {}
costs["a"] = 6
costs["b"] = 2
costs["fin"] = infinity

# the parents table
parents = {}
parents["a"] = "start"
parents["b"] = "start"
parents["fin"] = None

processed = []

def compute_lowest_cost_node(costs):
	lowest_value = float("inf")  # mean the infinity
	lowest_node = None
	for node in costs:
		if node in processed:
			continue

		node_cost = costs[node]
		if node_cost < lowest_value:
			lowest_value = node_cost
			lowest_node = node

	return lowest_node

if __name__ == "__main__":
	print("Before dijkstra : {}".format(costs))

	lowest_node = compute_lowest_cost_node(costs)

	while lowest_node != None:
		# Go throught all the neighbors of this node
		neighbor_nodes = graph[lowest_node]
		lowest_value   = costs[lowest_node]

		for node in neighbor_nodes.keys():
			node_cost     = costs[node]
			# Compute the cost of start get to this neighbor by going through the lowest_node
			node_new_cost = neighbor_nodes[node] + lowest_value
		
			if node_new_cost < node_cost or node_cost == float('inf'):
				costs[node]   = node_new_cost
				parents[node] = lowest_node
		processed.append(lowest_node)
		lowest_node = compute_lowest_cost_node(costs)

	print("After dijkstra : {}".format(costs))



