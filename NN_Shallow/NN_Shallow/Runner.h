#pragma once
#include "Config.h"
#include "DataIn.h"
#include "Input.h"
#include "HiddenLayer.h"
#include "Output.h"
#include "DataOut.h"
#include <cstddef>

class Runner
{
public:
	Runner();
	void training();
	void backpropogation();
	~Runner();
};


