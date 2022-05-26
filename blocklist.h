#pragma once
//基类
class Block
{
public:
	Block(int row = 0, int col = 0,int face1=0) :centerx(row), centery(col), face(face1),num(0) {}
	virtual ~Block() {}
	int num;//编号
	int face;//面向状态，一共有0123四个状态，构造时为0
	int centerx;
	int centery;
	int b0x=0, b0y=0, b1x=0, b1y=0, b2x=0, b2y=0, b3x=0, b3y=0;
	virtual void Set(int row, int col, int face) {
		centerx = row, centery = col, this->face = face;
	}
	void Reset() {
		centerx = precx, centery = precy, face = pref;
		b0x = preb0x, b0y = preb0y, b1x = preb1x, b1y = preb1y, b2x = preb2x, b2y = preb2y, b3x = preb3x, b3y = preb3y;
	}
	//	o - y
	//	|
	//	x
protected:
	int preb0x = 0, preb0y = 0, preb1x = 0, preb1y = 0, preb2x = 0, preb2y = 0, preb3x = 0, preb3y = 0;
	int precx = 0, precy = 0, pref = 0;
};
//派生类
class I :public Block
{
public:
	I(int row, int col,int face1) :Block(row, col,face1) {
		num = 1;
		this->Set(row, col, face1);
	}
	~I() {}
	void Set(int row, int col, int face1) {
		precx = centerx, precy = centery, pref = face;
		preb0x = b0x, preb0y = b0y, preb1x = b1x, preb1y = b1y, preb2x = b2x, preb2y = b2y, preb3x = b3x, preb3y = b3y;
		centerx = row, centery = col, face = face1;
		b0x = centerx, b0y = centery;
		if (face == 0) { 
			b1x = b0x, b1y = b0y + 1, b2x = b0x, b2y = b0y - 1, b3x = b0x, b3y = b0y - 2;
			while (b3y < 0) this->Set(row, col + 1, 0);
			while (b1y > 9) this->Set(row, col - 1, 0);
		}
		//b3 b2 b0 b1
		else if (face == 1) { b1x = b0x - 1, b1y = b0y, b2x = b0x + 1, b2y = b0y, b3x = b0x + 2, b3y = b0y; }
		//b1
		//b0
		//b2
		//b3
		else if (face == 2) { 
			b1x = b0x, b1y = b0y - 1, b2x = b0x, b2y = b0y + 1, b3x = b0x, b3y = b0y + 2; 
			while (b1y < 0) this->Set(row, col + 1, 0);
			while (b3y > 9) this->Set(row, col - 1, 0);
		}
		//b1 b0 b2 b3
		else if (face == 3) { b1x = b0x + 1, b1y = b0y, b2x = b0x - 1, b2y = b0y, b3x = b0x - 2, b3y = b0y; }
		//b3
		//b2
		//b0
		//b1
	}
};
class J :public Block
{
public:
	J(int row, int col,int face1) :Block(row, col,face1) {
		num = 2;
		this->Set(row, col, face1);
	}
	~J() {}
	void Set(int row, int col, int face1) {
		precx = centerx, precy = centery, pref = face;
		preb0x = b0x, preb0y = b0y, preb1x = b1x, preb1y = b1y, preb2x = b2x, preb2y = b2y, preb3x = b3x, preb3y = b3y;
		centerx = row, centery = col, face = face1;
		b0x = centerx, b0y = centery;
		if (face == 0) { 
			b1x = b0x, b1y = b0y + 1, b2x = b0x + 1, b2y = b0y, b3x = b0x + 2, b3y = b0y; 
			while (b1y > 9) this->Set(row, col - 1, 0);
		}
		//b0 b1
		//b2
		//b3
		else if (face == 1) {
			b1x = b0x - 1, b1y = b0y, b2x = b0x, b2y = b0y + 1, b3x = b0x, b3y = b0y + 2;
			while (b3y > 9) this->Set(row, col - 1, 0);
		}
		//b1
		//b0 b2 b3
		else if (face == 2) { 
			b1x = b0x, b1y = b0y - 1, b2x = b0x - 1, b2y = b0y, b3x = b0x - 2, b3y = b0y; 
			while (b1y < 0) this->Set(row, col + 1, 0);
		}
		//	 b3
		//	 b2
		//b1 b0
		else if (face == 3) { 
			b1x = b0x + 1, b1y = b0y, b2x = b0x, b2y = b0y - 1, b3x = b0x, b3y = b0y - 2; 
			while (b3y < 0) this->Set(row, col + 1, 0);
		}
		//b3 b2 b0
		//		b1
	}
};
class L :public Block
{
public:
	L(int row, int col,int face1) :Block(row, col,face1) {
		num = 3;
		this->Set(row, col, face1);
	}
	~L() {}
	void Set(int row, int col, int face1) {
		precx = centerx, precy = centery, pref = face;
		preb0x = b0x, preb0y = b0y, preb1x = b1x, preb1y = b1y, preb2x = b2x, preb2y = b2y, preb3x = b3x, preb3y = b3y;
		centerx = row, centery = col, face = face1;
		b0x = centerx, b0y = centery;
		if (face == 0) { 
			b1x = b0x, b1y = b0y - 1, b2x = b0x + 1, b2y = b0y, b3x = b0x + 2, b3y = b0y;
			while (b1y < 0) this->Set(row, col + 1, 0);
		}
		//b1 b0
		//	 b2
		//	 b3
		else if (face == 1) { 
			b1x = b0x + 1, b1y = b0y, b2x = b0x, b2y = b0y + 1, b3x = b0x, b3y = b0y + 2; 
			while (b3y > 9) this->Set(row, col - 1, 0);
		}
		//b0 b2 b3
		//b1
		else if (face == 2) {
			b1x = b0x, b1y = b0y + 1, b2x = b0x - 1, b2y = b0y, b3x = b0x - 2, b3y = b0y;
			while (b1y > 9) this->Set(row, col - 1, 0);
		}
		//b3
		//b2
		//b0 b1
		else if (face == 3) {
			b1x = b0x - 1, b1y = b0y, b2x = b0x, b2y = b0y - 1, b3x = b0x, b3y = b0y - 2;
			while (b3y < 0) this->Set(row, col + 1, 0);
		}
		//		b1
		//b3 b2 b0
	}
};
class O :public Block
{
public:
	O(int row, int col,int face1) :Block(row, col,face1) {
		num = 4;
		this->Set(row, col, face1);
	}
	~O() {}
	void Set(int row, int col, int face1) {
		precx = centerx, precy = centery, pref = face;
		preb0x = b0x, preb0y = b0y, preb1x = b1x, preb1y = b1y, preb2x = b2x, preb2y = b2y, preb3x = b3x, preb3y = b3y;
		centerx = row, centery = col, face = face1;
		b0x = centerx, b0y = centery;
		if (face == 0) { 
			b1x = b0x + 1, b1y = b0y, b2x = b0x + 1, b2y = b0y + 1, b3x = b0x, b3y = b0y + 1; 
			while (b3y > 9) this->Set(row, col - 1, 0);
		}
		//b0 b3
		//b1 b2
		else if (face == 1) { 
			b1x = b0x, b1y = b0y + 1, b2x = b0x - 1, b2y = b0y + 1, b3x = b0x - 1, b3y = b0y; 
			while (b2y > 9) this->Set(row, col - 1, 0);
		}
		//b3 b2
		//b0 b1
		else if (face == 2) {
			b1x = b0x - 1, b1y = b0y, b2x = b0x - 1, b2y = b0y - 1, b3x = b0x, b3y = b0y - 1;
			while (b3y < 0) this->Set(row, col + 1, 0);
		}
		//b2 b1
		//b3 b0
		else if (face == 3) { 
			b1x = b0x, b1y = b0y - 1, b2x = b0x + 1, b2y = b0y - 1, b3x = b0x + 1, b3y = b0y; 
			while (b2y < 0) this->Set(row, col + 1, 0);
		}
		//b1 b0
		//b2 b3
	}
};
class S :public Block
{
public:
	S(int row, int col,int face1) :Block(row, col,face1) {
		num = 5;
		this->Set(row, col, face1);
	}
	~S() {}
	void Set(int row, int col, int face1) {
		precx = centerx, precy = centery, pref = face;
		preb0x = b0x, preb0y = b0y, preb1x = b1x, preb1y = b1y, preb2x = b2x, preb2y = b2y, preb3x = b3x, preb3y = b3y;
		centerx = row, centery = col, face = face1;
		b0x = centerx, b0y = centery;
		if (face == 0) {
			b1x = b0x - 1, b1y = b0y, b2x = b0x, b2y = b0y + 1, b3x = b0x + 1, b3y = b0y + 1; 
			while (b3y > 9) this->Set(row, col - 1, 0);
		}
		//b1
		//b0 b2
		//	 b3
		else if (face == 1) { 
			b1x = b0x, b1y = b0y - 1, b2x = b0x - 1, b2y = b0y, b3x = b0x - 1, b3y = b0y + 1;
			while (b1y < 0) this->Set(row, col + 1, 0);
			while (b3y > 9) this->Set(row, col - 1, 0);
		}
		//	 b2 b3
		//b1 b0
		else if (face == 2) {
			b1x = b0x + 1, b1y = b0y, b2x = b0x, b2y = b0y - 1, b3x = b0x - 1, b3y = b0y - 1;
			while (b3y < 0) this->Set(row, col + 1, 0);
		}
		//b3
		//b2 b0
		//	 b1
		else if (face == 3) {
			b1x = b0x, b1y = b0y + 1, b2x = b0x + 1, b2y = b0y, b3x = b0x + 1, b3y = b0y - 1;
			while (b3y < 0) this->Set(row, col + 1, 0);
			while (b1y > 9) this->Set(row, col - 1, 0);
		}
		//	 b0 b1
		//b3 b2
	}
};
class Z :public Block
{
public:
	Z(int row, int col,int face1) :Block(row, col,face1) {
		num = 6;
		this->Set(row, col, face1);
	}
	~Z() {}
	void Set(int row, int col, int face1) {
		precx = centerx, precy = centery, pref = face;
		preb0x = b0x, preb0y = b0y, preb1x = b1x, preb1y = b1y, preb2x = b2x, preb2y = b2y, preb3x = b3x, preb3y = b3y;
		centerx = row, centery = col, face = face1;
		b0x = centerx, b0y = centery;
		if (face == 0) { 
			b1x = b0x - 1, b1y = b0y, b2x = b0x, b2y = b0y - 1, b3x = b0x + 1, b3y = b0y - 1; 
			while (b3y < 0) this->Set(row, col + 1, 0);
		}
		//	 b1
		//b2 b0
		//b3
		else if (face == 1) { 
			b1x = b0x, b1y = b0y - 1, b2x = b0x + 1, b2y = b0y, b3x = b0x + 1, b3y = b0y + 1; 
			while (b1y < 0) this->Set(row, col + 1, 0);
			while (b3y > 9) this->Set(row, col - 1, 0);
		}
		//b1 b0
		//	 b2 b3
		else if (face == 2) { 
			b1x = b0x + 1, b1y = b0y, b2x = b0x, b2y = b0y + 1, b3x = b0x - 1, b3y = b0y + 1; 
			while (b3y > 9) this->Set(row, col - 1, 0);
		}
		//	 b3
		//b0 b2
		//b1
		else if (face == 3) { 
			b1x = b0x, b1y = b0y + 1, b2x = b0x - 1, b2y = b0y, b3x = b0x - 1, b3y = b0y - 1; 
			while (b3y < 0) this->Set(row, col + 1, 0);
			while (b1y > 9) this->Set(row, col - 1, 0);
		}
		//b3 b2
		//	 b0 b1
	}
};
class T :public Block
{
public:
	T(int row, int col,int face1) :Block(row, col,face1) {
		num = 7;
		this->Set(row, col, face1);
	}
	~T() {}
	void Set(int row, int col, int face1) {
		precx = centerx, precy = centery, pref = face;
		preb0x = b0x, preb0y = b0y, preb1x = b1x, preb1y = b1y, preb2x = b2x, preb2y = b2y, preb3x = b3x, preb3y = b3y;
		centerx = row, centery = col, face = face1;
		b0x = centerx, b0y = centery;
		if (face == 0) { 
			b1x = b0x - 1, b1y = b0y, b2x = b0x, b2y = b0y + 1, b3x = b0x + 1, b3y = b0y; 
			while (b2y > 9) this->Set(row, col - 1, 0);
		}
		//b1
		//b0 b2
		//b3
		else if (face == 1) { 
			b1x = b0x, b1y = b0y - 1, b2x = b0x - 1, b2y = b0y, b3x = b0x, b3y = b0y + 1; 
			while (b1y < 0) this->Set(row, col + 1, 0);
			while (b3y > 9) this->Set(row, col - 1, 0);
		}
		//	 b2
		//b1 b0 b3
		else if (face == 2) { 
			b1x = b0x + 1, b1y = b0y, b2x = b0x, b2y = b0y - 1, b3x = b0x - 1, b3y = b0y;
			while (b2y < 0) this->Set(row, col + 1, 0);
		}
		//	 b3
		//b2 b0
		//	 b1
		else if (face == 3) { 
			b1x = b0x, b1y = b0y + 1, b2x = b0x + 1, b2y = b0y, b3x = b0x, b3y = b0y - 1; 
			while (b3y < 0) this->Set(row, col + 1, 0);
			while (b1y > 9) this->Set(row, col - 1, 0);
		}
		//b3 b0 b1
		//	 b2
	}
};

