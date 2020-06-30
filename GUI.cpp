#include "GUI.h"

void GUI::initGUIComponents()
{
	QHBoxLayout* mainLy = new QHBoxLayout{};
	setLayout(mainLy);

	QGridLayout* gridLy = new QGridLayout;
	gridLy->addWidget(table);
	mainLy->addLayout(gridLy);

	QVBoxLayout* rightLy = new QVBoxLayout;

	QFormLayout* formsLy = new QFormLayout;
	formsLy->addRow("Movie ID: ", idTxt);
	formsLy->addRow("Movie Title: ", titleTxt);
	formsLy->addRow("Movie Genre: ", genreCombo);
	genreCombo->addItems(genresList);
	yearSpin->setRange(1895, 2030);
	formsLy->addRow("Release Year: ", yearSpin);
	formsLy->addRow("Main Actor: ", protagonistTxt);
	rightLy->addLayout(formsLy);

	QHBoxLayout* buttonsLy = new QHBoxLayout;
	buttonsLy->addWidget(addButton);
	buttonsLy->addWidget(deleteButton);
	buttonsLy->addWidget(updateButton);
	rightLy->addLayout(buttonsLy);

	QHBoxLayout* buttonsLy2 = new QHBoxLayout;
	buttonsLy2->addWidget(ReloadButton);
	buttonsLy2->addWidget(UndoButton);
	rightLy->addLayout(buttonsLy2);

	QHBoxLayout* buttonsLy3 = new QHBoxLayout;
	buttonsLy3->addWidget(openCartButton);
	buttonsLy3->addWidget(openCartHistogram);
	rightLy->addLayout(buttonsLy3);

	mainLy->addLayout(rightLy);
}

void GUI::initConnect()
{
	QObject::connect(addButton, &QPushButton::clicked, [&]() {

		auto id = idTxt->text().toInt();
		auto title = titleTxt->text().toStdString();
		auto genre = genreCombo->currentText().toStdString();
		auto year = yearSpin->value();
		auto protagonist = protagonistTxt->text().toStdString();

		try
		{
			serv.service_add_movie(id, title, genre, year, protagonist);
		}
		catch (RepoException ex)
		{
			string message = ex.get_exception_message();
			QString warning_message = QString::fromStdString(message);
			QMessageBox::warning(nullptr, "Warning!\n", warning_message);
		}
		catch (Exception ex)
		{
			string message = ex.get_validation_messages();
			QString warning_message = QString::fromStdString(message);
			QMessageBox::warning(nullptr, "Warning!\n", warning_message);
		}

		reloadTable(serv.service_get_all_movies());

		});

	QObject::connect(updateButton, &QPushButton::clicked, [&]() {

		auto id = idTxt->text().toInt();
		auto title = titleTxt->text().toStdString();
		auto genre = genreCombo->currentText().toStdString();
		auto year = yearSpin->value();
		auto protagonist = protagonistTxt->text().toStdString();

		try
		{
			serv.service_update_movie(id, title, genre, year, protagonist);
		}
		catch (RepoException ex)
		{
			string message = ex.get_exception_message();
			QString warning_message = QString::fromStdString(message);
			QMessageBox::warning(nullptr, "Warning!\n", warning_message);
		}
		catch (Exception ex)
		{
			string message = ex.get_validation_messages();
			QString warning_message = QString::fromStdString(message);
			QMessageBox::warning(nullptr, "Warning!\n", warning_message);
		}

		reloadTable(serv.service_get_all_movies());

		});

	QObject::connect(deleteButton, &QPushButton::clicked, [&]() {

		auto id = idTxt->text().toInt();

		try
		{
			serv.service_delete_movie(id);
		}
		catch (RepoException ex)
		{
			string message = ex.get_exception_message();
			QString warning_message = QString::fromStdString(message);
			QMessageBox::warning(nullptr, "Warning!\n", warning_message);
		}

		reloadTable(serv.service_get_all_movies());

		});

	QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {

		if (table->selectionModel()->selectedIndexes().isEmpty())
		{
			idTxt->setText("");
			titleTxt->setText("");
			genreCombo->setCurrentText("Action");
			yearSpin->setValue(1895);
			protagonistTxt->setText("");
		}
		else
		{
			auto selectedRow = table->selectionModel()->selectedIndexes().at(0).row();
			auto column0 = table->model()->index(selectedRow, 0);
			auto id = table->model()->data(column0, Qt::UserRole).toInt();
			auto movie = serv.service_find_movie(id);
			idTxt->setText(QString::number(movie.get_id()));
			titleTxt->setText(QString::fromStdString(movie.get_title()));
			genreCombo->setCurrentText(QString::fromStdString(movie.get_genre()));
			yearSpin->setValue(movie.get_year());
			protagonistTxt->setText(QString::fromStdString(movie.get_protagonist()));
		}

		});

	QObject::connect(UndoButton, &QPushButton::clicked, [&]() {

		try
		{
			serv.undo();
		}
		catch (RepoException ex)
		{
			string message = ex.get_exception_message();
			QString warning_message = QString::fromStdString(message);
			QMessageBox::warning(nullptr, "Warning!\n", warning_message);
		}

		reloadTable(serv.service_get_all_movies());

		});

	QObject::connect(ReloadButton, &QPushButton::clicked, [&]() {

		reloadTable(serv.service_get_all_movies());

		});

	QObject::connect(openCartButton, &QPushButton::clicked, [&]() {

		CartGUI* cartGui = new CartGUI{ serv.get_cart() };
		cartGui->show();

		});

}

void GUI::reloadTable(vector<Movie> movies)
{
	model->setMovies(movies);
	model->refresh();
}
