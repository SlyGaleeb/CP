vector<vector<int>>ps;
 
void power_set(vector<int> &subset, int i, vector<int> &v) {
	if (i==v.size()) {
		ps.push_back(subset);
		return;
	}
	power_set(subset,i+1,v);
	subset.push_back(v[i]);
	power_set(subset,i+1,v);
	subset.pop_back();
}
