#ifndef C_PAIR_H
#define C_PAIR_H

class c_pair
{
public:
	int index;
	float value;

	c_pair();
	c_pair(int, float);
	~c_pair();
};


c_pair::c_pair() {
	this->index = 0;
	this->value = 0.0;
}

c_pair::c_pair(int _index, float _value){
	this->index = _index;
	this->value = _value;
}


c_pair::~c_pair()
{
}


#endif