#include "CustomTripPlanner.h"

CustomTripPlanner::CustomTripPlanner(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	availableStadiums = StadiumList(AppSettings.stadiums);
	availableStadiumsModel = new StadiumListModel();
	availableStadiumsModel->ShowStadiums(availableStadiums);
	ui.availableStadiums->setModel(availableStadiumsModel);

	chosenStadiumsModel = new StadiumListModel();
	chosenStadiumsModel->ShowStadiums(chosenStadiums);
	ui.chosenStadiums->setModel(chosenStadiumsModel);

	disconnect(ui.buttons, SIGNAL(accepted()),
			   this,       SLOT(accept()));

	connect(ui.addButton,      SIGNAL(clicked()),
			this,              SLOT(AddStadium()));
	connect(ui.removeButton,   SIGNAL(clicked()),
			this,              SLOT(RemoveStadium()));
	connect(ui.moveUpButton,   SIGNAL(clicked()),
			this,              SLOT(MoveUp()));
	connect(ui.moveDownButton, SIGNAL(clicked()),
			this,              SLOT(MoveDown()));
	connect(ui.buttons,        SIGNAL(accepted()),
			this,              SLOT(StartTrip()));
	connect(ui.buttons,        SIGNAL(rejected()),
			this,              SLOT(reject()));
}

void CustomTripPlanner::AddStadium()
{
	QModelIndex index = ui.availableStadiums->selectionModel()->currentIndex();

	if (index.isValid())
	{
		chosenStadiumsModel->AddStadium(availableStadiums[index.row()]);
		availableStadiumsModel->RemoveStadium(index.row());
	}
}

void CustomTripPlanner::RemoveStadium()
{
	QModelIndex index = ui.chosenStadiums->selectionModel()->currentIndex();

	if (index.isValid())
	{
		availableStadiumsModel->AddStadium(chosenStadiums[index.row()]);
		chosenStadiumsModel->RemoveStadium(index.row());
	}
}

void CustomTripPlanner::MoveUp()
{
	QModelIndex index = ui.chosenStadiums->selectionModel()->currentIndex();

	if (index.isValid())
		chosenStadiumsModel->MoveUp(index.row());
}

void CustomTripPlanner::MoveDown()
{
	QModelIndex index = ui.chosenStadiums->selectionModel()->currentIndex();

	if (index.isValid())
		chosenStadiumsModel->MoveDown(index.row());
}

void CustomTripPlanner::StartTrip()
{
	if (chosenStadiums.count() < 2)
	{
		(new QMessageBox(QMessageBox::Critical,
			             "", "You must select at least 2 stadiums to visit!"))->exec();
		return;
	}
	else
	{
		close();
		(new CurrentTrip(chosenStadiums))->exec();
	}
}