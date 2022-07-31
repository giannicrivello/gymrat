#include<iostream>
#include<vector>
#include<tuple>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;
//global indexes
tuple<int, int, int> chestidx;
tuple<int, int, int> backidx;
tuple<int, int, int> legidx;
tuple<int, int> arobicidx;

struct workout {
	int currentmax;
	string name;
	tuple<int, int, int, int> insturctions; //max four sets, 0 indecates empty set
};
struct daysWorkout {
	vector<workout> workouts;
	
};
//sets of body groups
vector<workout> chest;
vector<workout> back;
vector<workout> legs;
vector<workout> arobic;


void fileread(vector<int> &vec, string file_name){
	string line;
	ifstream file(file_name);
	if(file.is_open()) {
		getline(file, line);
		stringstream ss(line);
		string s;
		while(getline(ss, s, ' ')) {
			vec.push_back(stoi(s));
		}
		file.close();
	}

}
void miniloadidx(){
	vector<int> chestvec;
	fileread(chestvec, "chestidxfile");
	for(vector<int>::iterator it = chestvec.begin(); it != chestvec.end(); it++){
		cout << *it << endl;
	}
	get<0>(chestidx) = chestvec[0];
	get<1>(chestidx) = chestvec[1];
	get<2>(chestidx) = chestvec[2];


}
void loadidx(){
	vector<int> chestvec;
	vector<int> backvec;
	vector<int> legvec;
	vector<int> arobicvec;
	
	//load idx
	//set global idx
	//
	fileread(chestvec, "chestidxfile");
	get<0>(chestidx) = chestvec[0];
	get<1>(chestidx) = chestvec[1];
	get<2>(chestidx) = chestvec[2];
	
	fileread(backvec, "backidxfile");
	get<0>(backidx) = backvec[0];
	get<1>(backidx) = backvec[1];
	get<2>(backidx) = backvec[2];
	
	//build legs idx
	fileread(legvec, "legidxfile");
	get<0>(legidx) = legvec[0];
	get<1>(legidx) = legvec[1];
	get<2>(legidx) = legvec[2];
	
	//build arobic idx
	fileread(arobicvec, "arobicidxfile");
	get<0>(arobicidx) = arobicvec[0];
	get<1>(arobicidx) = arobicvec[1];
}

vector<workout> genworkout(vector<workout> a, vector<workout> b, vector<workout> c, vector<workout> d, vector<workout> dest) {
	vector<workout> today;
	//build from chest
	today.push_back(a[get<0>(chestidx)]);
	today.push_back(a[get<1>(chestidx)]);
	today.push_back(a[get<2>(chestidx)]);

	//build from back
	today.push_back(b[get<0>(chestidx)]);
	today.push_back(b[get<1>(chestidx)]);
	today.push_back(b[get<2>(chestidx)]);
	
	
	//build from legs
	today.push_back(c[get<0>(chestidx)]);
	today.push_back(c[get<1>(chestidx)]);
	today.push_back(c[get<2>(chestidx)]);
	
	//build from arobic
	today.push_back(d[get<0>(chestidx)]);
	today.push_back(d[get<1>(chestidx)]);
	copy(today.begin(), today.end(), dest.begin());
	
	//add back to main later
	cout << "Back IDX" << endl;
	cout << get<0>(backidx) << endl;
	cout << get<1>(backidx) << endl;
	cout << get<2>(backidx) << endl;
	cout << "Leg IDX" << endl;
	cout << get<0>(legidx) << endl;
	cout << get<1>(legidx) << endl;
	cout << get<2>(legidx) << endl;
	cout << "Arobic IDX" << endl;
	cout << get<0>(arobicidx) << endl;
	cout << get<1>(arobicidx) << endl;
	
	return today;
}

int main(){
	vector<workout> todayTraining;
	//load workouts from file system
	//load current indexes
	//
	miniloadidx();
	cout << "Chest IDX" << endl;
	cout << get<0>(chestidx) << endl;
	cout << get<1>(chestidx) << endl;
	cout << get<2>(chestidx) << endl;

	//generate todays workout
	// TODO genworkout(chest, back, legs, arobic, todayTraining);
}







