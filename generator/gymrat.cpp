#include<iostream>
#include<map>
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
class workout {
	private:
		std::map<std::string, std::string> map; //[name] = currentmax
		int idx; //idx of vector
		std::string _filename;
		std::string _idxfilename;
	public:
		workout(std::string filename, std::string idxname){
			std::ofstream workout_file("workout.html");
			workout_file << " ";
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
	void load(int load_num);
};
void workout::load(int load_num){
	//check if idx is out of bounds
	//load in range load_num
	//increment idx
	int n=0;
	std::ofstream file;
	file.open("workout.html", std::ios::app);
	std::map<std::string, std::string>::iterator it = map.begin();
	//increment our pointer to last saved idx
	for(int i=0; i < idx; i++) {
		if(it == map.end()) it=map.begin();
		it++;
	}
	while(n < load_num){
		if(it == map.end()) it=map.begin();
		file << "<h1>====== Workout: " << it->first << " =========</h1>\n" 
			<< "<h2>Spread =====> </h2>\n"
			<< "<ul> \n"
			<< "<li>60% of max (13-15 reps): " << stof(it->second)*0.60 << "lbs</li>\n" 
			<< "<li>80% of max (8-10 reps): " << stof(it->second)*0.80 << "lbs</li>\n" 
			<< "<li>90% of max (1-5 reps): " << stof(it->second)*0.90 << "lbs</li>\n" 
			<< "<li>Current Max: " << stof(it->second) << "lbs\n" 
			<< "</ul>\n"
			<< std::endl;
		it++;
		n++;
	}
	file.close();
}
void workout::dump_all_workouts(){
	for(std::map<std::string, std::string>::iterator it=map.begin(); it != map.end(); it++){
		std::cout << "Workout name: " << it->first << " " << "Current max: " << it->second << std::endl;
	}
}
int main(){
	//keeping track of idx and workout file
	workout chest("chest.txt", "chestidx.txt");
	workout back("back.txt", "backidx.txt");
	workout legs("legs.txt", "legsidx.txt");
	chest.load(3);
	back.load(3);
	legs.load(3);
	std::cout<<"**** Successfully generated workout \u2620 ****";
}
