#include "test_runner.h"

using namespace std;

class Rational {
public:
	// Р’С‹ РјРѕР¶РµС‚Рµ РІСЃС‚Р°РІР»СЏС‚СЊ СЃСЋРґР° СЂР°Р·Р»РёС‡РЅС‹Рµ СЂРµР°Р»РёР·Р°С†РёРё,
	// С‡С‚РѕР±С‹ РїСЂРѕРІРµСЂРёС‚СЊ, С‡С‚Рѕ РІР°С€Рё С‚РµСЃС‚С‹ РїСЂРѕРїСѓСЃРєР°СЋС‚ РєРѕСЂСЂРµРєС‚РЅС‹Р№ РєРѕРґ
	// Рё Р»РѕРІСЏС‚ РЅРµРєРѕСЂСЂРµРєС‚РЅС‹Р№

	Rational();
	Rational(int numerator, int denominator) {
	}

	int Numerator() const {
	}

	int Denominator() const {
	}
};

void TestBasicConstructor() {
	Rational r;
	Assert(r.Numerator() == 0, "Basic constructor zero num");
	Assert(r.Denominator() == 1, "Basic constructor one den");
}

void TestConstructorReduces() {
	Rational r(5, 10);
	Assert(r.Numerator() == 1, "Num reduces");
	Assert(r.Denominator() == 2, "Den reduces");
}

void TestLtZero() {
	Rational r(-1, 2);
	Assert(r.Numerator() < 0, "Num < 0 didn't change");
	Assert(r.Denominator() > 0, "Den > 0 didn't change");
	r = Rational(2, -3);
	Assert(r.Numerator() < 0, "Num < 0 changed");
	Assert(r.Denominator() > 0, "Den > 0 changed");
}

void TestGtZero() {
	Rational r(-1, -2);
	Assert(r.Numerator() > 0, "Num > 0 changed");
	Assert(r.Denominator() > 0, "Den > 0 changed");
}

void TestNumEqZero() {
	Rational r(0, 76);
	Assert(r.Denominator() == 1, "Num is zero => den is one");
}

void TestAll2() {
	TestRunner runner;
	runner.RunTest(TestBasicConstructor, "TestBasicConstructor");
	runner.RunTest(TestConstructorReduces, "TestConstructorReduces");
	runner.RunTest(TestLtZero, "TestLtZero");
	runner.RunTest(TestGtZero, "TestGtZero");
	runner.RunTest(TestNumEqZero, "TestNumEqZero");
}

int main23() {
	TestAll2();
	// РґРѕР±Р°РІСЊС‚Рµ СЃСЋРґР° СЃРІРѕРё С‚РµСЃС‚С‹
	return 0;
}