#pragma once

#include "../Types.h"

namespace Klang {

template<typename Data_T>
class TempVector {
public:

private:
	natptr _capacity;
	Data_T* _data;
	Data_T* _back;
};

}
