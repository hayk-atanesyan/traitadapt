/**
 * This is just a quick and dirty example.
 *
 */

#include <trait_selector.hpp>
#include <iostream>

using namespace hapnmc::traitadapt;

int main(int argc, char* argv[])
{
	TraitSelector ts;
	InteractionReport ir;

	std::string tag1 ("the one");
	std::string tag2 ("number two");
	std::string tag3 ("the perfect number");
	std::string tag4 ("FOUR");

	Trait trait1(tag1);
	Trait trait2(tag2);
		trait2.AddTag(tag1);
	Trait trait3(tag3);
		trait3.AddTag(tag2);
	Trait trait4(tag4);
		trait3.AddTag(tag1);


	ir.Process(trait1, 0.6f);
	ir.Process(trait2, 0.6f);
	ir.Process(trait3, 0.9f);
	ir.Process(trait4, 0.0f);
	ir.Process(trait4, 0.1f);
	ir.Finalize();

	ts.AddTrait(trait1);
	ts.AddTrait(trait2);
	ts.AddTrait(trait3);
	ts.AddTrait(trait4);

	ts.Process(ir);

	for(const Trait& t : ts.GetAllUseful())
	{
		std::cout << t.GetPrimaryTag() << std::endl;
	}

	return 0;
}