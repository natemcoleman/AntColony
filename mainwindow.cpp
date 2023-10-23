#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AntWorld.h"
#include <QGraphicsView>
#include <QDockWidget>
#include <QGraphicsView>
#include <QPainter>
#include <iostream>
#include <QLCDNumber>
#include <QTimer>
#include <QMouseEvent>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(originalWindowSize);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_pushButton_released()));
    timer->start(timerPauseValue);

    const QIcon settingsIcon = QIcon(":myicons/ant.png");
    setWindowIcon(QIcon(settingsIcon));

    build_world();

    setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_food(double foodX, double foodY)
{
    thisWorld.add_food(foodX, foodY);
}

void MainWindow::add_colony(double colonyX, double colonyY)
{
    thisWorld.add_colony(colonyX,colonyY);
}

void MainWindow::add_colony(double colonyX, double colonyY, int foodAmount)
{
    thisWorld.add_colony(colonyX,colonyY, foodAmount);
}

double MainWindow::scale_x_value(double inputXValue)
{
    QSize windowSize = this->size();
    int xSize = windowSize.width();

    double returnLocation = (inputXValue*xSize)/thisWorld.get_size_of_world();

    return returnLocation;
}

double MainWindow::scale_y_value(double inputYValue)
{
    QSize windowSize = this->size();
    int ySize = windowSize.height() - topBuffer;

    double returnLocation = (inputYValue*ySize)/thisWorld.get_size_of_world();

    return returnLocation + topBuffer;
}

void MainWindow::paint_world()
{
    QPainter paintWorld(this);

    QSize windowSize = this->size();
    int xSize = windowSize.width();
    int ySize = windowSize.height();

//    antEllipseSize = (initialAntEllipseSize*std::min(xSize,ySize))/150;
    antEllipseSize = (initialAntEllipseSize*std::min(xSize,ySize))/WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP;

    QRectF worldBorder(0,topBuffer,xSize,ySize-topBuffer);

    paintWorld.setBrush(worldColor);

    paintWorld.drawRect(worldBorder);
}

void MainWindow::paint_colonies()
{
    QPainter paintColonies(this);

    QSize windowSize = this->size();
    int xSize = windowSize.width();
    int ySize = windowSize.height();

    paintColonies.setBrush(colonyColor);
    std::vector<Colony> currWorldColonies = thisWorld.get_colonies();
    for(int i = 0; i < currWorldColonies.size(); i++)
    {
        std::vector<double> locations = currWorldColonies.at(i).get_colony_location();
        double colonyXLocation = locations[0];
        double colonyYLocation = locations[1];

        colonyXLocation = scale_x_value(colonyXLocation);
        colonyYLocation = scale_y_value(colonyYLocation);

        currWorldColonies.at(i).colonyEllipseSize = (currWorldColonies.at(i).initialColonyEllipseSize*std::min(xSize,ySize)*2)/(WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP);

        double drawEllipseSize{static_cast<double>(currWorldColonies.at(i).colonyEllipseSize*sqrt(currWorldColonies.at(i).get_number_of_ants()))/75};

        double plotLocationX = colonyXLocation - (drawEllipseSize/2);
        double plotLocationY = colonyYLocation - (drawEllipseSize/2);

        paintColonies.drawEllipse(plotLocationX, plotLocationY, drawEllipseSize,drawEllipseSize);
        paintColonies.drawText(colonyXLocation, colonyYLocation, QString::number(currWorldColonies.at(i).get_amount_of_food_in_colony()));

        paintColonies.drawEllipse(colonyXLocation, colonyYLocation,4,4);
    }
}

void MainWindow::paint_pheromones()
{
    QPainter paintTrail(this);

    int numRows =  WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP;
    int numCols = WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP;

    int colorStrengthScale{thisWorld.antWorldLogic.pheromoneMaxStrength};

    QPen trailPen{};

    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            if(thisWorld.colonyPheromoneArray[i][j]>0)
            {
                update_pheromone_color(thisWorld.colonyPheromoneArray[i][j], colorStrengthScale, false);

                trailPen.setColor(trailColor);
                trailPen.setWidth(2);

                paintTrail.setPen(trailPen);

                double pheromoneXLocation = scale_x_value(i);
                double pheromoneYLocation = scale_y_value(j);

                paintTrail.drawPoint(pheromoneXLocation, pheromoneYLocation);

                thisWorld.colonyPheromoneArray[i][j]-=1;
            }
            if(thisWorld.foodPheromoneArray[i][j]>0)
            {
                update_pheromone_color(thisWorld.foodPheromoneArray[i][j], colorStrengthScale, true);

                trailPen.setColor(trailColor);
                trailPen.setWidth(2);

                paintTrail.setPen(trailPen);

                double pheromoneXLocation = scale_x_value(i);
                double pheromoneYLocation = scale_y_value(j);

                paintTrail.drawPoint(pheromoneXLocation, pheromoneYLocation);

                thisWorld.foodPheromoneArray[i][j]-=1;
            }
        }
    }
}

void MainWindow::update_pheromone_color(double currentTrailPheromoneStrength, double scaleStrengthValue, bool isFood)
{
    int redValue{0};
    int blueValue{0};

    if(isFood)
    {
        redValue = (currentTrailPheromoneStrength*255)/scaleStrengthValue;
    }
    else
    {
        blueValue = (currentTrailPheromoneStrength*255)/scaleStrengthValue;
    }
    trailColor = QColor(redValue, 0, blueValue, 220);
}


