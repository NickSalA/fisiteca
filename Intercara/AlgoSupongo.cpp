#include <iostream>
#include <string>

using namespace std;

class Monitor {
public:
	virtual string getDimension() = 0;
	virtual void setResolution(int height, int width) = 0;
protected:
	int height, width;
};

class Dell : public Monitor{
public:
	void setResolution(int height, int width)
	{
		this->height = height;
		this->width = width;
	}
	string getDimension()
	{
		string strDim = std::to_string(this->height) + "x" + std::to_string(this->width);
		return strDim;
	}
};
class Samsung : public Monitor {
public:
	void setResolution(int height, int width)
	{
		this->height = height;
		this->width = width;
	}
	string getDimension()
	{
		string strDim = std::to_string(this->height) + "x" + std::to_string(this->width);
		return strDim;
	}	
};

int main(void)
{
	Dell dellMon;
	dellMon.setResolution(1920, 720);
	cout << dellMon.getDimension() << endl;

	Samsung samMon;
	samMon.setResolution(1024, 768);
	cout << samMon.getDimension() << endl;

}