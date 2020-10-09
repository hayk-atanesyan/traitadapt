#ifndef TRAITADAPT_TRAITCARRIER_HPP
#define TRAITADAPT_TRAITCARRIER_HPP

#include <trait.hpp>

namespace hapnmc { namespace traitadapt {

	/**
	 * A generic Base class for the sake of keeping code more modular.
	 *
	 */
	class TraitCarrier
	{
	private:
		Trait _trait;

	public:
		void SetTrait(Trait t) { _trait = t; }
		Trait& GetTraitRef() { return _trait; }
		const Trait& GetTrait() { return _trait; }
	};

}} // hapnmc::traitadapt

#endif // TRAITADAPT_TRAITCARRIER_HPP