void MainWindow::paint_food()
{
    QPainter paintFood(this);

    QSize windowSize = this->size();
    int xSize = windowSize.width();
    int ySize = windowSize.height();

    paintFood.setBrush(foodColor);
    std::vector<Food> currWorldFood = thisWorld.get_food();
    for(int i = 0; i < currWorldFood.size(); i++)
    {
        std::vector<double> locations = currWorldFood.at(i).get_food_location();
        double foodXLocation = locations[0];
        double foodYLocation = locations[1];

        foodXLocation = scale_x_value(foodXLocation);
        foodYLocation = scale_y_value(foodYLocation);

        currWorldFood.at(i).foodEllipseSize = (currWorldFood.at(i).initialFoodEllipseSize*std::min(xSize,ySize)*2)/(WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP);

        double drawEllipseSize{static_cast<double>(currWorldFood.at(i).foodEllipseSize*currWorldFood.at(i).get_amount_of_food())/750};

        double plotLocationX = foodXLocation - (drawEllipseSize/2);
        double plotLocationY = foodYLocation - (drawEllipseSize/2);

        paintFood.drawEllipse(plotLocationX, plotLocationY, drawEllipseSize, drawEllipseSize);
        paintFood.drawText(foodXLocation, foodYLocation, QString::number(currWorldFood.at(i).get_amount_of_food()));
        paintFood.drawEllipse(foodXLocation, foodYLocation,4,4);
    }
}

void MainWindow::paint_ants()
{
    QPainter paintAnts(this);

    paintAnts.setBrush(antColor);
    for(int j = 0; j < thisWorld.get_number_of_colonies(); j++){
        std::vector<Colony> currWorldColonies = thisWorld.get_colonies();
        for(int i = 0; i < currWorldColonies.size(); i++)
        {
            std::vector<Ant> colonyAnts = currWorldColonies.at(i).get_colony_ants();
            for(int z = 0; z < colonyAnts.size(); z++){

                std::vector<double> locations = colonyAnts.at(z).get_position();

                double antInitialXLocation = locations[0];
                double antInitialYLocation = locations[1];

                double antXLocation = scale_x_value(antInitialXLocation);
                double antYLocation = scale_y_value(antInitialYLocation);

                double plotLocationX = antXLocation;
                double plotLocationY = antYLocation;

                if (colonyAnts.at(z).check_food() == true)
                {
                    antHead = foodColor;
                }
                else
                {
                    antHead = QColor(0, 0, 0, 255);
                }

                QPen antPen{antHead};
                antPen.setWidth(5);

                paintAnts.setPen(antPen);

                paintAnts.drawPoint(plotLocationX,plotLocationY);
            }
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    paint_world();

    paint_colonies();

    paint_food();

    paint_pheromones();

    paint_ants();
}

double MainWindow::generate_random_double()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, maxRandomNumber);
    return dis(gen);
}

void MainWindow::build_world()
{
    add_colony(generate_random_double(),generate_random_double(),100);
    for(int i = 0; i < numberOfFoodToAddToWorld; i++)
    {
        add_food(generate_random_double(),generate_random_double());
    }
}

void MainWindow::update_window()
{
    thisWorld.update_world();
    repaint();
    ui->numAnts->display(thisWorld.get_total_world_ants());
}

void MainWindow::on_addAnt_clicked()
{
    std::vector<double> locations = thisWorld.worldColonies.at(0).get_colony_location();
    double colonyXLocation = locations[0];
    double colonyYLocation = locations[1];

    thisWorld.worldColonies[0].add_ant(colonyXLocation, colonyYLocation);

    repaint();
    ui->numAnts->display(thisWorld.get_total_world_ants());
}

void MainWindow::on_updateDial_sliderMoved(int position)
{
    update_window();
}

void MainWindow::on_resetWorld_released()
{
    thisWorld.reset_world();

    build_world();

    repaint();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QSize windowSize = this->size();
    int xSize = windowSize.width();
    int ySize = windowSize.height();

    if (addFoodActive == true){
        add_food(ceil((event->scenePosition().x()*thisWorld.get_size_of_world())/(xSize)), (event->scenePosition().y()*thisWorld.get_size_of_world())/(ySize+(2*topBuffer)));
        addFoodActive = false;
    }
    else if (addAntActive == true)
    {
        thisWorld.worldColonies[0].add_ant(((event->scenePosition().x()*thisWorld.get_size_of_world())/(xSize)), ((event->scenePosition().y()*thisWorld.get_size_of_world())/(ySize+(2*topBuffer))), ui->updateDial->value());
        addAntActive = false;
    }
    repaint();
}

void MainWindow::on_addFoodOnClick_released()
{
    addFoodActive = true;
}

void MainWindow::on_addAntOnClick_released()
{
    addAntActive = true;
}

void MainWindow::update_world()
{
    update_window();
    ui->numAnts->display(thisWorld.get_total_world_ants());
}

void MainWindow::on_pushButton_released()
{
    if(!isPaused)
    {
        update_world();
    }
}


void MainWindow::on_pauseButton_released()
{
    isPaused = !isPaused;
}

