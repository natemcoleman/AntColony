#include "gtest/gtest.h"
#include "ant.h"
#include "food.h"
#include "ColonyLogic.hpp"
#include "AntWorldLogic.hpp"
#include "AntWorld.h"


TEST(Ant, AntConstructorInitializesToCorrectGivenValues)
{   
  Ant newAnt{2.54, -3.00, 187};


  EXPECT_EQ(newAnt.get_angle(), 187);
  EXPECT_EQ(newAnt.get_position()[0], 2.54);
  EXPECT_EQ(newAnt.get_position()[1], -3.00);
}

TEST(Ant, AntConstructorInitializesCorrectlyWithNoValues)
{
  Ant newAnt{};


  EXPECT_EQ(newAnt.get_angle(), 0);
  EXPECT_EQ(newAnt.get_position()[0], 0);
  EXPECT_EQ(newAnt.get_position()[1], 0);
}

TEST(Ant, SetAntPositions_GetCorrectResults)
{
    Ant newAnt{2.54, -3.00, 187};


    newAnt.set_position(0,-57);


    EXPECT_EQ(newAnt.get_position()[0], 0);
    EXPECT_EQ(newAnt.get_position()[1], -57);
}

TEST(Ant, SetAntAngle_GetCorrectResults)
{
    Ant newAnt{2.54, -3.00, 187};


    newAnt.set_angle(23.78);


    EXPECT_EQ(newAnt.get_angle(), 23.78);
}

TEST(Ant, UpdateAnt_GetNewValues_UseNonRandomAngle)
{
    Ant newAnt{2.54, -3.00, 187};


    newAnt.update_ant(3);

    EXPECT_EQ(newAnt.get_angle(), 190);



    newAnt.update_ant(-30);

    EXPECT_EQ(newAnt.get_angle(), 160);
}

TEST(Ant, InitializeWithNoFood)
{
    Ant newAnt{};


    ASSERT_FALSE(newAnt.check_food());


    newAnt.give_food();

    ASSERT_TRUE(newAnt.check_food());


    newAnt.take_food();

    ASSERT_FALSE(newAnt.check_food());
}

TEST(Ant, TestSettingFoundNewTrail)
{
    Ant newAnt{};


    newAnt.setHasFoundATrail(true);

    ASSERT_TRUE(newAnt.getHasFoundATrail());


    newAnt.setHasFoundATrail(false);

    ASSERT_FALSE(newAnt.getHasFoundATrail());
}

TEST(AntLogic, TestSettingAngle)
{
    AntLogic testAntLogic{};
    double firstAngle{5};
    double newAngle{24};

    double goldenAngle{24};


    testAntLogic.set_angle(firstAngle, newAngle);


    EXPECT_EQ(newAngle, goldenAngle);
}

TEST(AntLogic, TestSetNewPosition)
{
    AntLogic testAntLogic{};
    double firstX{0};
    double secondX{73.4};
    double firstY{0};
    double secondY{-13.5};

    double goldenX{73.4};
    double goldenY{-13.5};


    testAntLogic.set_position(firstX, firstY, secondX, secondY);


    EXPECT_EQ(firstX, goldenX);
    EXPECT_EQ(firstY, goldenY);
}

TEST(AntLogic, TestGiveAndTakeFood_ChangeBoolByReference)
{
    AntLogic testAntLogic{};
    bool antHasFood{false};


    testAntLogic.give_food(antHasFood);

    ASSERT_TRUE(antHasFood);


    testAntLogic.take_food(antHasFood);

    ASSERT_FALSE(antHasFood);
}

TEST(AntLogic, SetIfAntHasFoundATrail)
{
    AntLogic testAntLogic{};
    bool antHasFoundATrail{false};


    testAntLogic.set_has_found_a_trail(antHasFoundATrail, false);

    ASSERT_FALSE(antHasFoundATrail);


    testAntLogic.set_has_found_a_trail(antHasFoundATrail, true);

    ASSERT_TRUE(antHasFoundATrail);


    testAntLogic.set_has_found_a_trail(antHasFoundATrail, false);

    ASSERT_FALSE(antHasFoundATrail);
}

