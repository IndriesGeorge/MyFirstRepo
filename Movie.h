#pragma once

#include <string>

using std::string;

class Movie
{
	int id;
	string title;
	string genre;
	int year;
	string protagonist;

public:

	// Movie Constructor
	Movie(int id, string tt, string gn, int yy, string pp) :id{ id }, title{ tt }, genre{ gn }, year{ yy }, protagonist{ pp }{}

	// Copy Constructor
	Movie(const Movie& ot) :id{ ot.id }, title{ ot.title }, genre{ ot.genre }, year{ ot.year }, protagonist{ ot.protagonist }{}

	// Return the id
	int get_id() const noexcept;

	// Returns the title
	string get_title() const;
	
	// Returns the genre
	string get_genre() const;

	// Returns the year of apparition
	int get_year() const noexcept;

	// Returns the main actor's name
	string get_protagonist() const;

	// Sets the title
	void set_title(string str);

	// Sets the genre
	void set_genre(string str);

	// Sets the year of apparition
	void set_year(int val);

	// Sets the main actor's name
	void set_protagonist(string str);

};

