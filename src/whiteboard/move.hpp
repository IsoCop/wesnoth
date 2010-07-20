/* $Id$ */
/*
 Copyright (C) 2010 by Gabriel Morin <gabrielmorin (at) gmail (dot) com>
 Part of the Battle for Wesnoth Project http://www.wesnoth.org

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License version 2
 or at your option any later version.
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY.

 See the COPYING file for more details.
 */

/**
 * @file move.hpp
 */

#ifndef WB_MOVE_HPP_
#define WB_MOVE_HPP_

#include "action.hpp"
#include "map_location.hpp"
#include "typedefs.hpp"

#include <boost/enable_shared_from_this.hpp>

namespace wb {

/**
 * A planned move, represented on the map by an arrow and
 * a ghosted unit in the destination hex.
 */
class move : public action, public boost::enable_shared_from_this<move>
{
public:
	friend class validate_visitor;
	friend class highlight_visitor;
	friend std::ostream& operator<<(std::ostream& s, move const& move);

	static const double ALPHA_HIGHLIGHT;
	static const double ALPHA_NORMAL;
	static const std::string ARROW_STYLE_VALID;
	static const std::string ARROW_STYLE_INVALID;

	move(const map_location& source_hex, const map_location& target_hex, arrow_ptr arrow,
			fake_unit_ptr fake_unit);
	virtual ~move();

	virtual std::ostream& print(std::ostream& s) const;

	virtual void accept(visitor& v);

	virtual bool execute();

	/** Return the unit targeted by this action. Null if unit doesn't exist. */
	virtual unit* get_unit() const;

	virtual arrow_ptr get_arrow() { return arrow_; }
	virtual fake_unit_ptr get_fake_unit() { return fake_unit_; }
	virtual map_location const& get_source_hex() const { return source_hex_; }
	virtual map_location const& get_dest_hex() const { return dest_hex_; }

	/** Applies temporarily the result of this action to the specified unit map. */
	virtual void apply_temp_modifier(unit_map& unit_map);
	/** Removes the result of this action from the specified unit map. */
	virtual void remove_temp_modifier(unit_map& unit_map);

	/** Gets called by display when drawing a hex, to allow actions to draw to the screen. */
	virtual void draw_hex(const map_location& hex);

	virtual bool is_numbering_hex(const map_location& hex) const;

	virtual void set_valid(bool valid);
	virtual bool is_valid() { return valid_; }

protected:
	int underlying_unit_id_;
	map_location source_hex_;
	map_location dest_hex_;
	int movement_cost_;

	arrow_ptr arrow_;
	fake_unit_ptr fake_unit_;

	bool valid_;
};

/** Dumps an move on a stream, for debug purposes. */
std::ostream &operator<<(std::ostream &s, wb::move const& move);

} // end namespace wb

#endif /* WB_MOVE_HPP_ */