TEST(AntLogic, UpdateAntWithNonRandomNumber_IfHasNotFoundATrail)
{
    AntLogic testAntLogic{};

    bool antHasNotFoundATrail{false};

    double antXPosition{100};
    double antYPosition{100};
    double antAngle{0};

    double nonRandomNewAngle{90};

    double goldenX{101};
    double goldenY{100};
    double goldenAngle{90};


    testAntLogic.update_ant(antXPosition, antYPosition, antAngle, antHasNotFoundATrail, nonRandomNewAngle);


    EXPECT_NEAR(antXPosition, goldenX, 1E-5);
    EXPECT_NEAR(antYPosition, goldenY, 1E-5);
    EXPECT_NEAR(antAngle, goldenAngle, 1E-5);
}

TEST(AntLogic, UpdateAntWithNonRandomNumber_IfHasFoundATrail)
{
    AntLogic testAntLogic{};

    bool antHasFoundATrail{true};

    double antXPosition{100};
    double antYPosition{100};
    double antAngle{0};

    double nonRandomNewAngle{90};

    double goldenX{100};
    double goldenY{99};
    double goldenAngle{0};


    testAntLogic.update_ant(antXPosition, antYPosition, antAngle, antHasFoundATrail, nonRandomNewAngle);


    EXPECT_NEAR(antXPosition, goldenX, 1E-5);
    EXPECT_NEAR(antYPosition, goldenY, 1E-5);
    EXPECT_NEAR(antAngle, goldenAngle, 1E-5);
}

TEST(Food, InitializeWithNoValues)
{
    Food testFood{};


    EXPECT_EQ(testFood.get_amount_of_food(), 100);
    EXPECT_EQ(testFood.get_food_location()[0], 0);
    EXPECT_EQ(testFood.get_food_location()[1], 0);
}

TEST(Food, InitializeWithValues_GetCorrectValues)
{
    Food testFood{-13.64, 40.95234, 73};


    EXPECT_EQ(testFood.get_food_location()[0], -13.64);
    EXPECT_EQ(testFood.get_food_location()[1], 40.95234);
    EXPECT_EQ(testFood.get_amount_of_food(), 73);
}

TEST(Food, UpdateFood)
{
    Food testFood{};


    testFood.update_food();


    EXPECT_EQ(testFood.get_amount_of_food(), 99);
}

TEST(Food, UpdateFood_WithZeroFood)
{
    Food testFood{0,0,1};


    testFood.update_food();

    EXPECT_EQ(testFood.get_amount_of_food(), 0);


    testFood.update_food();

    EXPECT_EQ(testFood.get_amount_of_food(), 0);
}

TEST(Food, SetNewFoodAmount)
{
    Food testFood{};


    testFood.set_amount_of_food(43);


    EXPECT_EQ(testFood.get_amount_of_food(), 43);
}

TEST(Food, SetNewLocation)
{
    Food testFood{};


    testFood.set_location(34, 56.76);


    EXPECT_EQ(testFood.get_food_location()[0], 34);
    EXPECT_EQ(testFood.get_food_location()[1], 56.76);
}

TEST(FoodLogic, TestUpdatingFood)
{
    FoodLogic testFoodLogic{};
    int currentAmountOfFood{0};
    int firstGoldenValue{0};
    int secondGoldenValue{9};


    testFoodLogic.update_food(currentAmountOfFood);

    EXPECT_EQ(currentAmountOfFood, firstGoldenValue);


    currentAmountOfFood = 10;


    testFoodLogic.update_food(currentAmountOfFood);

    EXPECT_EQ(currentAmountOfFood, secondGoldenValue);


    testFoodLogic.update_food(currentAmountOfFood);

    EXPECT_EQ(currentAmountOfFood, secondGoldenValue-1);
}

