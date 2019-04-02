/*
 * Code.h
 *
 *  Created on: Sep 16, 2015
 *      Author: maddy
 */

#ifndef CODE_H_
#define CODE_H_

#include <vector>
#include <iostream>

class Code {
public:
	Code() = default; //default constructors will run in visual studio 2010
	Code(const std::vector<int> code_value);//constructs the code object

	//Operator Overloads
	friend std::ostream &operator <<(std::ostream &output, const std::vector<int> &guess);
	friend std::ostream &operator <<(std::ostream &output, const Code &c);

	//randomly gets and prints the code
	void initializeCode();
	void printCode();

	void init();
	void clear();
	void initializeCheck();

	bool checkStat() {return isChecked[0];};
	void changeCheck(int n);

	//checks
	int checkCorrect(const Code& guess) const;
	int checkIncorrect(const Code& guess) const;

	//increment function
	void increment();
private:
	std::vector<int> mystery_code;
	std::vector<bool> isChecked;
};

#endif /* CODE_H_ */
