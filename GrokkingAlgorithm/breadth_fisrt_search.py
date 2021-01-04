# Breath first seacrch
from collections import deque

#create graph
graph = {}
graph["you"] = ["alice", "bob", "claire"]
graph["bob"] = ["anuj", "peggy"]
graph["alice"] = ["peggy"]
graph["claire"] = ["thom", "jonny"]
graph["anuj"] = []
graph["peggy"] = []
graph["thom"] = []
graph["jonny"] = []

def is_whanted(name):
	return name[-1] == "m"

def search_bf(name):
	search_queue = deque()
	search_queue += graph[name]
    
	names_searched = []
	while search_queue:
		current_name = search_queue.popleft()
		if current_name in names_searched:
			continue
		if is_whanted(current_name):
			print("Get the name is {}".format(current_name))
			return
		else:
		   search_queue += graph[current_name]
		   names_searched.append(current_name)

if __name__ == "__main__":
	search_bf("you")
