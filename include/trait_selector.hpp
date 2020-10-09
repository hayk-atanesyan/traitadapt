#ifndef TRAITADAPT_TRAITSELECTOR_HPP
#define TRAITADAPT_TRAITSELECTOR_HPP

#include <trait.hpp>
#include <interaction_report.hpp>
#include <list>
#include <unordered_set>

namespace hapnmc { namespace traitadapt {

	/**
	 * This class is responsible for selecting traits based on interaction reports (adapting).
	 *
	 * It is based on a single interaction. It is possible to incorporate multiple interactions
	 * by creating an amalgamated report, but this should be entirely unnecessary as long as 
	 * an "interaction" is defined correctly. 
	 */
	class TraitSelector
	{
	private:
		std::unordered_set<Trait> _available_traits;

		std::list<Trait> _useful_traits; // ordered best first
	public:
		/** Traits are added here before processing the interaction report. */
		void AddTrait(const Trait& t)
		{
			_available_traits.insert(t);
		}

		void RemoveTrait(const Trait& t)
		{
			_available_traits.erase(t);
		}

		/** Remove all traits, clear evaluations */
		void Clear()
		{
			_available_traits.clear();
			_useful_traits.clear();
		}

		/** Reshuffles available trait priorities based on the interaction report and provided ruleset. */
		void Process(const InteractionReport& ir);

		/** Returns the trait that would be best used in the next step */
		const Trait& GetBest();

		/** Returns a selection of useful traits, ordered by priority where applicable. */
		const std::list<Trait>& GetAllUseful();

		bool HasUsefulTraits()
		{
			return !_useful_traits.empty();
		}
	};

}} // hapnmc::traitadapt

#endif // TRAITADAPT_TRAITSELECTOR_HPP