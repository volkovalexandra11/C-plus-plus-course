#include "test_runner.h"

using namespace std;


class Person {
public:
	// Р’С‹ РјРѕР¶РµС‚Рµ РІСЃС‚Р°РІР»СЏС‚СЊ СЃСЋРґР° СЂР°Р·Р»РёС‡РЅС‹Рµ СЂРµР°Р»РёР·Р°С†РёРё РєР»Р°СЃСЃР°,
	// С‡С‚РѕР±С‹ РїСЂРѕРІРµСЂРёС‚СЊ, С‡С‚Рѕ РІР°С€Рё С‚РµСЃС‚С‹ РїСЂРѕРїСѓСЃРєР°СЋС‚ РєРѕСЂСЂРµРєС‚РЅС‹Р№ РєРѕРґ
	// Рё Р»РѕРІСЏС‚ РЅРµРєРѕСЂСЂРµРєС‚РЅС‹Р№
	void ChangeFirstName(int year, const string& first_name) {
	}
	void ChangeLastName(int year, const string& last_name) {
	}
	string GetFullName(int year) {
	}
};

void TestIncognito() {
	Person p;
	Assert(p.GetFullName(123) == "Incognito", "Test Incognito");
}

void TestUnknownLastName() {
	Person p;
	p.ChangeFirstName(214, "Polina");
	Assert(p.GetFullName(215) == "Polina with unknown last name", "");
}

void TestUnknownFirstName() {
	Person p;
	p.ChangeLastName(214, "Pshenova");
	Assert(p.GetFullName(215) == "Pshenova with unknown first name", "");
}

void TestAllChangedName() {
	Person p;
	p.ChangeFirstName(213, "Polina");
	p.ChangeLastName(214, "Pshenova");
	Assert(p.GetFullName(215) == "Polina Pshenova", "Must be Polina Pshenova");
}


void TestAll1() {
	TestRunner runner;
	runner.RunTest(TestIncognito, "TestIncognito");
	runner.RunTest(TestUnknownFirstName, "TestUnknownFirstName");
	runner.RunTest(TestUnknownLastName, "TestUnknownLastName");
	runner.RunTest(TestAllChangedName, "TestAllChangedName");
}

int main54() {
	// РґРѕР±Р°РІСЊС‚Рµ СЃСЋРґР° СЃРІРѕРё С‚РµСЃС‚С‹
	TestAll1();
	return 0;
}