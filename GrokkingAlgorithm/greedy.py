'''
贪婪算法是一种近似求解的算法，对于NP完全问题很难求得最优解，可以应用贪婪算法，分步求解，每一步求得当前
的局部最优解，最后求得不一定是最优解但肯定是接近最优解的近似解。
问题：电台覆盖问题。现有8个州，5个电台，每个电台有自己的覆盖范围，选择最少的电台能完全覆盖这8个州
分析：这个是NP完全问题，寻找最佳覆盖方案就要列出所有方案，总的方案个数为2的n次幂，n为电台个数，
	  在这个问题中n较小，但随着n的增加，情况将复杂得多。
	  应用贪婪算法，选出m个电台，每次选择是保证所选电台覆盖面积最大。此时的时间复杂度为O(n*n),
	  不算太快， 但有所提升。
'''

def greedy(states_all, stations):
	result = []

	# NOTE: the end condition cant be "states_all != None"
	while states_all:
		best_station = None
		cover_states = set()
		for station, states in stations.items():
			cover = states & states_all
			if len(cover_states) < len(cover):
				best_station = station
				cover_states = cover

		states_all -= cover_states
		print("cover_states: {}".format(cover_states))
		del(stations[best_station])
		result.append(best_station)
	
	return result

if __name__ == "__main__":
	
	states_all = set(["mt", "wa", "or", "id", "nv", "ut", "ca", "az"])

	stations = {}
	stations['S1'] = set(["id", "nv", "ut"])
	stations['S2'] = set(["wa", "id", "mt"])
	stations['S3'] = set(["or", "nv", "ca"])
	stations['S4'] = set(["nv", "ut"])
	stations['S5'] = set(["ca", "az"])

	result = greedy(states_all, stations)
	print(result)
