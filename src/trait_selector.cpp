#include <trait_selector.hpp>
#include <algorithm>

namespace hapnmc { namespace traitadapt {

	void TraitSelector::Process(const InteractionReport& ir)
	{
		if(_available_traits.empty()) return;

		_useful_traits.clear();

		// full trait matches have higher priority
		for(const TraitEffect& tref : ir.GetTraitEffectiveness()) {
			if(_available_traits.contains(tref.trait)) {
				_useful_traits.push_back(tref.trait);
			}
		}

		// partial matches work as well, primary tag checks take priority
		for(const TagEffect& tgef : ir.GetTagEffectiveness()) {
			for(const Trait& avtrait : _available_traits) {
				// no need for dupes
				if((std::find(_useful_traits.begin(), _useful_traits.end(), avtrait) != _useful_traits.end())) continue;

				if(avtrait.GetPrimaryTag() == tgef.tag) {
					_useful_traits.push_back(avtrait);
				}
			}
		}

		// secondary tag matches are added after primary matches
		for(const TagEffect& tgef : ir.GetTagEffectiveness()) {
			for(const Trait& avtrait : _available_traits) {
				// no need for dupes
				if((std::find(_useful_traits.begin(), _useful_traits.end(), avtrait) != _useful_traits.end())) continue;

				if(avtrait.HasSecondaryTag(tgef.tag)) {
					_useful_traits.push_back(avtrait);
				}
			}
		}
	}

	const Trait& TraitSelector::GetBest()
	{
		return _useful_traits.front();
	}

	const std::list<Trait>& TraitSelector::GetAllUseful()
	{
		return _useful_traits;
	}

}} // hapnmc::traitadapt