TEST(FoodLogic, TestUpdatingFood_CheckThatItIsNeverSetBelowZero)
{
    FoodLogic testFoodLogic{};
    int currentAmountOfFood{0};
    int setAmountOfFoodNegative{-10};
    int goldenValue{0};


    testFoodLogic.update_food(currentAmountOfFood);

    EXPECT_EQ(currentAmountOfFood, goldenValue);


    testFoodLogic.set_amount_of_food(currentAmountOfFood, setAmountOfFoodNegative);

    EXPECT_EQ(currentAmountOfFood, goldenValue);
}

TEST(FoodLogic, TestSetAmountOfFood)
{
    FoodLogic testFoodLogic{};
    int amountOfFood{0};
    int newAmountOfFood{10};
    int goldenValue{10};


    testFoodLogic.set_amount_of_food(amountOfFood, newAmountOfFood);


    EXPECT_EQ(amountOfFood, goldenValue);
}

TEST(FoodLogic, TestSettingFoodLocation)
{
    FoodLogic testFoodLogic{};
    double foodXPosition{100};
    double foodYPosition{100};
    double newXPosition{89.5};
    double newYPosition{-37};

    double goldenX{89.5};
    double goldenY{-37};


    testFoodLogic.set_location(foodXPosition, foodYPosition, newXPosition, newYPosition);


    EXPECT_EQ(foodXPosition, goldenX);
    EXPECT_EQ(foodYPosition, goldenY);
}

TEST(ColonyLogic, TestResettingNumberOfAnts)
{
    ColonyLogic testColonyLogic{};
    int numberOfAnts{10};
    int goldenValue{0};


    testColonyLogic.reset_number_of_ants(numberOfAnts);


    EXPECT_EQ(numberOfAnts, goldenValue);
}

TEST(ColonyLogic, TestUpdatingColony_NoFoodInColony)
{
    ColonyLogic testColonyLogic{};
    int amountOfFoodInColony{0};
    int numberOfAnts{0};

    std::vector<Ant> testAntsVector{};
    std::vector<double> colonyLocation{100,100};

    int goldenFoodValue{0};
    int goldenAntValue{0};


    testColonyLogic.update_colony(amountOfFoodInColony, numberOfAnts, testAntsVector, colonyLocation);


    EXPECT_EQ(amountOfFoodInColony, goldenFoodValue);
    EXPECT_EQ(numberOfAnts, goldenAntValue);
}

TEST(ColonyLogic, TestUpdatingColony_FoodInColony)
{
    ColonyLogic testColonyLogic{};
    int amountOfFoodInColony{10};
    int numberOfAnts{0};

    int goldenFoodValue{5};
    int goldenAntValue{5};

    std::vector<Ant> testAntsVector{};
    std::vector<double> colonyLocation{100,100};


    testColonyLogic.update_colony(amountOfFoodInColony, numberOfAnts, testAntsVector, colonyLocation);


    EXPECT_EQ(amountOfFoodInColony, goldenFoodValue);
    EXPECT_EQ(numberOfAnts, goldenAntValue);
}

TEST(ColonyLogic, TestAddAntToColony_WithNoInitialAngle)
{
    ColonyLogic testColonyLogic{};
    std::vector<Ant> colonyAnts{};
    int numberOfAnts{0};
    double newAntX{10};
    double newAntY{27};

    double goldenNumberOfAnts{1};
    double goldenAntX{10};
    double goldenAntY{27};


    EXPECT_EQ(colonyAnts.size(), 0);


    testColonyLogic.add_ant_to_colony(colonyAnts, numberOfAnts, newAntX, newAntY);


    EXPECT_EQ(colonyAnts.size(), 1);
    EXPECT_EQ(numberOfAnts,  goldenNumberOfAnts);
    EXPECT_EQ(colonyAnts.at(0).get_position()[0], goldenAntX);
    EXPECT_EQ(colonyAnts.at(0).get_position()[1], goldenAntY);
}

