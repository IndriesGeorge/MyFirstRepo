#include "Movie.h"
#include "Repository.h"

class UndoAction
{
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() = default;
};

class UndoAdd : public UndoAction
{
	Repository& rep;
	Movie added_movie;
	
public:

	UndoAdd(Repository& rep, const Movie& m) :rep{ rep }, added_movie{ m }{}

	void doUndo() override
	{
		rep.repo_delete_movie(added_movie);
	}

};

class UndoDelete : public UndoAction
{
	Repository& rep;
	Movie deleted_movie;

public:

	UndoDelete(Repository& rep, const Movie& m) :rep{ rep }, deleted_movie{ m }{}

	void doUndo() override
	{
		rep.repo_add_movie(deleted_movie);
	}

};

class UndoUpdate : public UndoAction
{
	Repository& rep;
	Movie updated_movie;

public:

	UndoUpdate(Repository& rep, const Movie& m) :rep{ rep }, updated_movie{ m }{}

	void doUndo() override
	{
		rep.repo_update_movie(updated_movie);
	}

};