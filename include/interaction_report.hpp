#ifndef TRAITADAPT_INTERACTIONREPORT_HPP
#define TRAITADAPT_INTERACTIONREPORT_HPP

#include <string>
#include <list>
#include <unordered_map>

#include <trait.hpp>

namespace hapnmc { namespace traitadapt {

	/** The float value assigned to the tag represents how effective an individual tag is on average, higher is better */
	struct TagEffect 
	{
		std::string tag;
		float effectiveness; // 1.0f corresponds to 100% effectiveness, i.e. full intended effect

		// quick hacks: comparison is for priority purposes, which is why the lt op uses gt
		bool operator<(const TagEffect& tageff)
		{
			return effectiveness > tageff.effectiveness;
		}
	};

	/** Shows effectiveness of a specific tag combination, these are usually a better indication of what to use or avoid */
	struct TraitEffect 
	{
		Trait trait;
		float effectiveness;

		bool operator<(const TraitEffect& treff)
		{
			return effectiveness > treff.effectiveness;
		}
	};

	/**
	 * Encompases info that could be useful for the TraitSelector class for the purpose of
	 * selecting traits based on the previous interaction. Note that this only covers a single interaction.
	 * If multiple interactions need to be taken into account, it is advised to find common points in
	 * multiple reports or use a more generic system alltogether for larger data sets. This, 
	 * however, should be unnecessary in most cases, as long as "interaction" is defined correctly
	 * to fit the requirements.
	 *
	 * As a rule of thumb, an interaction should be defined in such a way as to allow a number of
	 * different actions to be performed within its limits, preferably including actions with differing
	 * tagsets with an emphasis on primary tags. This way the relative effectiveness value 
	 * will be more accurate.
	 *
	 * Every action measures its own effectiveness which it passes to InteractionReport. IR then
	 * constructs prioritised lists of tags and traits based on those effectiveness reports.
	 *
	 * p.s. it is intended for the effectiveness priority to be calculated by an external script to be customizable by end user,
	 * but for the sake of keeping this demo light and free of external libs, it will be hardcoded here.
	 */
	class InteractionReport
	{
	private:
		// ================ Rating Parameters ================================= //
		// these control how the tags are rated, should be provided externally
		/** Tag effectiveness is multiplied by this value if it is a primary tag. */
		float _primary_tag_multiplier = 1.1f; // TODO get rid

		// ================ Effectiveness ================================= //
		/** Shows average effectiveness of any single tag in an interaction, ordered high to low. */
		std::list<TagEffect> _tags_by_effect;

		/** Shows average effectiveness of any used traits in an interaction, ordered high to low. */
		std::list<TraitEffect> _traits_by_effect;

		// ========== Intermediate Containers ===================== //

		std::unordered_map<std::string, std::list<float>> _tags_effects; 
		std::unordered_map<Trait, std::list<float>> _traits_effects; 

		// ================ Stats ================================= //
		int16_t _number_of_actions_processed = 0;

		float _average_action_effectiveness = 0.0f; // 1.0f corresponds to full effect

		// ================ Methods ================================= //
		void applyExternalMods();

	public:

		const std::list<TagEffect>& GetTagEffectiveness() const { return _tags_by_effect; }
		const std::list<TraitEffect>& GetTraitEffectiveness() const { return _traits_by_effect; }

		/**
		* After an action is resolved this method is called with action's trait and effectiveness.
		* If actions with delayed effect exist, this should be called in a loop for each action with final effectiveness
		* at the end of interaction.
		* A version with context would include the subject's trait if any, but for this example it is not necessary.
		*/
		void Process(const Trait& t, float effectiveness);

		/** Constructs the sorted effectiveness lists */
		void Finalize();

	};

}} // hapnmc::traitadapt

#endif // TRAITADAPT_INTERACTIONREPORT_HPP