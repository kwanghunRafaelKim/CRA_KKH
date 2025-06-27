#include "gmock/gmock.h"

#include "Common.h"
#include "car.h"
#include "carfactory.h"
#include "carSimulator.h"

TEST(CarTest, SedanWithContinentalBrake) {
    Car car;
    car.setCarType(CarType::SEDAN);
    car.setBrakeSystem(brakeSystem::CONTINENTAL);

    EXPECT_EQ(car.carValidCheck(), ErrorType::CASE_SEDAN_CONTINENTAL_B);

    car.setCarType(CarType::SUV);
    car.setEngine(Engine::TOYOTA);

    EXPECT_EQ(car.carValidCheck(), ErrorType::CASE_SUV_TOYOTA_ENGINE);

    car.setCarType(CarType::TRUCK);
    car.setEngine(Engine::WIA);

    EXPECT_EQ(car.carValidCheck(), ErrorType::CASE_TRUCK_WIA_ENGINE);

    car.setCarType(CarType::TRUCK);
    car.setBrakeSystem(brakeSystem::MANDO);

    EXPECT_EQ(car.carValidCheck(), ErrorType::CASE_TRUCK_MANDO_B);

    car.setBrakeSystem(brakeSystem::BOSCH_B);
    car.setSteeringSystem(SteeringSystem::MOBIS);  // not BOSCH_S

    EXPECT_EQ(car.carValidCheck(), ErrorType::CASE_BOSCH_B_NOT_BOSCH_S);

    car.setEngine(Engine::BROKEN_ENGINE);

    EXPECT_EQ(car.carValidCheck(), ErrorType::CASE_BROKEN_ENGINE);
}

TEST(CarFactoryTest, SetCarType) {
    CarFactory factory;
    factory.makeCar(CarType_Q, static_cast<int>(CarType::SUV));

    EXPECT_EQ(factory.getCar().getCarType(), CarType::SUV);

    factory.makeCar(Engine_Q, static_cast<int>(Engine::TOYOTA));

    EXPECT_EQ(factory.getCar().getEngine(), Engine::TOYOTA);
}
//
//TEST(CarSimulatorTest, Run_BrokenEngine) {
//    Car car;
//    car.setCarType(CarType::SEDAN);
//    car.setBrakeSystem(brakeSystem::CONTINENTAL);
//    car.setEngine(Engine::BROKEN);
//}
//