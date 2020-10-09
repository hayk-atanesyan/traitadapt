#ifndef TRAITADAPT_TRAIT_HPP
#define TRAITADAPT_TRAIT_HPP

#include <string>
#include <unordered_set>



namespace hapnmc { namespace traitadapt {

	/**
	 * Metadata for actions and other trait carriers. All tags go into one trait.
	 *
	 * There are different types of trait carriers, most common ones are actions. Traits are
	 * used to identify useful properties of those carriers, most commonly for the purposes
	 * of dynamically selecting an action in an automated system based on specific rulesets
	 * provided externally. Another example would be world entities, as those can have traits
	 * and certain actions can interact with them based on those traits.
	 *
	 */
	class Trait
	{
	private:

		/** Most trait carriers can have multiple tags but only one primary. Carriers are commonly filtered by this tag. */
		std::string _primary_tag;

		/** Certain more complex rulesets care about those. E.g. "Primary tag is X and has secondary tag Y" */
		std::unordered_set<std::string> _secondary_tags;

	public:
		Trait() noexcept {}

		Trait(const std::string& primaryTag) : Trait()
		{
			SetPrimaryTag(primaryTag);
		}

		Trait(const Trait& t) : Trait()
		{
			Set(t);
		}

		void Set(const Trait& t)
		{
			SetPrimaryTag(t.GetPrimaryTag());
			SetSecondaryTags(t.GetSecondaryTags());
		}

		Trait& operator=(const Trait& t)
		{
			Set(t);

			return *this;
		}

		bool operator==(const Trait& t) const noexcept
		{
			return _primary_tag == t._primary_tag && _secondary_tags == t._secondary_tags;
		}

		const std::string& GetPrimaryTag() const { return _primary_tag; }
		const std::unordered_set<std::string>& GetSecondaryTags() const { return _secondary_tags; }

		void SetPrimaryTag(const std::string& tag) { _primary_tag = tag; }
		void SetSecondaryTags(const std::unordered_set<std::string>& tags)
		{
			_secondary_tags = tags;
		}

		bool HasSecondaryTag(const std::string& tag) const
		{
			return _secondary_tags.contains(tag);
		}

		bool HasTag(const std::string& tag) const
		{
			return _primary_tag == tag || HasSecondaryTag(tag);
		}

		void AddSecondaryTag(const std::string& tag)
		{
			if(HasTag(tag)) return;

			_secondary_tags.insert(tag);
		}

		void AddTag(const std::string& tag)
		{
			if(_primary_tag.empty()) _primary_tag = tag;
			else AddSecondaryTag(tag);
		}

		void RemoveSecondaryTag(const std::string& tag)
		{
			_secondary_tags.erase(tag);
		}

	};


	// ======== hash hack in ========== //
	template <class T>
	inline void hash_combine(std::size_t& seed, const T& v)
	{
	    std::hash<T> hasher;
	    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
	}

}} // hapnmc::traitadapt



// just a quick hash hack in to make example code work, no time for custom container
namespace std
{
	using hapnmc::traitadapt::Trait;
	using hapnmc::traitadapt::hash_combine;

	template <>
	struct hash<Trait>
	{
		std::size_t operator()(const Trait& t) const noexcept
		{
			std::size_t hash = 0;
			hash_combine(hash, t.GetPrimaryTag());

			// this could have an issue with order, in which case we could get a sorted list, but good enough for example
			for (const std::string& s : t.GetSecondaryTags()) {
				hash_combine(hash, s);
			}
			return hash;
		}
	};
} // namespace::std

#endif // TRAITADAPT_TRAIT_HPP