TEST(ColonyLogic, TestAddAntToColony_WithInitialAngle)
{
    ColonyLogic newLogic{};
    std::vector<Ant> colonyAnts{};
    int numberOfAnts{0};
    double newAntX{24.3};
    double newAntY{-97.8};
    double antAngle{273};

    double goldenNumberOfAnts{1};
    double goldenAntX{24.3};
    double goldenAntY{-97.8};
    double goldenAngle{273};


    EXPECT_EQ(colonyAnts.size(), 0);


    newLogic.add_ant_to_colony(colonyAnts, numberOfAnts, newAntX, newAntY, antAngle);


    EXPECT_EQ(colonyAnts.size(), 1);
    EXPECT_EQ(numberOfAnts, goldenNumberOfAnts);
    EXPECT_EQ(colonyAnts.at(0).get_position()[0], goldenAntX);
    EXPECT_EQ(colonyAnts.at(0).get_position()[1], goldenAntY);
    EXPECT_EQ(colonyAnts.at(0).get_angle(), goldenAngle);
}

TEST(ColonyLogic, TestAddFoodToColony)
{
    ColonyLogic newLogic{};
    int amountOfFood{10};
    int firstGoldenAmountOfFood{11};


    newLogic.add_food_to_colony(amountOfFood);


    EXPECT_EQ(amountOfFood, firstGoldenAmountOfFood);
}

TEST(ColonyLogic, TestNonRandomDoubleGenerator)
{
    ColonyLogic newLogic{};
    double nonRandomDouble{10};
    double goldenDouble{10};


    EXPECT_EQ(newLogic.generate_non_random_double(nonRandomDouble), goldenDouble);
}

TEST(ColonyLogic, TestRandomDoubleGeneratorIsWithinRange)
{
    ColonyLogic newLogic{};
    double highRange{360};
    double lowRange{0};
    bool isWithinRange{true};
    double randomDouble{0};

    for(int i = 0; i < 100; i++)
    {
        randomDouble = newLogic.generate_random_double();

        if(randomDouble > highRange || randomDouble < lowRange)
        {
            isWithinRange = false;
        }
    }

    ASSERT_TRUE(isWithinRange);
}

TEST(AntWorldLogic, TestAddColonyToWorld)
{
    AntWorldLogic newLogic{};
    std::vector<Colony> worldColonies{};
    double colonyX{13.5};
    double colonyY{45.6};
    double goldenX{13.5};
    double goldenY{45.6};


    EXPECT_EQ(worldColonies.size(), 0);


    newLogic.add_colony(worldColonies, colonyX, colonyY);


    EXPECT_EQ(worldColonies.at(0).get_colony_location()[0], goldenX);
    EXPECT_EQ(worldColonies.at(0).get_colony_location()[1], goldenY);
}

TEST(AntWorldLogic, TestAddFoodToWorld)
{
    AntWorldLogic newLogic{};
    std::vector<Food> worldFood{};
    double foodX{13.5};
    double foodY{45.6};
    int foodAmount{90};

    double goldenX{13.5};
    double goldenY{45.6};
    int goldenFoodAmount{90};


    EXPECT_EQ(worldFood.size(), 0);


    newLogic.add_food(worldFood, foodX, foodY, foodAmount);


    EXPECT_EQ(worldFood.at(0).get_food_location()[0], goldenX);
    EXPECT_EQ(worldFood.at(0).get_food_location()[1], goldenY);
    EXPECT_EQ(worldFood.at(0).get_amount_of_food(), goldenFoodAmount);
}

class AntWorldSpy: public AntWorld
{
public:
    void create_world()
    {
        Colony firstWorldColony{10, 10};
        worldColonies.push_back(firstWorldColony);

        worldColonies.at(0).add_ant(5,5,135);

        Food firstWorldFood{15, 15, 10};
        worldFood.push_back(firstWorldFood);
   }
    void set_pheromone_max_strength(int newStrength)
    {
        pheromoneMaxStrength = newStrength;
    }
    double sizeOfThisWorld{10};
    int numberOfAnts{1};
};

