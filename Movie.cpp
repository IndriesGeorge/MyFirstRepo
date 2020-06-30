#include "Movie.h"

int Movie::get_id() const noexcept
{
	return id;
}

string Movie::get_title() const
{
	return title;
}

string Movie::get_genre() const
{
	return genre;
}

int Movie::get_year() const noexcept
{
	return year;
}

string Movie::get_protagonist() const
{
	return protagonist;
}

void Movie::set_title(string str)
{
	title = str;
}

void Movie::set_genre(string str)
{
	genre = str;
}

void Movie::set_year(int val)
{
	year = val;
}

void Movie::set_protagonist(string str)
{
	protagonist = str;
}
