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
			std::string line;
			std::deque<std::string> queue;
			std::ifstream file(filename);
			if(file.is_open()){
				while(!file.eof()) {
					while(getline (file, line)){
						std::stringstream ss(line);
						std::string s;
						while(getline(ss, s, ' ')) {
							queue.push_back(s);
						}
						std::string key = queue.at(0);
						std::string val = queue.at(1);
						map[key] = val;
						//clear queue
						queue.pop_front();
						queue.pop_front();
					}
				}
				file.close();
			}
			std::ifstream idxfile(idxname);
			_idxfilename = idxname;
			if(idxfile.is_open()){
				getline(idxfile, line);
				idx = stoi(line);
				std::cout << idx << std::endl;
			}
		}
		~workout(){
			idx++;
			std::ofstream file(_idxfilename);
			file << std::to_string(idx + 1);
		}
	void dump_all_workouts();
	std::vector<std::string> load(int load_num);
};
std::vector<std::string> workout::load(int load_num){
	std::vector<std::string> vec;
	//check if idx is out of bounds
	//load in range load_num
	//increment idx
	int n=0;
	std::map<std::string, std::string>::iterator it = map.begin();
	//increment our pointer to last saved idx
	for(int i=0; i < idx; i++) {
		if(it == map.end()) it=map.begin();
		it++;
	}
	while(n < load_num){
		if(it == map.end()) it=map.begin();
		vec.push_back(it->second);
		it++;
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
	//keeping track of idx and workout file
	workout chest("chest.txt", "chestidx.txt");
	chest.dump_all_workouts();
	std::vector<std::string> vec = chest.load(3);
	for(std::vector<std::string>::iterator it=vec.begin(); it != vec.end(); it++){
		std::cout << *it << std::endl;
	}
}
