TEST(AntWorldLogic, TestResetWorld)
{
    AntWorldSpy testWorld{};
    testWorld.create_world();


    EXPECT_NE(testWorld.get_total_world_ants(), 0);
    EXPECT_NE(testWorld.get_colonies().size(), 0);
    EXPECT_NE(testWorld.get_food().size(), 0);
    EXPECT_NE(testWorld.get_number_of_colonies(), 0);


    testWorld.antWorldLogic.reset_world(testWorld.worldColonies, testWorld.totalWorldAnts, testWorld.worldFood, testWorld.foodPheromoneArray, testWorld.colonyPheromoneArray);


    EXPECT_EQ(testWorld.get_total_world_ants(), 0);
    EXPECT_EQ(testWorld.get_colonies().size(), 0);
    EXPECT_EQ(testWorld.get_food().size(), 0);
    EXPECT_EQ(testWorld.get_number_of_colonies(), 0);
}

TEST(AntWorldLogic, GetNumberOfColonies)
{
    AntWorldSpy testWorld{};
    testWorld.create_world();

    int goldenNumberOfColonies{1};


    EXPECT_EQ(testWorld.get_number_of_colonies(), goldenNumberOfColonies);
}

TEST(AntWorldLogic, CheckWorldAntsLocationForEdge_ToKeepAntInWindow_XMax)
{
    AntWorldSpy testWorld{};
    testWorld.create_world();


    testWorld.worldColonies.at(0).add_ant(10,3,135);

    testWorld.antWorldLogic.check_world_ants_location(testWorld.worldColonies, testWorld.sizeOfThisWorld, testWorld.totalWorldAnts);


    ASSERT_TRUE(testWorld.worldColonies.at(0).colonyAnts.at(0).get_position()[0] < 10);
}

TEST(AntWorldLogic, CheckWorldAntsLocationForEdge_ToKeepAntInWindow_XMin)
{
    AntWorldSpy testWorld{};
    testWorld.create_world();


    testWorld.worldColonies.at(0).add_ant(0, 3, 280);

    testWorld.antWorldLogic.check_world_ants_location(testWorld.worldColonies, testWorld.sizeOfThisWorld, testWorld.totalWorldAnts);


    ASSERT_TRUE(testWorld.worldColonies.at(0).colonyAnts.at(0).get_position()[0] > 0);
}

TEST(AntWorldLogic, CheckWorldAntsLocationForEdge_ToKeepAntInWindow_YMax)
{
    AntWorldSpy testWorld{};
    testWorld.create_world();


    testWorld.worldColonies.at(0).add_ant(5, 10, 95);

    testWorld.antWorldLogic.check_world_ants_location(testWorld.worldColonies, testWorld.sizeOfThisWorld, testWorld.totalWorldAnts);


    ASSERT_TRUE(testWorld.worldColonies.at(0).colonyAnts.at(0).get_position()[1] < 10);
}

TEST(AntWorldLogic, CheckWorldAntsLocationForEdge_ToKeepAntInWindow_YMin)
{
    AntWorldSpy testWorld{};
    testWorld.create_world();


    testWorld.worldColonies.at(0).add_ant(5, 0, 290);

    testWorld.antWorldLogic.check_world_ants_location(testWorld.worldColonies, testWorld.sizeOfThisWorld, testWorld.totalWorldAnts);


    ASSERT_TRUE(testWorld.worldColonies.at(0).colonyAnts.at(0).get_position()[1] > 0);
}

TEST(AntWorldLogic, CheckAntsLocationToSeeIfNearFood_IsNearFood)
{
    AntWorldSpy testWorld{};
    testWorld.create_world();

    double checkDistance{2};


    testWorld.worldColonies.clear();
    testWorld.add_colony(1,1);

    testWorld.worldFood.clear();
    testWorld.add_food(8,8);

    testWorld.worldColonies.at(0).add_ant(8,8);


    ASSERT_FALSE(testWorld.worldColonies.at(0).colonyAnts.at(0).check_food());
    EXPECT_EQ(testWorld.worldColonies.at(0).colonyAnts.size(), 1);


    testWorld.antWorldLogic.check_world_ants_and_food(testWorld.worldColonies, testWorld.worldFood, checkDistance);


    EXPECT_EQ(testWorld.worldFood.at(0).get_amount_of_food(), 99);
    ASSERT_TRUE(testWorld.worldColonies.at(0).colonyAnts.at(0).check_food());
}

