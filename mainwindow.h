#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "AntWorld.h"
//#include <random>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setup_graphics_window();
    void add_food(double foodX, double foodY);
    void add_colony(double colonyX, double colonyY);
    void add_colony(double colonyX, double colonyY, int foodAmount);

    double generate_random_double();


protected:
    AntWorld thisWorld{};

    void build_world();
    void update_window();
    void paint_colonies();
    void paint_food();
    void paint_world();
    void paint_ants();
    void paint_pheromones();
    void update_pheromone_color(double currentTrailPheromoneStrength, double scaleStrengthValue, bool isFood);

    double scale_x_value(double inputXValue);
    double scale_y_value(double inputYValue);


    int topBuffer{100};
    int antEllipseSize{5};
    int pheromoneEllipseSize{3};
    double maxRandomNumber{WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP-5};
    int timerPauseValue{40};

    const int initialAntEllipseSize{5};
    const int initialPheromoneEllipseSize{5};
    const int numberOfFoodToAddToWorld{5};

    bool addFoodActive{false};
    bool addAntActive{false};
    bool isPaused{false};

    QColor worldColor = QColor(240, 214, 180, 255);
    QColor colonyColor = QColor(92, 71, 27, 255);
    QColor foodColor = QColor(99, 212, 135, 255);
    QColor antColor = QColor(0, 0, 0, 255);
    QColor antHead = QColor(183, 0, 0, 255);
    QColor trailColor = QColor(239, 255, 1, 255);

    QSize originalWindowSize{600,600};


private:
    Ui::MainWindow *ui;
    QDockWidget* mAntView;
    QGraphicsView* mGraphicsView;

public slots:
    void update_world();

private slots:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void on_addAnt_clicked();
    void on_updateDial_sliderMoved(int position);
    void on_resetWorld_released();
    void on_addFoodOnClick_released();
    void on_addAntOnClick_released();
    void on_pushButton_released();
    void on_pauseButton_released();
};


#endif // MAINWINDOW_H
