#ifndef C_GRAPH_H
#define C_GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include "c_pair.h"

using namespace std;

class c_comparison {
public:
	bool operator ()(const c_pair& lhs, const c_pair& rhs) {
		return (lhs.value < rhs.value);
	}
};


class c_graph
{
public:
	int n_nodes;
	int sybil_connections;
	int non_sybil_connections;
	int infected_proportions;	
	int secure_proportions;
	float initial_trust;
	vector< vector <float> > social_graph;
	vector <int> sybil_nodes;

	c_graph(int); // Number of nodes.
	~c_graph();

	void print_graph();
	void set_sybil_nodes(int);
	void getting_nodes(int&);
	bool is_sybil_node(int);
	int get_non_sybil_node();
	void set_non_sybil_node();//Should not be executed without set_sybil_nodes first.
	void set_nodes();
	void sybil_analyze();
	void start_record(int, float);
	int get_at_line(int);
	void find_out_results();
	int get_number_connections(int);

};



c_graph::c_graph(int _n){
	this->n_nodes = _n;
	this->sybil_connections = 3;
	this->non_sybil_connections = this->sybil_connections * 3;
	this->social_graph = vector< vector<float> >(_n, vector<float>(_n, 0.0)); //Nodes from 0 to size()-1
	this->sybil_nodes = vector<int>(0, 0);
	this->infected_proportions = 20;
	this->secure_proportions = 15;
	this->initial_trust = 100.0;
}


c_graph::~c_graph()
{
}

void c_graph::set_nodes() {
	this->set_sybil_nodes(this->infected_proportions);
	this->set_non_sybil_node();
}

void c_graph::set_sybil_nodes(int percentaje) {
	int affected = (int)((float)(this->social_graph.size()) * (float)(percentaje / 100.0) );
	 
	while (affected > 0) {
		int temp_node; this->getting_nodes(temp_node);
		if (!this->is_sybil_node(temp_node)) {
			this->sybil_nodes.push_back(temp_node);
			affected--;
		}
	}

	for (unsigned int i = 0; i < this->sybil_nodes.size(); i++) {
		cout << this->sybil_nodes[i] << " ";
	}
	cout << endl;
	
	//Defining Rules;
	if (this->sybil_nodes.size() > 1) {
		for (unsigned int i = 1; i < this->sybil_nodes.size(); i++) {
			this->social_graph[sybil_nodes[i - 1]][sybil_nodes[i]] = 1.0;
			this->social_graph[sybil_nodes[i]][sybil_nodes[i - 1]] = 1.0;
		}
	}

	for (unsigned int i = 0; i < this->sybil_nodes.size(); i++) {
		for (int i = 0; i < this->sybil_connections; i++) {
			int temp = this->get_non_sybil_node();
			this->social_graph[temp][sybil_nodes[i]] = 1.0;
			this->social_graph[sybil_nodes[i]][temp] = 1.0;
 		}
	}
}


void c_graph::set_non_sybil_node() {
	for (unsigned int i = 0; i < this->social_graph.size(); i++) {
		if (!this->is_sybil_node(i)) {
			for (int i = 0; i < this->non_sybil_connections; i++) {
				int temp = this->get_non_sybil_node();
				this->social_graph[i][temp] = 2.0;
				this->social_graph[temp][i] = 2.0;
			}
		}
	}
}

void c_graph::getting_nodes(int& a) {
	a = rand() % this->n_nodes;
	return;
}

bool c_graph::is_sybil_node(int a) {
	for (unsigned int i = 0; i < this->sybil_nodes.size(); i++) {
		if (this->sybil_nodes[i] == a) {
			return true;
		}
	}
	return false;
}

int c_graph::get_non_sybil_node() {
	while(true){
		int temp = rand() % this->n_nodes;
		if (!this->is_sybil_node(temp)) {
			return temp;
		}
	}
}


void c_graph::print_graph() {
	cout << "   ";
	for (unsigned int i = 0; i < this->social_graph.size(); i++) {
		if (this->is_sybil_node(i)) {
			cout << "*" << "  ";
		}
		else {
			cout << "|" << "  ";
		}
	}
	cout << endl;

	for (unsigned int i = 0; i < this->social_graph.size(); i++) {
		if (this->is_sybil_node(i)) {
			cout << "-*" << "  ";
		}
		else {
			cout << "->" << "  ";
		}

		for (unsigned int j = 0; j < this->social_graph[i].size(); j++) {
			cout << this->social_graph[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

void c_graph::sybil_analyze() {
	cout << "Start Sybil Analyze" << endl;
//	int secure_nodes = 12; //Must be under the total nodes 
	int secure_nodes = (int)((float)(this->social_graph.size()) * (float)(this->secure_proportions / 100.0)); //Must be under the total nodes 
	for (int i = 0; i < secure_nodes; i++) {
		int temp = this->get_non_sybil_node();
		this->start_record(temp, this->initial_trust);
	}
	this->find_out_results();
}

void c_graph::start_record(int initial_node, float trust) {
	//cout << "Start Record: " << initial_node << " : " << trust << endl;
	if (trust > 0) {
		int line_partner = this->get_at_line(initial_node);
		this->social_graph[initial_node][line_partner] += trust;
		this->social_graph[line_partner][initial_node] += trust;
		trust =  trust - this->n_nodes / (this->n_nodes - this->sybil_nodes.size());
		this->start_record(line_partner, trust);

	}
	else {
		return;
	}
}

int c_graph::get_at_line(int line) {
	int temp_node = rand() % this->n_nodes;
	while (this->social_graph[line][temp_node] == 0) {//0 implies a non_conection besides the vector
		temp_node = (temp_node + 1) % this->n_nodes;
	}
	return temp_node;
}

int c_graph::get_number_connections(int line) {
	int result = 0;
	for (unsigned int i = 0; i < this->social_graph[line].size(); i++) {
		if (this->social_graph[line][i] != 0) {
			result++;
		}
	}
	return result;
}
void c_graph::find_out_results() {

	priority_queue<c_pair, std::vector<c_pair>, c_comparison> my_queue;
	vector<float> results = vector<float>(this->n_nodes, 0.0);
	
	for (unsigned int i = 0; i < this->social_graph.size(); i++) {
		for (unsigned int j = 0; j < this->social_graph[i].size(); j++) {
			results[i] += this->social_graph[i][j];
		}
	}

	//Setting Up queue;
	for (unsigned int i = 0; i < results.size(); i++) {
		c_pair temp = c_pair(i, results[i]);
		my_queue.push(temp);
	}

	cout << "FINAL RESULTS: " << endl;
	while (!my_queue.empty()) {
		cout << "Node: " << my_queue.top().index << " with value " << my_queue.top().value;
		if (this->is_sybil_node(my_queue.top().index)) {
			cout << " * " << " Connections: "<< this->get_number_connections(my_queue.top().index) <<endl;
		}
		else {
			cout << " -- " << " Connections: " << this->get_number_connections(my_queue.top().index) << endl;
		}
		my_queue.pop();
	}
}

#endif