TEST(AntWorldLogic, CheckAntsLocationToSeeIfNearFood_IsNotNearFood)
{
    AntWorldSpy testWorld{};
    testWorld.create_world();

    double checkDistance{2};


    testWorld.worldColonies.clear();
    testWorld.add_colony(1,1);

    testWorld.worldFood.clear();
    testWorld.add_food(8,8);

    testWorld.worldColonies.at(0).add_ant(2,2);


    ASSERT_FALSE(testWorld.worldColonies.at(0).colonyAnts.at(0).check_food());
    EXPECT_EQ(testWorld.worldColonies.at(0).colonyAnts.size(), 1);


    testWorld.antWorldLogic.check_world_ants_and_food(testWorld.worldColonies, testWorld.worldFood, checkDistance);


    EXPECT_EQ(testWorld.worldFood.at(0).get_amount_of_food(), 100);
    ASSERT_FALSE(testWorld.worldColonies.at(0).colonyAnts.at(0).check_food());
}

TEST(AntWorldLogic, CheckAntLocationToSeeIfNearColonies_IsNearColony_DoesNotHaveFood)
{
    AntWorldSpy testWorld{};
    testWorld.create_world();

    double checkDistance{2};
    double checkSize{2};


    testWorld.worldColonies.clear();
    testWorld.add_colony(1,1);

    testWorld.worldFood.clear();
    testWorld.add_food(8,8);

    testWorld.worldColonies.at(0).add_ant(2,2);


    ASSERT_FALSE(testWorld.worldColonies.at(0).colonyAnts.at(0).check_food());


    testWorld.antWorldLogic.check_world_ants_and_colonies(testWorld.worldColonies, checkSize);


    ASSERT_FALSE(testWorld.worldColonies.at(0).colonyAnts.at(0).check_food());
    ASSERT_FALSE(testWorld.worldColonies.at(0).colonyAnts.at(0).getHasFoundATrail());
}

TEST(AntWorldLogic, CheckAntLocationToSeeIfNearColonies_IsNearColony_DoesHaveFood_TooFarFromColony)
{
    AntWorldSpy testWorld{};
    testWorld.create_world();

    double checkDistance{2};
    double checkSize{2};


    testWorld.worldColonies.clear();
    testWorld.add_colony(1,1);

    testWorld.worldFood.clear();
    testWorld.add_food(8,8);

    testWorld.worldColonies.at(0).add_ant(5,5);
    testWorld.worldColonies.at(0).colonyAnts.at(0).take_food();


    ASSERT_FALSE(testWorld.worldColonies.at(0).colonyAnts.at(0).check_food());


    testWorld.worldColonies.at(0).colonyAnts.at(0).give_food();
    testWorld.antWorldLogic.check_world_ants_and_colonies(testWorld.worldColonies, checkDistance);


    ASSERT_TRUE(testWorld.worldColonies.at(0).colonyAnts.at(0).check_food());
    ASSERT_FALSE(testWorld.worldColonies.at(0).colonyAnts.at(0).getHasFoundATrail());
}

TEST(AntWorldLogic, CheckAntLocationToSeeIfNearColonies_IsNearColony_DoesHaveFood_WithinRangeOfColony)
{
    AntWorldSpy testWorld{};
    testWorld.create_world();

    double checkSize{2};
    double goldenFoodInColonyValue{11};


    testWorld.worldColonies.clear();
    testWorld.add_colony(1,1);

    testWorld.worldFood.clear();
    testWorld.add_food(8,8);

    testWorld.worldColonies.at(0).add_ant(1,1);
    testWorld.worldColonies.at(0).colonyAnts.at(0).take_food();


    ASSERT_FALSE(testWorld.worldColonies.at(0).colonyAnts.at(0).check_food());


    testWorld.worldColonies.at(0).colonyAnts.at(0).give_food();
    testWorld.worldColonies.at(0).colonyAnts.at(0).setHasFoundATrail(true);
    testWorld.antWorldLogic.check_world_ants_and_colonies(testWorld.worldColonies, checkSize);


    EXPECT_EQ(testWorld.worldColonies.at(0).get_amount_of_food_in_colony(), goldenFoodInColonyValue);
    ASSERT_FALSE(testWorld.worldColonies.at(0).colonyAnts.at(0).check_food());
    ASSERT_FALSE(testWorld.worldColonies.at(0).colonyAnts.at(0).getHasFoundATrail());
}

