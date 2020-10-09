#include <interaction_report.hpp>
#include <numeric>

namespace hapnmc { namespace traitadapt {

	void InteractionReport::Process(const Trait& t, float effectiveness)
	{
		Trait nt(t);	
		_traits_effects[t].push_back(effectiveness);

		_tags_effects[t.GetPrimaryTag()].push_back(effectiveness * _primary_tag_multiplier);

		for (const std::string& s : t.GetSecondaryTags()) {
			_tags_effects[s].push_back(effectiveness);
		}

		Finalize(); // actually should be called once at the end, but just to make sure example is simpler to run i'll keep this here
	}


	void InteractionReport::Finalize()
	{
		_tags_by_effect.clear();
		_traits_by_effect.clear();

		for(auto const& [tagname, efflist] : _tags_effects) {
			TagEffect te;
			te.tag = tagname;
			te.effectiveness = std::accumulate(std::begin(efflist), std::end(efflist), 0.0) / efflist.size();

			_tags_by_effect.push_back(te);
		}
		_tags_by_effect.sort();

		for(auto const& [trait, efflist] : _traits_effects) {
			TraitEffect te;
			te.trait = trait;
			te.effectiveness = std::accumulate(std::begin(efflist), std::end(efflist), 0.0) / efflist.size();

			_traits_by_effect.push_back(te);
		}
		_traits_by_effect.sort();
	}

}} // hapnmc::traitadapt