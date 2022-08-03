#include<iostream>
#include<map>
#include<vector>
#include<tuple>
#include<string>
#include<fstream>
#include<sstream>
#include<stdio.h>
#include<stdlib.h>
#include<numeric>


using namespace std;
//read in the workouts (key, val) ?
//read in the idx (place holder for idx of key val)
//construct a vector of workouts
//return vector of workouts
//write idx to file
//

class workout {
	private:
		std::map<std::string, std::string> map; //[name] = currentmax
		int idx; //idx of vector
		std::string _filename;
		std::string _idxfilename;
	public:
		workout(std::string filename, std::string idxname){
			_filename = filename;
			string line;
			deque<string> queue;
			ifstream file(filename);
			if(file.is_open()){
				while(!file.eof()) {
					while(getline (file, line)){
						stringstream ss(line);
						string s;
						while(getline(ss, s, ' ')) {
							queue.push_back(s);
						}
						string key = queue.at(0);
						string val = queue.at(1);
						map[key] = val;
						//clear queue
						queue.pop_front();
						queue.pop_front();
					}
				}
				file.close();
			}
			ifstream idxfile(idxname);
			_idxfilename = idxname;
			if(idxfile.is_open()){
				getline(idxfile, line);
				idx = stoi(line);
				std::cout << idx << std::endl;
			}
		}
		~workout(){
			idx++;
			ofstream file(_idxfilename);
			file << std::to_string(idx);
		}
	void dump_all_workouts();
	std::vector<std::string> load(int load_num);
};
std::vector<std::string> workout::load(int load_num){
		std::vector<std::string> vec;
		int n=0;
		std::map<std::string, std::string>::iterator it=map.begin();
		if(idx >= map.size()){
			it = map.begin();
		}else {
			while(int i=0 < idx) it++;
		}
		while(n < load_num){
			if(it == map.end()) it=map.begin();
			vec.push_back(it->first);
			n++;
		}
		return vec;
}
void workout::dump_all_workouts(){
	for(std::map<std::string, std::string>::iterator it=map.begin(); it != map.end(); it++){
		std::cout << "Workout name: " << it->first << " " << "Current max: " << it->second << std::endl;
	}
}
int main(){
	workout chest("chest.txt", "chestidx.txt");
	chest.dump_all_workouts();
	std::vector<std::string> vec = chest.load(2);
	for(std::vector<std::string>::iterator it=vec.begin(); it != vec.end(); it++){
		std::cout << *it << std::endl;
	}

}
