TEST(AntWorldLogic, CheckPheromoneArrays_ToSeeIfAntsAreFoundTrail_FoodTrail_NoFoodTrailOnLocation)
{
    AntWorldSpy testWorld{};
    testWorld.create_world();

    double checkSize{2};
    double goldenFoodInColonyValue{11};

    int foodPheromoneArray[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP];
    int colonyPheromoneArray[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP];


    testWorld.worldColonies.clear();
    testWorld.add_colony(0,0);

    testWorld.worldFood.clear();
    testWorld.add_food(5,5);

    testWorld.worldColonies.at(0).add_ant(5,5);


    testWorld.antWorldLogic.check_pheromone_trail(testWorld.worldColonies, testWorld.worldFood, foodPheromoneArray, colonyPheromoneArray);


    ASSERT_FALSE(testWorld.worldColonies.at(0).colonyAnts.at(0).getHasFoundATrail());
}

double TestPheromoneAngleAlgorithm(double angle)
{
    if(angle<0)
    {
        angle+=360;
    }
    angle-=90;
    if(angle<0)
    {
        angle+=360;
    }
    angle = 360-angle;

    return angle;
}

TEST(AntWorldLogic, Test_FindingCorrectAngleAlgorithm_UsedInFindingPheromoneTrail_ConvertingAngleFoundWithATan2ToNorthFacing360DegreeCWCoordinateSystem)
{
    double input1{180};
    double output1{270};
    double input2{135};
    double output2{315};
    double input3{90};
    double output3{360};
    double input4{45};
    double output4{45};
    double input5{0};
    double output5{90};
    double input6{-45};
    double output6{135};
    double input7{-90};
    double output7{180};
    double input8{-135};
    double output8{225};
    double input9{-179};
    double output9{269};


    EXPECT_EQ(TestPheromoneAngleAlgorithm(input1), output1);
    EXPECT_EQ(TestPheromoneAngleAlgorithm(input2), output2);
    EXPECT_EQ(TestPheromoneAngleAlgorithm(input3), output3);
    EXPECT_EQ(TestPheromoneAngleAlgorithm(input4), output4);
    EXPECT_EQ(TestPheromoneAngleAlgorithm(input5), output5);
    EXPECT_EQ(TestPheromoneAngleAlgorithm(input6), output6);
    EXPECT_EQ(TestPheromoneAngleAlgorithm(input7), output7);
    EXPECT_EQ(TestPheromoneAngleAlgorithm(input8), output8);
    EXPECT_EQ(TestPheromoneAngleAlgorithm(input9), output9);
}

TEST(AntWorldLogic, CheckStrongestPheromoneDirection_HasFood_FindColony)
{
    int antX{5};
    int antY{45};
    double firstAngle{27.5};
    bool antHasFood{true};
    int foodPheromoneArray[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP];
    int colonyPheromoneArray[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP];
    double newAntAngle{};
    AntWorldLogic newLogic{};
    Ant tempAnt{};
    Colony firstColony(10,40);
    std::vector<Colony> colonyVector{firstColony};
    Food firstFood(5,5);
    std::vector<Food> testFood{firstFood};

    double goldenAngle{45};


    foodPheromoneArray[antX][antY] = 5;
    colonyPheromoneArray[10][40] = 10;
    newAntAngle = newLogic.get_strongest_pheromone_direction(colonyVector, testFood, tempAnt, antX, antY, antHasFood, foodPheromoneArray, colonyPheromoneArray, firstAngle);


    EXPECT_NEAR(newAntAngle, goldenAngle, 1);
}

