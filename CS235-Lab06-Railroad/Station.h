#ifndef STATION_H
#define STATION_H

#include "Queue.h"
#include "Stack.h"
#include "Vector.h"
#include "Car.h"

template <typename T>
class Station
	: public Queue<T>, public Stack<T>, public Vector<T>
{
private:
	T turnTableCar_;
	Vector<T> train_;
	Queue<T> queue_;
	Stack<T> stack_;
	bool empty;

public:
	Station() :
		turnTableCar_(NULL),
		empty(true) {}
	~Station() {}


	std::string addCar(const T& car)  // Adds car to turn table, returns occupied if occupied
	{
		if (turnTableCar_ != NULL) { return "Turntable occupied!"; }
		else
		{
			turnTableCar_ = car;
			return "OK";
		}
	}

	std::string addQueue()  // Moves turntable car to queue
	{
		if (turnTableCar_ == NULL) { return "Turntable empty!"; }
		else
		{
			queue_.push(turnTableCar_);
			turnTableCar_ = NULL;
			return "OK";
		}
	}

	std::string addStack() // Moves turntable car to stack
	{
		if (turnTableCar_ == NULL) { return "Turntable empty!"; }
		else
		{
			stack_.push(turnTableCar_);
			turnTableCar_ = NULL;
			return "OK";
		}
	}

	std::string removeCar() // Moves turntable car to vector
	{
		if (turnTableCar_ == NULL) { return "Turntable empty!"; }
		else
		{
			train_.push_back(turnTableCar_);
			turnTableCar_ = NULL;
			return "OK";
		}
	}

	std::string removeQueue() // Moves head of queue to turntable
	{
		if (turnTableCar_ != NULL) { return "Turntable occupied!"; }
		else if (queue_.empty()) { return "Queue empty!"; }
		else
		{
			turnTableCar_ = queue_.top();
			queue_.pop();
			return "OK";
		}
	}

	std::string removeStack() // Moves head of queue to turntable
	{
		if (turnTableCar_ != NULL) { return "Turntable occupied!"; }
		else if (stack_.empty()) { return "Stack empty!"; }
		else
		{
			turnTableCar_ = stack_.top();
			stack_.pop();
			return "OK";
		}
	}

	std::string topCar()  // Outputs turntable car
	{
		if (turnTableCar_ == NULL) { return "Turntable empty!"; }
		else { return turnTableCar_.toString(); }
	}

	std::string topQueue() // Outputs head of queue
	{
		if (queue_.top() == NULL) { return "Queue empty!"; }
		else { return queue_.top().toString(); }
	}

	std::string topStack()  // Outputs head of stack
	{
		if (stack_.top() == NULL) { return "Stack empty!"; }
		else { return stack_.top().toString(); }
	}

	std::string sizeQueue() { return std::to_string(queue_.size()); } // Outputs size of queue
	
	std::string sizeStack() { return std::to_string(stack_.size()); }  // Outputs size of stack

	std::string sizeTrain() { return std::to_string(train_.size()); }  // Outputs size of stack

	std::string find(T car) // Displays location of car (turntable, queue, stack, vector) and index
	{
		int returnIndex;
		if (turnTableCar_ == car) { return "Turntable"; }
		else if ((returnIndex = queue_.find(car)) >= 0) { return "Queue[" + std::to_string(returnIndex) + "]"; }
		else if ((returnIndex = stack_.find(car)) >= 0) { return "Stack[" + std::to_string(returnIndex) + "]"; }
		else if ((returnIndex = train_.find(car)) >= 0) { return "Train[" + std::to_string(returnIndex) + "]"; }
		else { return "Not Found!"; }
	}

	std::string printQueue() // Outputs entire queue's contents
	{
		std::stringstream outQueue;
		for (size_t i = 0; i < queue_.size(); ++i) { outQueue << queue_.at(i).toString() << " "; }
		return outQueue.str();
	}

	std::string printStack() // Outputs entire stack's contents
	{
		std::stringstream outStack;
		for (size_t i = 0; i < stack_.size(); ++i) { outStack << stack_.at(i).toString() << " "; }
		return outStack.str();
	}

	
	std::string toString()  // Outputs entire vector's (train's) contents
	{
		if (train_.empty()) { return "Train empty!"; }
		else
		{
			std::stringstream outTrain;
			for (size_t i = 0; i < train_.size(); ++i) { outTrain << train_.at(i).toString() << " "; }
			return outTrain.str();
		}
	}

	friend std::ostream& operator<<(std::ostream& os, Station& rtn) { return os << rtn.toString(); }
};

#endif //STATION_H