TEST(AntWorldLogic, CheckStrongestPheromoneDirection_DoesntHaveFood_FindFood)
{
    int antX{5};
    int antY{45};
    double firstAngle{27.5};
    bool antHasFood{false};
    int foodPheromoneArray[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP];
    int colonyPheromoneArray[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP];
    double newAntAngle{};
    AntWorldLogic newLogic{};
    Ant tempAnt{};
    Colony firstColony(10,40);
    std::vector<Colony> colonyVector{firstColony};
    Food firstFood(10,40);
    std::vector<Food> testFood{firstFood};

    double goldenAngle{45};


    foodPheromoneArray[antX][antY] = 5;
    foodPheromoneArray[10][40] = 10;
    newAntAngle = newLogic.get_strongest_pheromone_direction(colonyVector, testFood, tempAnt, antX, antY, antHasFood, foodPheromoneArray, colonyPheromoneArray, firstAngle);


    EXPECT_NEAR(newAntAngle, goldenAngle, 1);
}

TEST(AntWorldLogic, CheckStrongestPheromoneDirection_DoesntHaveFood_FindFood_LargeAngle)
{
    int antX{5};
    int antY{5};
    double firstAngle{27.5};
    bool antHasFood{false};
    int foodPheromoneArray[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP];
    int colonyPheromoneArray[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP];
    double newAntAngle{};
    AntWorldLogic newLogic{};
    Ant tempAnt{};
    Colony firstColony(10,40);
    std::vector<Colony> colonyVector{firstColony};
    Food firstFood(10,10);
    std::vector<Food> testFood{firstFood};

    double goldenAngle{135};


    foodPheromoneArray[10][10] = 10;
    newAntAngle = newLogic.get_strongest_pheromone_direction(colonyVector, testFood, tempAnt, antX, antY, antHasFood, foodPheromoneArray, colonyPheromoneArray, firstAngle);


    EXPECT_NEAR(newAntAngle, goldenAngle, 1);
}

TEST(AntWorldLogic, CheckStrongestPheromoneDirection_DoesntHaveFood_FindFood_NonDiscreteAngle)
{
    int antX{45};
    int antY{45};
    double firstAngle{27.5};
    bool antHasFood{false};
    int foodPheromoneArray[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP];
    int colonyPheromoneArray[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP];
    double newAntAngle{};
    AntWorldLogic newLogic{};
    Ant tempAnt{};
    Colony firstColony(10,40);
    std::vector<Colony> colonyVector{firstColony};
    Food firstFood(40,40);
    std::vector<Food> testFood{firstFood};


    double goldenAngle{315};


    foodPheromoneArray[40][40] = 10;
    newAntAngle = newLogic.get_strongest_pheromone_direction(colonyVector,testFood, tempAnt, antX, antY, antHasFood, foodPheromoneArray, colonyPheromoneArray, firstAngle);


    EXPECT_NEAR(newAntAngle, goldenAngle, 1);
}

TEST(AntWorldLogic, CheckPheromoneArrays_ToSeeIfAntsAreFoundTrail_FoodTrail_FoodTrailOnLocation)
{
    std::vector<Colony> testColonies{};
    AntWorldLogic newLogic{};
    Colony firstColony{0, 0};
    int antX{5};
    int antY{5};
    int foodPheromoneArray[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP];
    int colonyPheromoneArray[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP];
    Food firstFood(40,40);
    std::vector<Food> testFood{firstFood};

    firstColony.add_ant(antX, antY);
    testColonies.push_back(firstColony);
    foodPheromoneArray[antX][antY] = 5;


    ASSERT_FALSE(testColonies.at(0).colonyAnts.at(0).getHasFoundATrail());


    newLogic.check_pheromone_trail(testColonies, testFood, foodPheromoneArray, colonyPheromoneArray);


    ASSERT_TRUE(testColonies.at(0).colonyAnts.at(0).getHasFoundATrail());
}
